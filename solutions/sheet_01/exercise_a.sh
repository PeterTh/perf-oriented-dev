#!/bin/bash

cd ../../small_samples

mkdir build
cd build
cmake .. -G Ninja -DCMAKE_BUILD_TYPE=Release
ninja

# output only measurment we are interested in
format="\tWall clock time: %E\n\tCPU time: %U\n\tSystem time: %S\n\tMax memory usage: %M Kb"

echo -e "\nDelannoy"
/bin/time -f "$format" ./delannoy 12

echo -e "\nFilegen"
/bin/time -p -f "$format" ./filegen 100 100 100 100

# too fast to measure --> added -p flag
echo -e "\nFilesearch"
/bin/time -p -f "$format" ./filesearch

echo -e "\nMmul"
/bin/time -f "$format" ./mmul

echo -e "\nNbody"
/bin/time -f "$format" ./nbody

echo -e "\nQap"
/bin/time -f "$format" ./qap ../qap/problems/chr15a.dat