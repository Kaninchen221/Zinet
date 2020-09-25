#!/bin/bash
chmod 777 scripts/linux/*.sh

scripts/linux/install_cmake.sh
scripts/linux/dependencies.sh

mkdir build
cd build
cmake ../ -G "Unix Makefiles"
cd ..