/* Fibonacci.c: example demonstrating recursion */
/* author: Mervin Nguyen                        */
/* modifications:                               */
/* 01/26/24 RD  initial version                 */

#include <stdio.h>

/* function definition*/
long fibonacci(long n){
    if ( n <=1){
        return n;
    }
    else{
        return (fibonacci(n-1) + fibonacci(n-2));
    }
}

int main(void){
    long int n, f;

    printf("Please enter value n: ");
    scanf("%ld", &n);
    
    f = fibonacci(n);
    
    printf("The %ld-th Fibonacci number is %ld. \n", n, f);

    return 0;
}

