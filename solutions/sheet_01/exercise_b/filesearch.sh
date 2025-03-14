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

dirs=( 1 5 10 )
files=( 10 100 1000 )
file_size=1024
for i in $(seq 1 $iterations)
do
    for dir in "${dirs[@]}"
    do
        for file in "${files[@]}"
        do
            ./filegen $dir $files $file_size $file_size
            values=$( /bin/time -f "$format" ./filesearch $dir $files $file_size $file_size 2>&1 | tr '\n' ',' )
            echo "$dir - $file - $file_size,$values" >> $output_file
        done
    done
done
rm -rf generated