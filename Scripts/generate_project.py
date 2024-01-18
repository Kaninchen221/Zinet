import argparse
import os
import subprocess
import sys

from zinet_utilities.paths import find_zinet_root_path

parser = argparse.ArgumentParser(description='Generate project files')
parser.add_argument('--AddressSanitizer', type=str, help='true or false', default='false')
args = parser.parse_args()

if args.AddressSanitizer != "true" or args.AddressSanitizer != "false":
    zinet_root_path = find_zinet_root_path()
    print(f"Zinet root path: {zinet_root_path}")

    build_folder_path = zinet_root_path / "build"
    print(f"Build folder path: {build_folder_path}")

    args = f"-m zinet_generator --AddressSanitizer {args.AddressSanitizer}"
    process = subprocess.run("python " + args, stdout=subprocess.PIPE, stderr=subprocess.PIPE, shell=True,
                             universal_newlines=True)
    print(process.stdout)
    print(process.stderr)

    if process.returncode != 0:
        print(f"Generate project files return code {process.returncode}")
        sys.exit(1)
else:
    print("Incorrect AddressSanitizer arg")
    sys.exit(1)
