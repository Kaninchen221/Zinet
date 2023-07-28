import argparse
import os
import subprocess
import sys

parser = argparse.ArgumentParser(description='CMake Build')

parser.add_argument('--BuildType', type=str, help='Debug or Release', default='Debug')

args = parser.parse_args()

print('BuildType:', args.BuildType)

if args.BuildType == "Debug" or args.BuildType == "Release":
    
    profileFile = ""
    if args.BuildType == "Debug":
        profileFile = "conan_profile_windows_vs_debug.txt"
    else:
        profileFile = "conan_profile_windows_vs_release.txt"

    arguments = f'install . --profile Scripts\conan_profiles\{profileFile} --build=missing --install-folder=build'
    
    process = subprocess.run("conan " + arguments, stdout=subprocess.PIPE, stderr=subprocess.PIPE, shell=True, universal_newlines=True)
    print(process.stdout)
    print(process.stderr)
    
    if process.returncode != 0:
        print(f"Conan return code {process.returncode}")
        sys.exit(1)
else:
    print("Incorrect BuildType arg")
    sys.exit(1)