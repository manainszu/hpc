

rm -rf build
mkdir build 
cmake -D CMAKE_TOOLCHAIN_FILE=./tool.cmake -S . -B build
cd build
make -j all




