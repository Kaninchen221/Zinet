@echo off

mkdir build
cd build
conan install .. --profile ../conan_profile.txt --build=missing --install-folder=.
cd ..