
#include<gtest/gtest.h>
#include <limits.h>
#include "runtime.hpp"
#include <stdio.h>
#include <random>

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

float rm(){
    std::random_device random_machine;
    std::mt19937 gen(random_machine());
    std::uniform_real_distribution<float>dist(-10000,10000);
    return dist(gen);
}
TEST(precise , negative){
    for (int i ; i<10000 ;i++){
        float rd = rm() ;
        float result_1 =  fabsf_c(rd);
        float result_2 =  fabsf_neon_hfp(rd);
        EXPECT_NEAR(result_1,result_2,1e-5);
    }
    
}
TEST(RuntimeTest , Negitive){
    
    auto start_time = std::chrono::high_resolution_clock::now();
    for(int i = 0 ; i<1000 ;i++){
        float rd = rm();
        float time_c = fabs(rd);
    }
    auto end_time = std::chrono::high_resolution_clock::now();
    auto duration_c = std::chrono::duration_cast<std::chrono::microseconds>(end_time - start_time);

    //neon 版本
    auto start_time_neon = std::chrono::high_resolution_clock::now();
    for(int i = 0 ; i<1000 ; i++){
        float rd = rm();
        float time_c = fabsf_neon_hfp(rd);
    }
    auto end_time_neon = std::chrono::high_resolution_clock::now();
    auto duration_neon = std::chrono::duration_cast<std::chrono::microseconds>(end_time_neon - start_time_neon);
    float effiency = duration_c/duration_neon ;
    std::cout<<"c_time is  "<< duration_c.count()<<"microseconds\n";
    std::cout<<"neon_time is  "<< duration_neon.count()<<"microseconds\n";
    std::cout<<"effiency of neon is "<<effiency<<std::endl;
}


    