/*  Average.c: Compute the average of a set of numbers*/
/*                                                    */
/*  Author: Mervin Nguyen                             */
/*                                                    */
/*  modifications:                                    */
#include <stdio.h>
int main(void){
    int counter;
    double value;
    double total;
    double average;

    /*input and computation section */
    counter = 0;
    total = 0.0;
    
    while(1){
        printf("Enter a value (or -1 to quit): ");
        scanf("%lf", &value);
        if(value == -1.0){
            break;
        }

        total = total + value;
        counter = counter + 1;

    }

    printf("%d values entered.\n", counter);
    if (counter >= 1)
    {
        average = total / counter;
        printf("The average is %lf\n", average);
    }
    return 0;
}