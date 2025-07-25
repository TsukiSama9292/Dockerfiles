import os
import time
import resource
import subprocess
from multiprocessing import Process, Manager
import re

def strip_ansi(s):
    ansi_escape = re.compile(r'\x1B[@-_][0-?]*[ -/]*[@-~]')
    return ansi_escape.sub('', s)

def run_sub(cmd, result, collect_stats=True):
    p = subprocess.Popen(cmd, shell=True, stdout=subprocess.PIPE, stderr=subprocess.PIPE)
    stdout, stderr = p.communicate()
    result['stdout'] = strip_ansi(stdout.decode())
    result['stderr'] = stderr.decode()
    result['returncode'] = p.returncode
    if collect_stats:
        usage = resource.getrusage(resource.RUSAGE_CHILDREN)
        result['utime'] = usage.ru_utime
        result['stime'] = usage.ru_stime
        result['maxrss_kb'] = usage.ru_maxrss

def measure(cmd, collect_stats=True):
    """
    執行一個子程序指令並收集執行結果與資源使用狀況。

    參數:
        cmd (str): 要執行的命令字串。
        collect_stats (bool): 是否收集 CPU 時間與記憶體使用統計，預設為 True。

    回傳(dict):
        {
            "stdout": str,           # 子程序標準輸出（文字內容）
            "stderr": str,           # 子程序標準錯誤輸出（錯誤訊息）
            "returncode": int,       # 子程序返回碼，0 通常代表成功，非 0 表示錯誤
            "time_wall_sec": float,  # （選擇性）牆鐘時間（秒），從啟動到結束的真實經過時間
            "cpu_utime": float,      # （選擇性）CPU 使用者態時間（秒），程式運算時間
            "cpu_stime": float,      # （選擇性）CPU 系統態時間（秒），系統呼叫或 I/O 花費的時間
            "maxrss_mb": float       # （選擇性）最大常駐記憶體大小，單位 MB（峰值記憶體使用量）
        }
    """
    with Manager() as mgr:
        result = mgr.dict()
        proc = Process(target=run_sub, args=(cmd, result, collect_stats))
        t0 = time.time()
        proc.start()
        proc.join()
        t1 = time.time()
        output = {
            "stdout": result.get("stdout"),
            "stderr": result.get("stderr"),
            "returncode": result.get("returncode"),
        }
        if collect_stats:
            output.update({
                "time_wall_sec": t1 - t0,
                "cpu_utime": result.get("utime"),
                "cpu_stime": result.get("stime"),
                "maxrss_mb": result.get("maxrss_kb") / 1024,
            })
        return output

