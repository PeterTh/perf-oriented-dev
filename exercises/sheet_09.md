Exercise Sheet 9
================

A) Data Structure Benchmark Design and Implementation
-----------------------------------------------------

Create a benchmark setup which can measure a given set of mixes of insertion/deletion and read/write operations on different containers of arbitrary types and size. (Compare with the "The Dangers of Intuition" slide in the Optimization / Data Structures chapter)  
For the insertion/deletion and read/write categories, ensure a 50%/50% frequency each (i.e., after an even number of insertion/deletion operations the number of elements is the same as at the start). Also implement the requested instruction mix using the minimum spacing possible, that is, for a total of 100 instructions, a ratio of 20% ins/del and 80% read/write should be implemented as

```
read
write
read
write
insertion
read
write
read
write
deletion
... repeat x 10
```

rather than e.g.

```
read
write
... repeat x 40
insertion
deletion
... repeat x 10
```

Make sure to follow all the best practices regarding benchmark design which we outlined in the lecture, and try to avoid any perturbation unrelated to the effect we want to measure.


B) Array-like vs. Linked Lists
------------------------------

Apply your benchmark over the cross product of the following settings. Exclude combinations which would run out of memory.

**Data Structures**: Array, linked list

**Instruction Mix**:
| ins/del | read/write |
| -------:| ----------:|
|     0%  |      100%  |
|     1%  |       99%  |
|    10%  |       90%  |
|    50%  |       50%  |

**Element Size**: 8 Byte, 512 Byte, 8 MB

**Number of Elements**: 10, 1000, 100000, 10000000

Plot and discuss your results.

Submission
----------
Please submit your solutions by email to peter.thoman at UIBK, using the string "[Perf2023-sheet9]" in the subject line, before the start of the next VU at the latest.  
Try not to include attachments with a total size larger than 2 MiB.
