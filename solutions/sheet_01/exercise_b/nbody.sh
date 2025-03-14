#!/bin/bash

iterations=10
output_file=output/nbody_output.csv

cd ../../../small_samples/build
# create directory for output files if it does not exist
mkdir -p output
# create output file if it does not exist
if [ ! -f $output_file ]; then
    touch $output_file
fi

header="Wall clock time (m:s),CPU time (s),System time (s),Max memory usage (Kb)"
format="%E,%U,%S,%M"

echo $header > $output_file

# compile nbody with N, M, and L set
for i in $(seq 1 $iterations)
do
    values=$( /bin/time -f "$format" ./nbody 2>&1 | tr '\n' ',' )
    echo "$values" >> $output_file
done