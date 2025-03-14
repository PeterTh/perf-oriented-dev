#!/bin/bash

iterations=10
output_file=output/filegen_output.csv

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

# dirs=( 1 5 10 )
# files=( 10 100 1000 )
# min_size=1024
# max_size=100000
# for i in $(seq 1 $iterations)
# do
#     for dir in "${dirs[@]}"
#     do
#         for file in "${files[@]}"
#         do
#             values=$( /bin/time -f "$format" ./filegen $dir $file $min_size $max_size 2>&1 | tr '\n' ',' )
#             echo "$dir - $file - $min_size - $max_size,$values" >> $output_file
#         done
#         # remove generated folder and its content
#     done
# done
# rm -rf generated