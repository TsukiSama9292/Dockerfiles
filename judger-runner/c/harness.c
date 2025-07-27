/*
 * Config-Driven OJ Runner - Pure Function Interface
 * ------------------------------------------------
 * - harness.c is universal and never changes
 * - config.json defines input values and function signature
 * - User function receives inputs as initial parameter values
 * - No global variables needed
 *
 * Example config.json:
 * {
 *   "solve_params": [
 *     {"name": "a", "input_value": 3},
 *     {"name": "b", "input_value": 4}
 *   ],
 *   "expected": {"a": 6, "b": 9}
 * }
 *
 * User writes only:
 *   int solve(int *a, int *b) {
 *     *a = *a * 2;
 *     *b = *b + 5;
 *     return 0;
 *   }
 */

#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/resource.h>
#include <sys/time.h>
#include <sys/wait.h>
#include <cjson/cJSON.h>

static double now() {
    struct timeval tv; 
    gettimeofday(&tv, NULL);
    return tv.tv_sec + tv.tv_usec * 1e-6;
}

static void generate_header(cJSON *cfg) {
    // Generate simple header without globals
    FILE *hf = fopen("solve.h", "w");
    if (!hf) { perror("Cannot create solve.h"); exit(1); }
    
    fprintf(hf, "// Auto-generated function header\n");
    fprintf(hf, "#ifndef SOLVE_H\n#define SOLVE_H\n\n");
    fprintf(hf, "#include <stdio.h>\n\n");
    
    // Generate solve function signature
    fprintf(hf, "// User solve function\n");
    fprintf(hf, "int solve(");
    cJSON *params = cJSON_GetObjectItem(cfg, "solve_params");
    if (cJSON_IsArray(params)) {
        int count = cJSON_GetArraySize(params);
        for (int i = 0; i < count; i++) {
            if (i > 0) fprintf(hf, ", ");
            cJSON *param = cJSON_GetArrayItem(params, i);
            const char *name = cJSON_GetObjectItem(param, "name")->valuestring;
            fprintf(hf, "int *%s", name);
        }
    }
    fprintf(hf, ");\n\n");
    fprintf(hf, "#endif\n");
    fclose(hf);
}

static void generate_test_main(cJSON *cfg) {
    FILE *mf = fopen("test_main.c", "w");
    if (!mf) { perror("Cannot create test_main.c"); exit(1); }
    
    fprintf(mf, "// Auto-generated test main\n");
    fprintf(mf, "#include <stdio.h>\n");
    fprintf(mf, "#include \"solve.h\"\n\n");
    
    fprintf(mf, "int main() {\n");
    
    // Initialize parameters with input values
    cJSON *params = cJSON_GetObjectItem(cfg, "solve_params");
    
    if (cJSON_IsArray(params)) {
        int param_count = cJSON_GetArraySize(params);
        for (int i = 0; i < param_count; i++) {
            cJSON *param = cJSON_GetArrayItem(params, i);
            const char *name = cJSON_GetObjectItem(param, "name")->valuestring;
            int input_value = cJSON_GetObjectItem(param, "input_value")->valueint;
            fprintf(mf, "    int %s = %d;\n", name, input_value);
        }
        
        // Call solve function - let user.c produce stdout directly
        fprintf(mf, "    solve(");
        for (int i = 0; i < param_count; i++) {
            if (i > 0) fprintf(mf, ", ");
            cJSON *param = cJSON_GetArrayItem(params, i);
            const char *name = cJSON_GetObjectItem(param, "name")->valuestring;
            fprintf(mf, "&%s", name);
        }
        fprintf(mf, ");\n");
    }
    
    fprintf(mf, "    return 0;\n}\n");
    fclose(mf);
}