def auto_compile_and_run(src_path, cleanup=False):
    ext = os.path.splitext(src_path)[1]
    filename = os.path.basename(src_path)
    name = os.path.splitext(filename)[0]

    if ext == ".c":
        exe = f"./{name}_out"
        # print(f"[編譯 C] gcc {src_path} -o {exe}")
        compile_result = measure(f"gcc {src_path} -o {exe}", collect_stats=False)
        if compile_result["returncode"] != 0:
            return {"stage": "compile", **compile_result}
        run_result = measure(exe)
        if cleanup:
            try: os.remove(exe)
            except Exception as e: print(f"[清理失敗] {exe}: {e}")
        return {"stage": "run", **run_result}

    elif ext == ".cpp":
        exe = f"./{name}_out"
        # print(f"[編譯 C++] g++ {src_path} -o {exe}")
        compile_result = measure(f"g++ {src_path} -o {exe}", collect_stats=False)
        if compile_result["returncode"] != 0:
            return {"stage": "compile", **compile_result}
        run_result = measure(exe)
        if cleanup:
            try: os.remove(exe)
            except Exception as e: print(f"[清理失敗] {exe}: {e}")
        return {"stage": "run", **run_result}

    elif ext == ".java":
        # print(f"[編譯 Java] javac {src_path}")
        compile_result = measure(f"javac {src_path}", collect_stats=False)
        if compile_result["returncode"] != 0:
            return {"stage": "compile", **compile_result}
        class_name = name
        run_result = measure(f"java {class_name}")
        if cleanup:
            try: os.remove(f"{class_name}.class")
            except Exception as e: print(f"[清理失敗] {class_name}.class: {e}")
        return {"stage": "run", **run_result}

    elif ext == ".js":
        # print(f"[執行 JavaScript] node {src_path}")
        return {"stage": "run", **measure(f"node {src_path}")}

    elif ext == ".py":
        # print(f"[執行 Python] python3 {src_path}")
        return {"stage": "run", **measure(f"python3 {src_path}")}

    elif ext == ".rs":
        exe = f"./{name}_out"
        # print(f"[編譯 Rust] rustc {src_path} -o {exe}")
        compile_result = measure(f"rustc {src_path} -o {exe}", collect_stats=False)
        if compile_result["returncode"] != 0:
            return {"stage": "compile", **compile_result}
        run_result = measure(exe)
        if cleanup:
            try: os.remove(exe)
            except Exception as e: print(f"[清理失敗] {exe}: {e}")
        return {"stage": "run", **run_result}

    elif ext == ".go":
        exe = f"./{name}_out"
        # print(f"[編譯 Go] go build -o {exe} {src_path}")
        compile_result = measure(f"go build -o {exe} {src_path}", collect_stats=False)
        if compile_result["returncode"] != 0:
            return {"stage": "compile", **compile_result}
        run_result = measure(exe)
        if cleanup:
            try: os.remove(exe)
            except Exception as e: print(f"[清理失敗] {exe}: {e}")
        return {"stage": "run", **run_result}

    elif ext == ".rb":
        # print(f"[執行 Ruby] ruby {src_path}")
        return {"stage": "run", **measure(f"ruby {src_path}")}

    elif ext == ".php":
        # print(f"[執行 PHP] php {src_path}")
        return {"stage": "run", **measure(f"php {src_path}")}

    elif ext == ".sh":
        # print(f"[執行 Shell] bash {src_path}")
        return {"stage": "run", **measure(f"bash {src_path}")}

    elif ext == ".cs":
        exe = f"./{name}_out"
        # print(f"[編譯 C#] mcs {src_path} -out:{exe}")
        compile_result = measure(f"mcs {src_path} -out:{exe}", collect_stats=False)
        if compile_result["returncode"] != 0:
            return {"stage": "compile", **compile_result}
        run_result = measure(f"mono {exe}")
        if cleanup:
            try: os.remove(exe)
            except Exception as e: print(f"[清理失敗] {exe}: {e}")
        return {"stage": "run", **run_result}

    elif ext == ".kt":
        exe = f"./{name}_out.jar"
        # print(f"[編譯 Kotlin] kotlinc {src_path} -include-runtime -d {exe}")
        compile_result = measure(f"kotlinc {src_path} -include-runtime -d {exe}", collect_stats=False)
        if compile_result["returncode"] != 0:
            return {"stage": "compile", **compile_result}
        run_result = measure(f"java -jar {exe}")
        if cleanup:
            try: os.remove(exe)
            except Exception as e: print(f"[清理失敗] {exe}: {e}")
        return {"stage": "run", **run_result}

    elif ext == ".ts":
        # print(f"[執行 TypeScript] ts-node {src_path}")
        return {"stage": "run", **measure(f"ts-node {src_path}")}

    elif ext == ".sql":
        # print(f"[執行 SQL] sqlite3 {src_path}")
        return {"stage": "run", **measure(f"sqlite3 {src_path}")}

    else:
        return {"error": f"Unsupported extension: {ext}"}

import argparse

def main():
    parser = argparse.ArgumentParser(description="Compile and run a file using runner.")
    parser.add_argument("--filename", type=str, default="main.py", help="The filename to compile and run.")
    parser.add_argument("--cleanup", action="store_true", help="Remove the compiled executable after running.")
    args = parser.parse_args()

    result = auto_compile_and_run(args.filename, cleanup=args.cleanup)
    print(result)

if __name__ == "__main__":
    main()