import os
import subprocess
import sys

os.chdir("build/bin")

for file in os.listdir():
    if file.endswith(".exe") and file.find("Unit") != -1:
        process = subprocess.run(file, stdout=subprocess.PIPE, stderr=subprocess.PIPE, shell=True, universal_newlines=True)
        print(process.stdout)
        print(process.stderr)

        if process.returncode != 0:
            print(f"Process {file} return code {process.returncode}")
            sys.exit(1)