int main(int argc, char **argv) {
    if (argc != 3) {
        fprintf(stderr, "Usage: %s config.json result.json\n", argv[0]);
        return 1;
    }
    
    // Load config
    FILE *fc = fopen(argv[1], "rb");
    if (!fc) { perror("fopen config"); return 2; }
    fseek(fc, 0, SEEK_END); long len = ftell(fc); fseek(fc, 0, SEEK_SET);
    char *cfgtxt = malloc(len + 1);
    fread(cfgtxt, 1, len, fc); cfgtxt[len] = '\0'; fclose(fc);

    cJSON *cfg = cJSON_Parse(cfgtxt); free(cfgtxt);
    if (!cfg) {
        fprintf(stderr, "Invalid JSON config\n");
        return 3;
    }

    // Generate all necessary files
    generate_header(cfg);
    generate_test_main(cfg);
    
    // Compile everything with automatic stdio.h inclusion and capture stderr
    char compile_cmd[512];
    snprintf(compile_cmd, sizeof(compile_cmd), 
             "gcc -Wall -Wextra -std=c99 -include stdio.h -o test_runner test_main.c user.c 2>&1");
    
    FILE *compile_output = popen(compile_cmd, "r");
    if (!compile_output) {
        fprintf(stderr, "Failed to run compilation command\n");
        cJSON_Delete(cfg);
        return 4;
    }
    
    char compile_errors[4096] = {0};
    fread(compile_errors, 1, sizeof(compile_errors)-1, compile_output);
    int compile_rc = pclose(compile_output);
    
    if (compile_rc != 0) {
        fprintf(stderr, "Compilation failed\n");
        fprintf(stderr, "Compilation errors:\n%s\n", compile_errors);
        
        // Create error result with compilation details
        cJSON *error_res = cJSON_CreateObject();
        cJSON_AddStringToObject(error_res, "status", "COMPILE_ERROR");
        cJSON_AddStringToObject(error_res, "error", "Compilation failed");
        cJSON_AddStringToObject(error_res, "stderr", compile_errors);
        cJSON_AddNumberToObject(error_res, "exit_code", compile_rc);
        
        char *result_str = cJSON_Print(error_res);
        FILE *result_file = fopen(argv[2], "w");
        if (result_file) {
            fprintf(result_file, "%s\n", result_str);
            fclose(result_file);
        }
        free(result_str);
        cJSON_Delete(error_res);
        cJSON_Delete(cfg);
        return 4;
    }
    
    // Run the test and capture output
    struct rusage ru0, ru1;
    getrusage(RUSAGE_SELF, &ru0);
    double t0 = now();
    
    FILE *output = popen("./test_runner", "r");
    if (!output) {
        perror("Failed to run test");
        cJSON_Delete(cfg);
        return 5;
    }
    
    char test_output[4096] = {0};
    fread(test_output, 1, sizeof(test_output)-1, output);
    int rc = pclose(output);
    
    // Check if test execution failed
    if (rc != 0) {
        fprintf(stderr, "Test execution failed with code %d\n", rc);
        cJSON *error_res = cJSON_CreateObject();
        cJSON_AddStringToObject(error_res, "status", "ERROR");
        cJSON_AddStringToObject(error_res, "error", "Test execution failed");
        cJSON_AddNumberToObject(error_res, "exit_code", rc);
        
        char *result_str = cJSON_Print(error_res);
        FILE *result_file = fopen(argv[2], "w");
        if (result_file) {
            fprintf(result_file, "%s\n", result_str);
            fclose(result_file);
        }
        free(result_str);
        cJSON_Delete(error_res);
        cJSON_Delete(cfg);
        return 6;
    }
    
    double t1 = now();
    getrusage(RUSAGE_SELF, &ru1);
    
    // Build result with captured stdout
    cJSON *res = cJSON_CreateObject();
    
    // Since we're not parsing JSON anymore, just capture the raw stdout
    cJSON_AddStringToObject(res, "status", "SUCCESS");
    cJSON_AddStringToObject(res, "stdout", test_output);
    cJSON_AddNumberToObject(res, "time_sec", t1 - t0);
    
    double ut = (ru1.ru_utime.tv_sec - ru0.ru_utime.tv_sec) + 
                (ru1.ru_utime.tv_usec - ru0.ru_utime.tv_usec)/1e6;
    double st = (ru1.ru_stime.tv_sec - ru0.ru_stime.tv_sec) + 
                (ru1.ru_stime.tv_usec - ru0.ru_stime.tv_usec)/1e6;
    cJSON_AddNumberToObject(res, "cpu_utime", ut);
    cJSON_AddNumberToObject(res, "cpu_stime", st);
    cJSON_AddNumberToObject(res, "maxrss_mb", ru1.ru_maxrss/1024.0);

    // Write result
    char *s = cJSON_Print(res);
    FILE *fo = fopen(argv[2], "w"); 
    fputs(s, fo); 
    fclose(fo);
    
    cJSON_Delete(res);
    cJSON_Delete(cfg);
    free(s);
    
    return 0;
}
