#ifndef MATH_NEON_H
#define MATH_NEON_H

#ifdef __cplusplus
extern "C" {
#endif

// 判断是否支持 NEON
#if defined(__ARM_NEON) || defined(__aarch64__)
#define __MATH_NEON
#endif

// fabsf 函数声明
float fabsf_c(float x);
float fabsf_neon_hfp(float x);
float fabsf_neon_sfp(float x);

#ifdef __cplusplus
}
#endif

#endif // MATH_NEON_H
