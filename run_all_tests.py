import os

os.chdir("build/bin")

for file in os.listdir():
    if file.endswith(".exe"):
        os.system(file)