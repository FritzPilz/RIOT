int fibonacci(unsigned int n)
{
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