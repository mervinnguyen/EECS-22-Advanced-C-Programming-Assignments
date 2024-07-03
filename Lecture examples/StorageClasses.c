/* StorageClasses.c: example for storage classes and linkage*/
/* author: Mervin Nguyen                                    */
/*                                                          */
/* modifications:                                           */
/* 1/31/2024                                                */
/*                                                          */

/*** global scope ***/

       void f(int);
extern void g(int); 
static void h(int);

       double x;
extern double y;
static double z;

typedef double t;

void f(int p){
    /*** local scope ***/

    int i;
    int j;
    int r;
    int n = 0;
    n++;
    
    for (i=0; i < n; i++){
        for (j=0; j < p; j++){
            g(i*j);
        }
    }

    for (r=0; r<1000000; r++){
        h(r);
    }
}

static void h(int p){
    g(p+(x*y*z));
}