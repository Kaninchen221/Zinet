@echo off
mkdir build
cd build
conan install .. --profile ../conan_profile.txt --build=missing --install-folder=.
cmake ../ -G "Visual Studio 16 2019" -D CMAKE_BUILD_TYPE:STRING=Debug -D BUILD_SHARED_LIBS:BOOL=TRUE -D SAMPLES_BUILD_WITH_LOCAL_VULKAN_HPP=ON -D SAMPLES_BUILD=ON -D TESTS_BUILD_WITH_LOCAL_VULKAN_HPP=ON -D TESTS_BUILD=ON
cd ..
pause
