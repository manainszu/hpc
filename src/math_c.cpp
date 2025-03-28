/*
 * @Author: chengye zheng chengye zheng@Narwal.com
 * @Date: 2025-03-28 22:36:03
 * @LastEditors: chengye zheng chengye zheng@Narwal.com 
 * @LastEditTime: 2025-03-28 23:31:10
 * @FilePath: /hpc/src/math_c.cpp
 * @Description: 
 */
 
#include <math_c.h>
	
float ops::fabsf_c(float x)
{
	union {  //共用一个地址，用一个影响另一个
		int i;
		float f;
	} xx;

	xx.f = x;
	xx.i = xx.i & 0x7FFFFFFF;
	return xx.f;
}

float ops::fabsf_neon_hfp(float x)
{
	Mat image;
#ifdef __MATH_NEON
	asm volatile (
	"fabss	 		s0, s0					\n\t"	//s0 = fabs(s0)
	);
#endif
}

float ops::fabsf_neon_sfp(float x)
{
#ifdef __MATH_NEON
	asm volatile (
	"bic	 		r0, r0, #0x80000000		\n\t"	//r0 = r0 & ~(1 << 31)
	);
#else
	return fabsf_c(x);
#endif
}