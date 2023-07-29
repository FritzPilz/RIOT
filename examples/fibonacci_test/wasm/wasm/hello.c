#define WASM_EXPORT __attribute__((visibility("default")))

WASM_EXPORT int main(int argc, char **argv)
{
    int n = 24;

    if(n <= 2){
        return n;
    }
    int fib = 1;
    int prevFib = 0;
    for(int i = 1; i < n; ++i){
        int temp = fib;
        fib += prevFib;
        prevFib = temp;
    }
    return fib;

}
