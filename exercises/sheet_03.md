Exercise Sheet 3
================

A) Traditional profiling
------------------------

In `larger_samples/npb_bt` you find a somewhat larger C program. There are 5 variants generated at compile time, named `_s`, `_w`, `_a`, `_b`, `_c`, representing successively larger workloads in this order.

Use traditional profiling with `gprof` in order to gain insight into the CPU time distribution of this program, on both your own hardware and LCC3, for at least 2 different workload sizes.

Summarize, interpret and report your findings.


B) Hybrid trace profiling
-------------------------

Use the Tracy profiler to profile the same application. Think about what might be a good mapping for the concept of a "frame" in the context of the given program. Also annotate all functions or individual code regions which seem interesting (e.g. based on the traditional flat profile).

Try to measure the overhead of both gprof and Tracy, compared to the native execution without any profiling information.

You do not necessarily need to do this on LCC3, but can do so for extra clout.


Submission
----------
Please submit your solutions by email to peter.thoman at UIBK, using the string "[Perf2024-sheet3]" in the subject line, before the start of the next VU at the latest.  
Try not to include attachments with a total size larger than 2 MiB.
