import argparse
import os
import subprocess
import sys

parser = argparse.ArgumentParser(description='CMake Build')

parser.add_argument('--BuildType', type=str, help='Debug or Release', default='Debug')

args = parser.parse_args()

print('BuildType:', args.BuildType)

if args.BuildType == "Debug" or args.BuildType == "Release":
    arguments = f'-S ./ -B ./build -G "Visual Studio 17 2022" -D CMAKE_BUILD_TYPE={args.BuildType} -D BUILD_SHARED_LIBS:BOOL=TRUE -D SAMPLES_BUILD_WITH_LOCAL_VULKAN_HPP=ON -D SAMPLES_BUILD=ON -D TESTS_BUILD_WITH_LOCAL_VULKAN_HPP=ON -D TESTS_BUILD=ON'
    
    process = subprocess.run("cmake " + arguments, stdout=subprocess.PIPE, stderr=subprocess.PIPE, shell=True, universal_newlines=True)
    print(process.stdout)
    print(process.stderr)
    
    if process.returncode != 0:
        print(f"CMake return code {process.returncode}")
        sys.exit(1)
else:
    print("Incorrect BuildType arg")
    sys.exit(1)