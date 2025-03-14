#!/bin/bash

iterations=10
output_file=output/filesearch_output.csv

cd ../../../small_samples/build
# create directory for output files if it does not exist
mkdir -p output
# create output file if it does not exist
if [ ! -f $output_file ]; then
    touch $output_file
fi

header="Args,Wall clock time (m:s),CPU time (s),System time (s),Max memory usage (Kb)"
format="%E,%U,%S,%M"

echo $header > $output_file

dir=10
files=( 1 10 100 )
min_size=512
max_size=2048
for i in $(seq 1 $iterations)
do
    for file in "${files[@]}"
    do
        ./filegen $dir $files $min_size $max_size
        values=$( /bin/time -f "$format" ./filesearch 2>&1 | tr '\n' ',' )
        echo "$dir - $file - $min_size - $max_size,$values" >> $output_file
    done
done
rm -rf generated