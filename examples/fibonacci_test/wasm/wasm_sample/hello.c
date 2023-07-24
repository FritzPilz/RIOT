/* Copyright (C) World
 * a native printf is provided by the builtin libc of wamr */

#ifdef __cplusplus
extern "C" int printf( const char *, ...);
#define WASM_EXPORT __attribute__((visibility("default"))) extern "C"
#else
extern int printf( const char *, ...);
int atoi(char* str);
#define WASM_EXPORT __attribute__((visibility("default")))
#endif

WASM_EXPORT int main(int argc, char **argv)
{
    //int n = atoi(argv[0]);
    int n = 24;
    int fib = 1;
    int prevFib = 1;
    for(int i = 2; i < n; ++i){
        int temp = fib;
        fib += prevFib;
        prevFib = temp;
    }
    return fib;
}

int atoi(char* str){
    int res = 0;
    for(int i = 0; str[i] != '\0';++i){
        res = (res*10) + (str[i]-'0');
    }
    return res;
}
