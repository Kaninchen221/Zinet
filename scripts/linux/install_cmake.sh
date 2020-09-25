#!/bin/bash
cd ../../
DEPS_DIR="${TRAVIS_BUILD_DIR}/deps"
mkdir ${DEPS_DIR} && cd ${DEPS_DIR}
wget --no-check-certificate https://github.com/Kitware/CMake/releases/download/v3.18.3/cmake-3.18.3-Linux-x86_64.tar.gz
tar -xvf cmake-3.18.3-Linux-x86_64.tar.gz > /dev/null
mv cmake-3.18.3-Linux-x86_64 cmake-install
PATH=${DEPS_DIR}/cmake-install:${DEPS_DIR}/cmake-install/bin:$PATH
cd ${TRAVIS_BUILD_DIR}