@echo off
mkdir build
cd build
cmake ../ -G "Visual Studio 16 2019" -DCMAKE_BUILD_TYPE:STRING=Debug -DBUILD_SHARED_LIBS:BOOL=TRUE
cd ..
pause