#!/bin/bash
chmod 777 scripts/linux/*.sh

./scripts/linux/dependencies.sh

mkdir build
cd build
cmake ../ -G "Unix Makefiles" -DCMAKE_BUILD_TYPE:STRING=Debug -DBUILD_SHARED_LIBS:BOOL=TRUE -DZINET_LIBS_TYPE:STRING=STATIC
cd ..