cmake_minimum_required(VERSION 3.10)

# 项目名称
project(MathNeonLibrary CXX)

# 设置C标准为99
set(CMAKE_C_STANDARD 11)

# 查找GTest库
find_package(GTest REQUIRED)

# 添加源文件
add_executable(ops_test test/main.cpp)

# 设置包含目录
target_include_directories(ops_test PUBLIC ${GTEST_INCLUDE_DIRS})

# 链接 GTest 和 GMock 库
target_link_libraries(ops_test GTest::GTest GTest::GMock)

# 如果你要使用NEON指令集，这里是一个示例（根据需要启用NEON支持）
if(CMAKE_SYSTEM_PROCESSOR MATCHES "aarch64")
    add_compile_options(-mfpu=neon)
endif()

# 如果有其他源代码文件可以继续添加
# add_library(MathNeonLibrary STATIC src/some_source.cpp)
