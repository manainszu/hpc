/*
 * @Author: chengye zheng chengye zheng@Narwal.com
 * @Date: 2025-03-28 22:36:03
 * @LastEditors: chengye zheng chengye zheng@Narwal.com 
 * @LastEditTime: 2025-03-28 23:55:46
 * @FilePath: /hpc/test/math_test.cpp
 * @Description: 
 */

#include <gtest/gtest.h>
#include <limits.h>
#include "runtime.hpp"
#include <stdio.h>
#include <random>
#include <chrono>
#include <iostream>
#include <math_c.h>
#include <math_neon.h>

float rm(){
    std::random_device random_machine;
    std::mt19937 gen(random_machine());
    std::uniform_real_distribution<float>dist(-10000,10000);
    return dist(gen);
}

TEST(RuntimeTest , Negitive){
    
    // 1. 用随机数的输入
    float rd = rm();
    
    // 2. C 版本时间
    auto start_time = std::chrono::high_resolution_clock::now();
    float result_c = ops::fabs(rd);
    auto end_time = std::chrono::high_resolution_clock::now();
    auto duration_c = std::chrono::duration_cast<std::chrono::microseconds>(end_time - start_time);

    // 3. NEON 版本时间
    auto start_time_neon = std::chrono::high_resolution_clock::now();
    float result_neon = ops::fabsf_neon_hfp(rd);
    auto end_time_neon = std::chrono::high_resolution_clock::now();
    auto duration_neon = std::chrono::duration_cast<std::chrono::microseconds>(end_time_neon - start_time_neon);
    
    // 4. 结果对比
    EXPECT_NEAR(result_c, result_neon, 1e-6);

    // 5. 时间比较，结果打印
    float effiency = duration_c / duration_neon ;
    std::cout<<" c_time is "<< duration_c.count() <<"microseconds\n";
    std::cout<<" neon_time is "<< duration_neon.count() <<"microseconds\n";
    std::cout<<" effiency of neon is "<< effiency << std::endl; // 单次的对比

}


    