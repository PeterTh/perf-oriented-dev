#!/bin/bash

iterations=10
output_file_1=output/qap_sizes_output.csv
output_file_2=output/qap_structures_output.csv

cd ../../../small_samples/build
# create directory for output files if it does not exist
mkdir -p output
# create output file if it does not exist
if [ ! -f $output_file ]; then
    touch $output_file
fi

header="Args,Wall clock time (m:s),CPU time (s),System time (s),Max memory usage (Kb)"
format="%E,%U,%S,%M"

echo $header > $output_file_1
echo $header > $output_file_2

input_sizes=("../qap/problems/chr10a.dat" "../qap/problems/chr12a.dat" "../qap/problems/chr15a.dat")
input_structures=("../qap/problems/chr15a.dat" "../qap/problems/chr15b.dat" "../qap/problems/chr15c.dat")

# qap sizes
for i in $(seq 1 $iterations); do
    for input in "${input_sizes[@]}"; do
        values=$( /bin/time -f "$format" ./qap $input 2>&1 | tr '\n' ',' )
        echo "$input,$values" >> $output_file_1
    done
done

# qap structures
for i in $(seq 1 $iterations); do
    for input in "${input_structures[@]}"; do
        values=$( /bin/time -f "$format" ./qap $input 2>&1 | tr '\n' ',' )
        echo "$input,$values" >> $output_file_2
    done
done