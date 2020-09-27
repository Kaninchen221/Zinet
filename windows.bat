@echo off
mkdir build
cd build
echo del CMakeCache.txt
cmake ../ -G "Visual Studio 16 2019" -DCMAKE_BUILD_TYPE:STRING=Debug -DBUILD_SHARED_LIBS:BOOL=TRUE -DZINET_LIBS_TYPE:STRING=SHARED
cd ..