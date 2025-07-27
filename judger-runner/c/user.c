int solve(int *a, int *b) {
    printf("Hello from user.c!\n");
    printf("Input: a=%d, b=%d\n", *a, *b);
    *a = *a * 2;
    *b = *b + 5;
    printf("Output: a=%d, b=%d\n", *a, *b);
    return 0;
}