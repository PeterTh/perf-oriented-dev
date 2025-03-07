Exercise Sheet 10
=================

This exercise sheet should be worked on in groups.  
Perform all benchmarks on LCC3, using the benchmark structure defined in sheet 9.


A) Unrolled Linked Lists
------------------------

Implement an "unrolled linked list" data structure (i.e. a linked list of potentially partially empty fixed-size chunks). Evaluate different chunk sizes, and benchmark it compared to arrays and standard linked lists.


B) Tiered Arrays
----------------

Implement a "tiered array" data structure (i.e. a fixed set of indirection layers [at minimum one] which links to chunks of an array). Evaluate different configurations, and benchmark it compared to arrays and standard linked lists.


C) Extended Benchmarking
------------------------

Extend the list benchmark setup with an option to use a random access pattern (make sure to minimize the overhead of selecting the random locations, e.g. by precomputing them!).

Evaluate and plot how this change affects the performance of the two baselines (arrays and linked lists) as well as your new, more complex data structures.


Submission
----------
Please submit your solutions by email to peter.thoman at UIBK, using the string "[Perf2025-sheet10]" in the subject line, before the start of the next VU at the latest.
Include your group composition in the email.  
Try not to include attachments with a total size larger than 2 MiB.
