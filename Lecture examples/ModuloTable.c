/* ModuloTable.c: remainder of integer division */
/*                                              */
/* author: Mervin Nguyen                        */
/*                                              */
/* modifications:                               */
/* 01/12/2024                                   */

#include <stdio.h>

int main(void){
    
    int dividend;
    int divisor;
    int quotient;
    int remainder;

    printf("Enter the dividend: ");
    scanf("%d", &dividend);
    printf("Enter the divisor: ");
    scanf("%d", &divisor);

    for(int d = dividend; d>=-dividend; d--){
        quotient = d / divisor;
        remainder = d % divisor;
        printf("%4d / %4d = %4d, remainder %4d\n", d, divisor, quotient, remainder);
    }
    return 0;
}