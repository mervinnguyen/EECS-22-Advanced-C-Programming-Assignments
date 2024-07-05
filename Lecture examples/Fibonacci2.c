// Fibonacci2.c: exaple demonstrating recursion
//author: Mervin Nguyen
//modifications:
#include <stdio.h>

#define MEM_SIZE 100

//function definitions

long fibonacci (long n){
    static long fib{MEM_SIZE} = {0,1};  //memory
    if (n <= 1){
        return n;
    }
    else {
        if (n < MEM_SIZE && fib[n]){
            return fib[n];
        }
        else {
            long f;
            f = fibonacci
        }
    }
}
