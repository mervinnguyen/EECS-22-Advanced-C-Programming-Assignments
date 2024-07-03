/* Cylinder.c: cylinder functions    */
/* author: Mervin Nguyen             */
/* modifications:                    */
/* 01/25/24 RD initial version         */

#include <stdio.h>

/*  cylinder functions */

double pi(void){
    return (3.1415927);
}

double CircleArea(double r){
    return(pi() * r * r);
}

double CirclePerimeter(double r){
    return(2 * pi() * r);
}

double Surface(double r, double h){
    double side, lid;
    side = CirclePerimeter(r) * h;
    lid = CircleArea(r);
    return(side + 2*lid);
}

double Volume(double r, double h){
    return(CircleArea(r) * h);
}

int main(void){
    double r, h, s, v;
    printf("Please enter the radius: ");
    scanf("%lf", &r);
    printf("Please enter the height: ");
    scanf("%lf", &h);

    /* computation section*/
    s = Surface(r, h);
    v = Volume(r, h);

    /* output section */
    printf("The surface area of the cylinder is: %lf\n", s);
    printf("The volume is %f. \n", v);

    return 0;
}