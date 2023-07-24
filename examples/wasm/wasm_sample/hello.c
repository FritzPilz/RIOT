/* Copyright (C) World
 * a native printf is provided by the builtin libc of wamr */

#ifdef __cplusplus
extern "C" int printf( const char *, ...);
#define WASM_EXPORT __attribute__((visibility("default"))) extern "C"
#else
extern int printf( const char *, ...);
#define WASM_EXPORT __attribute__((visibility("default")))
#endif

WASM_EXPORT int main(int argc, char **argv)
{
    if(argv[0] <= 1){
        return argv[0];
    }
    int fib = 1;
    int prevFib = 1;
    for(int i = 2; i < argv[0]; ++i){
        int temp = fib;
        fib += prevFib;
        prevFib = temp;
    }
    return fib;
}
