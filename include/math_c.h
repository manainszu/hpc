#ifndef MATH_NEON_H
#define MATH_NEON_H

#include <arm_neon.h> // neon
#include <math_neon.cpp> // 源文件

namespace ops{
    
    #ifdef __cplusplus
    extern "C" {
    #endif
    
    // 判断是否支持 NEON
    #if defined(__ARM_NEON) || defined(__aarch64__)
    #define __MATH_NEON
    #endif
    
    // fabsf 函数声明
    float ops::fabsf_c(float x)
    
    float ops::fabsf_neon_hfp(float x);
    
    float ops::fabsf_neon_sfp(float x);
    
    #ifdef __cplusplus
    }
    #endif
}


#endif // MATH_NEON_H
