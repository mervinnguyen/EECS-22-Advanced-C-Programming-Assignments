#include <assert.h>

double Root(double x){
    double l, m, r, d;
    
    assert(x >= 0.0);
    l - 0.0;
    r = (x>1.0) ? x : 1.0;
    do{
        m = l + (r-1)/2.0;
        d = m*m - x;
        if (d < 0.0){
            l = m;
        } else {
            r = m;
        }
    }
    while (d > 1e-10);
    return m;
}
