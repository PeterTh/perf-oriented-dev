```
CPU: 12-core 13th Gen Intel Core i7-13700KF (-MT MCP-) speed: 3418 MHz
Kernel: 5.15.133.1-microsoft-standard-WSL2 x86_64 Up: 19m
Mem: 2026.2/15911.5 MiB (12.7%) Storage: 1 TiB (83.2% used) Procs: 26
Shell: Bash inxi: 3.3.13
```

### Exercise 1

delannoy.c is a program that calculates the Delannoy number, which represents the number of paths from (0,0) to (m,n) in a grid, only moving right, up, or diagonally right and up.

```
/bin/time ./delannoy 15
Verification: OK
33.05user 0.00system 0:33.05elapsed 100%CPU (0avgtext+0avgdata 1488maxresident)k
0inputs+0outputs (0major+68minor)pagefaults 0swaps
```

nbody.c is a program that simulates the gravitational forces between a collection of celestial bodies, updating their positions and velocities over time.

```
/bin/time ./nbody
Verification: OK
0.27user 0.00system 0:00.27elapsed 100%CPU (0avgtext+0avgdata 1892maxresident)k
0inputs+0outputs (0major+99minor)pagefaults 0swaps
```

MMult is a program that multiplies two matrices of size `n`x`n`. 

```
/bin/time ./mmul 
Verification: OK
0.68user 0.00system 0:00.68elapsed 99%CPU (0avgtext+0avgdata 24448maxresident)k
0inputs+0outputs (0major+1336minor)pagefaults 0swaps
```

filesearch is a program that searches the largest file in the current directory.

```
/bin/time ./filesearch
The largest file is ./CMakeFiles/CMakeOutput.log with size 45224 bytes
0.00user 0.00system 0:00.00elapsed 86%CPU (0avgtext+0avgdata 1608maxresident)k
0inputs+0outputs (0major+75minor)pagefaults 0swaps
```

filegen.c is a program that generates a specified number of directories and files, with each file's size randomly determined within a given minimum and maximum range, using a provided seed for the random number generator.

```
 /bin/time ./filegen 1000 1000 5000 7000 1
61.04user 15.57system 1:16.65elapsed 99%CPU (0avgtext+0avgdata 1632maxresident)k
0inputs+16000000outputs (0major+74minor)pagefaults 0swaps
```