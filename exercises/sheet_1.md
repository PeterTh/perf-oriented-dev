Exercise Sheet 1
================

A) Preparation
-------------- 

Take a look at the programs in `small_samples`. Build them, determine how to run each program, what parameters it needs and how they are set, and how the workload can be scaled.

For each program, measure the real (wall clock) time, CPU time, system time and maximum memory usage for specific executions. Empirically select a suitable set of execution parameters for each program.
Document your results, and provide an argument for why you chose a specific set of parameters.

> *Hint*  
> The program `/bin/time` can provide all the requested metrics.

B) Experiments
--------------

Create a simple automated experiment setup, e.g. using your favourite scripting language. All program should be executed, each with a specified number of repetitions, and the output should include the mean of the requested performance metrics, as well as the variance. All raw data should also be stored in a structured fashion for later use.

Provide the results for each benchmark, both on one of your personal compute platforms (describe it!) as well as on the LCC2 cluster.
