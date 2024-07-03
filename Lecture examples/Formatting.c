/* Formatting.c: formatted output demo      */
/* author: Mervin Nguyen                    */
/* modifications:                           */
/* 01/10/24                                 */
#include <stdio.h>

/* main function*/

int main(void){
    /* output section */
    printf("42 formatted as |%%d|:     |%d|\n", 42);
    printf("42 formatted as |%%8d|:    |%8d|\n", 42);
    printf("42 formatted as |%%-8d|:   |%-8d|\n", 42);
    printf("42 formatted as |%%+8d|:   |%+8d|\n", 42);
    printf("42 formatted as |%%08d|:   |%08d|\n", 42);
    printf("42 formatted as |%%x|:  |%x|\n", 42);
    printf("42 formatted as |%%o|:  |%o|\n", 42);
    printf("\n");
    printf("123.456 formatted as |%%f|:     |%f|\n", 123.456);
    printf("123.456 formatted as |%%e|:  |%e|\n", 123.456);
    printf("123.456 formatted as |%%g|:  |%g|\n", 123.456);
    printf("123.456 formatted as |%%12.4f|:  |%12.4f|\n", 123.456);
    printf("123.456 formatted as |%%12.4e|:  |%12.4e|\n", 123.456);
    printf("123.456 formatted as |%%12.4g|:  |%12.4g|\n", 123.456);
    printf("\n");
    printf("\"abc\" formatted as |%%12s|:     |%12s|\n", "abc");
    return 0;
}