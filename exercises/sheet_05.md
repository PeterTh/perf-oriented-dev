Exercise Sheet 5
================

Use the GCC 12 installation available in a module on LCC3 for this exercise (`gcc version 12.2.0 (Spack GCC)` / module `gcc/12.2.0-gcc-8.5.0-p4pe45v`).

For benchmarking, use both of our `larger_samples` testing programs, as well as `mmul`, `nbody`, `qap` and `delannoy`.
Use the following configurations:
```
mmul: default (S=1000)
nbody: M=400, others default
qap: chr15c.dat
delannoy: 13

npb_bt: W
ssca: 15
```

**NOTE**: You can query the available optimization options in GCC with  
```bash
gcc -Q --help=optimizers
```
This will also list their default setting. 
To get the setting of individual options at a given level of overall optimization, you can set that flag. E.g. you can use  
```bash
gcc -Q --help=optimizers -O2
```  
to see the default values at `-O2`.


A) Basic Optimization Levels
----------------------------

Benchmark each of the test cases at the `-O0`, `-O1`, `-O2`, `-O3`, `-Os` and `-Ofast` optimization levels.

Visualize and discuss the results.


B) Individual Compiler Optimizations
------------------------------------

Determine the set of compiler flags which changes when going from `-O2` to `-O3`. It is relatively small (at least compared to the total available amount of options).

Write a script or program which, starting from `-O2`, individually toggles these options to their `-O3` levels, trying all the options in turn and recording the resulting performance.

- Which of the options is the most meaningful for each of the programs?
- For the top 3 most impactful options across all test cases, read up on exactly what they do and try to reason about why they are effective for the given test cases.


C) Autotuning (optional)
------------------------

Extend your script to search for the best compiler configuration for each program.
The exact mechanism of this search is up to you.

Can you find a configuration for any of the programs which is better than any default (`-O*`) configuration to a statistically meaningful extent?


Submission
----------
Please submit your solutions by email to peter.thoman at UIBK, using the string "[Perf2024-sheet5]" in the subject line, before the start of the next VU at the latest.  
Try not to include attachments with a total size larger than 2 MiB.
