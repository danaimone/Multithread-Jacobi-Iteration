#!/bin/bash
bash -c '[ -d build ] && rm -r build'
mkdir build
cd build || exit
cmake -DCMAKE_BUILD_TYPE=build ..
make
