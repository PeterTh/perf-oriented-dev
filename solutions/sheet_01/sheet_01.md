# Sheet 01
Emanuele Goldin, Claudio Nardin

## Preparation

### delannoy
#### Input

- At least a positive number \< 23
- Additional args seem to be ignored \[+t\]

#### Scalability
- The workload can be scaled with the input and scales exponentially with base 3 since the delannoy function makes 3 recursive calls to itself.

#### Measurement

We selected the midpoint in the allowed range from 0 to 22

```sh
/bin/time delannoy 12
Verification: OK
        Wall clock time: 0:00.38
        CPU time: 0.37
        System time: 0.00
        Max memory usage: 1484 Kb
```


### filegen
#### Input

- Allows 4 or 5 arguments as an input (seed is optional)
- <num_directories> <num_files_per_directory> <min_file_size> <max_file_size> [\<seed>]

#### Scalability
- The workload scales with the <num_directories> * <num_files_per_directory> * a random file size between the <min_file_size> and <max_file_size>
- For this reason it makes sense to make <min_file_size> = <max_file_size>


### filesearch
#### Input

- Doesn't require any input arguments

#### Scalability
- The programm searches for the largest file in the current directory and all subdirectories. 
- Therefore the workload can be scaled by the amount of files in the directory and subdirectories

#### Measurement

We selected 100 100 100 100 as input. With a single directory the execution was too fast to be captured by `bin/time`

```sh
/bin/time filegen 100 100 100 100
        Wall clock time: 0:00.59
        CPU time: 0.01
        System time: 0.55
        Max memory usage: 1724 Kb
```

### mmul
#### Input

- Doesn't require any input arguments

#### Scalability
- The programm creates matrices with the predefined dimensions S*S (S=1000) and performes a matrix multiplication between them.
- The workload can therefore only be changed, by modifying the program itself. 

#### Measurement

```sh
/bin/time mmul
Verification: OK
        Wall clock time: 0:01.90
        CPU time: 1.86
        System time: 0.00
        Max memory usage: 24556 Kb
```

### nbody
#### Input

- Doesn't require any input arguments
- However the parameters N, M and L can be set through the environment
- N is the number of particles, whereas L determines the number of movable particles.

#### Scalability
- N - the number of particles
- M - number of iterations
- L - number of movable particles

#### Measurement

We kept the default (1000 particles, 100 iterations) since it seems relevant enough.

```sh
/bin/time nbody
Verification: OK
        Wall clock time: 0:00.85
        CPU time: 0.84
        System time: 0.00
        Max memory usage: 2052 Kb
```
The workload scales with M * N * min(N, L)

### qap
#### Input

- An argument is optional and determines the path to the dataset
- If no argument is provided the file "problems/chr10a.dat" is used per default
- Additional args seem to be ignored \[+t\]

#### Scalability
- The scalability of the workload is dependent on the size of the data set that contains the problem that needs to be solved. 

#### Measurement

We selected the problem _chr15a.dat_ after trying them out (sensible execution time)

```sh
/bin/time qap ../qap/problems/chr15a.dat
Loading Problem File ../qap/problems/chr15a.dat ..
  - problem size: 15
  - optimum: 9896
Run solver ...
Done!
Best Result: 9896
Verification: OK
        Wall clock time: 0:02.81
        CPU time: 2.77
        System time: 0.00
        Max memory usage: 1704 Kb
```

## Experiment

