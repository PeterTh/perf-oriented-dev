#!/bin/bash

iterations=10
output_file=output/delannoy_output.csv

cd ../../../small_samples/build
# create directory for output files if it does not exist
mkdir -p output
# create output file if it does not exist
if [ ! -f $output_file ]; then
    touch $output_file
fi

touch $output_file

header="Args,Wall clock time (m:s),CPU time (s),System time (s),Max memory usage (Kb)"
format="%E,%U,%S,%M"

echo $header > $output_file

inputs=( 11 12 13 )
for i in $(seq 1 $iterations)
do
    for input in "${inputs[@]}"
    do
        values=$( /bin/time -f "$format" ./delannoy $input 2>&1 | tr '\n' ',' )
        echo "$input,$values" >> $output_file
    done
done