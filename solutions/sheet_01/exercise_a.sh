#!/bin/bash

cd ../../small_samples

mkdir build
cd build
cmake .. -G Ninja -DCMAKE_BUILD_TYPE=Release
ninja

echo -e "\nDelannoy"
/bin/time -v ./delannoy 12

echo -e "\nFilegen"
/bin/time -v ./filegen 1 100 100 100

echo -e "\nFilesearch"
/bin/time -v ./filesearch

echo -e "\nMmul"
/bin/time -v ./mmul

echo -e "\nNbody"
/bin/time -v ./nbody

echo -e "\nQap"
/bin/time -v ./qap ../qap/problems/chr15a.dat