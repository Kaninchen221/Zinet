
# Deprecated but this repo contains functional vulkan renderer for 2D, Cpp code generator, cmake files generator 
# Next iteration of this project (Github actions, Debian support, Conan 2): https://github.com/Kaninchen221/Zinet2 

# Zinet

README is in TODO state

## Step by step first config
  + Install Conan 1.X the 2.X versions are not supported
  + Install Vulkan SDK 1.3
  + Install Python 3.X
  + Install min Visual Studio 2019
  + Install CMake 3.26.4
  + Clone repo
  + Run first_time.bat
  + Run generate_project_files.bat
  + Run conan_install.bat
  + Run build.py (optional --BuildType Debug\Release)
  + The solution file will be in the build folder

## FAQ
  + If you have some problem with "conan install" step then try "conan remove --locks"
