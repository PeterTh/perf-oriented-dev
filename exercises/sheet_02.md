Exercise Sheet 2
================

**Don't run either of these two exercises on the LCC3 headnode!**

A) External CPU load
--------------------

Have a look at `loadgen` in the tools folder.  
Use it (e.g. `exec_with_workstation_heavy.sh`) to generate external load while benchmarking and track the changes this causes to your measured performance metrics.

Improve your experiment setup/script from the first exercise to dynamically adjust the number of repetitions performed until some statistical confidence interval is reached, and present your results.


B) External I/O load
--------------------

Create a load generator which produces a configurable I/O load on the file system.  
Document its working principle, and demonstrate its impact on the speed of the I/O-bound benchmarks in `small_samples`.

**On the cluster, use the local file system for all FS benchmarking!**  
Do **not** use `/home` or `/scratch`.

Submission
----------
Please submit your solutions by email to peter.thoman at UIBK, using the string "[Perf2025-sheet2]" in the subject line, before the start of the next VU at the latest.  
Try not to include attachments with a total size larger than 2 MiB.
