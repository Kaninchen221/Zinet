import os
import subprocess
import sys

os.chdir("build/bin")

for file in os.listdir():
    if file.endswith(".exe"):
        #os.system(file)
        result = subprocess.run(file, capture_output=True)

        if result.returncode != 0:
            print(f"Process {file} return code {result.returncode}")
            sys.exit(1)