//Historgram2.c: print a histogram of data values
//author: Mervin Nguyen
//modifications:
#include <stdio.h>

//main function
int main(void){
    //input section
    int NumRows;
    printf("Number of data values: ");
    scanf("%d", &NumRows);

    //variable definitions
    int Data[NumRows]; //array of data values
    int i, j, max;
    double scale;

    //input section
    for(i = 0; i < NumRows; i++){
        printf("Data value %d: ", i + 1);
        scanf("%d", &Data[i]);
    }

    //Computation section
    max = 0;
    for(i = 0; i < NumRows; i++){
        if(Data[i] > max){
            max = Data[i];
        }
    }
    scale = 70.0 / max;

    //Output section
    for(i = 0; i < NumRows; i++){
        printf("%2d: %5d ", i + 1, Data[i]);
        for(j = 0; j < Data[i] * scale; j++){
            printf("*");
        }
        printf("\n");
    }
    return 0; 
}