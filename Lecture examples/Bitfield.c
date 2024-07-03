#include <stdio.h>

struct FloatFormat {
    unsigned int Mantissa : 23;
    unsigned int Exponent : 8;
    unsigned int Sign : 1;
};

union FloatUnion {
    float Value;
    struct FloatFormat Format;
    }
    Float = {
        -1.0
    };

int main(void) {
    printf("sizeof (float) = %lu\n", sizeof(float));
    printf("sizeof (Float) = %lu\n", sizeof(Float));
    printf("Float.Value = %f\n", Float.Value);
    printf("Float.Format.Sign = %u\n", Float.Format.Sign);
    printf("Float.Format.Exponent = %u\n", Float.Format.Exponent);
    printf("Float.Format.Mantissa = %u\n", Float.Format.Mantissa);
    return 0;
}
