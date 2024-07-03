#include <stdio.h>

int square (int a);
int add_y(int x);
int x = 5;
int y = 7;

int square (int a){
    int s;
    s= a * a;
    return s;
}

int add_y(int x){
    int s;
    s = x + y;
    return s;
}

int main(void){
    int z;

    z = square(x);
    z = add_y(z);

    printf("z is %d\n", z);
    return 0;
}