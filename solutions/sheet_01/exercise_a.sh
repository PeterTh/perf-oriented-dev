#!/bin/bash

cd ../../small_samples

mkdir build
cd build
cmake .. -G Ninja -DCMAKE_BUILD_TYPE=Release
ninja

echo -e "\nDelannoy"
/bin/time ./delannoy 12

echo -e "\nFilegen"
/bin/time ./filegen 10 100 100 100

echo -e "\nFilesearch"
/bin/time ./filesearch

echo -e "\nMmul"
/bin/time ./mmul

echo -e "\nNbody"
/bin/time ./nbody

echo -e "\nQap"
/bin/time ./qap ../qap/problems/chr15a.dat