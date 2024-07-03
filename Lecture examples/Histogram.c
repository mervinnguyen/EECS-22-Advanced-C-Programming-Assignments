/*Histogram.c: print a histogram of data values */
/*author: Mervin Nguyen                         */
/*modifications:                                */
/* 1/23/24                                      */ 
#include <stdio.h>

//constants
#define NUM_ROWS 10

int main(void){
    int Data[NUM_ROWS];
    int i, j, max;
    double scale;

    //input section
    for(i = 0; i < NUM_ROWS; i++){
        printf("Please enter a data value %2d: ", i + 1);
        scanf("%d", &Data[i]);
        }

        max = 0;
        for(i = 0; i < NUM_ROWS; i++){
            if(Data[i] > max){
                max = Data[i];
            }
        }
        scale = 70.0 / max;
     
     //output section
    for(i = 0; i < NUM_ROWS; i++){
         printf("%2d: %5d", i+1, Data[i]);
            for(j = 0; j < Data[i]*scale; j++){
                printf("*");
            }
         printf("\n");
     }
    return 0;
}
