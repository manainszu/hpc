#include <stdio.h>

float fabsf_c(float x)
{
    union {
        int i;
        float f;
    } xx;

    xx.f = x;
    xx.i = xx.i & 0x7FFFFFFF;
    return xx.f;
}

float fabsf_neon_hfp(float x)
{
#ifdef __MATH_NEON
    asm volatile (
        "vmov.f32    s0, %0         \n\t"  // x → s0
        "fabss       s0, s0         \n\t"  // fabs(s0)
        "vmov.f32    %0, s0         \n\t"  // s0 → x
        : "+t"(x)
    );
#endif
    return x;
}

int main() {
    float value = -3.14f;

    printf("fabsf_c(%f) = %f\n", value, fabsf_c(value));
    printf("fabsf_neon_hfp(%f) = %f\n", value, fabsf_neon_hfp(value));

    return 0;
}
