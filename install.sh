#!/bin/bash
mkdir Release
cd Release || exit
cmake -DCMAKE_BUILD_TYPE=Release ..
make
