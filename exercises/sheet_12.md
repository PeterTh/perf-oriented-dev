Exercise Sheet 12 (final)
=========================

This exercise sheet about the Lua interpreter should be worked on **in groups**.  
Perform all benchmarks on LCC3.


A) Setup and Basic Execution
----------------------------

Get the latest stable baseline Lua interpreter sources here: https://www.lua.org/download.html
Compile it, and use it to run the benchmarks in `lua/fib.lua` ["the benchmark"], i.e:

```
lua perf-oriented-dev/lua/fib.lua
```

Note the timing results you get for these initial runs, we will use them as our baseline.


B) Profiling
------------

 * Apply a profiler of your choice to study the behaviour of the Lua interpreter while running the benchmark.
 * Is the result sufficient to base optimization decisions on? Why? If not, use other tools or manually track and report additional information about the execution.

Report and discuss your results.


C) Code Understanding
---------------------

 * Describe the overall process of Lua execution in the interpreter. What are the major phases, and how much time do they take for the benchmark?
 * What does the option `LUA_USE_JUMPTABLE` do? Measure its performance impact on the benchmark.


D) Optimization
---------------

Optimize the Lua interpreter to more efficiently execute the benchmark.  
Valid strategies include:

 * Compiler optimizations or hints
 * Any manual procedural or algorithmic optimizations
 * Making suitable assumptions / implementing heuristics based on the properties of the benchmark

**Invalid** strategies are:

 * Anything which checks the source code (or its hash etc) against a table of pre-built or pre-optimized solutions
 * Anything which touches the input program

Your tuned interpreters' best times for all 3 benchmarks will be compared against all other groups' times.


Submission
----------
Please submit your solutions by email to peter.thoman at UIBK, using the string "[Perf2024-sheet12]" in the subject line, before the start of the next VU at the latest.
Include your group composition in the email.  
Try not to include attachments with a total size larger than 2 MiB.
