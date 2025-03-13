# Sheet 01
Emanuele Goldin, Claudio Nardin

## delannoy
### Input

- At least a positive number \< 23
- Additional args seem to be ignored \[+t\]

### Scalability
- The workload can be scaled with the input and scales exponentially with base 3 since the delannoy function makes 3 recursive calls to itself.

## filegen
### Input

- Allows 4 or 5 arguments as an input (seed is optional)
- <num_directories> <num_files_per_directory> <min_file_size> <max_file_size> [\<seed>]

### Scalability
- The workload scales with the <num_directories> * <num_files_per_directory> * a random file size between the <min_file_size> and <max_file_size>
- For this reason it makes sense to make <min_file_size> = <max_file_size>


## filesearch
### Input

- Doesn't require any input arguments

### Scalability
- The programm searches for the largest file in the current directory and all subdirectories. 
- Therefore the workload can be scaled by the amount of files in the directory and subdirectories

## mmul
### Input

- Doesn't require any input arguments

### Scalability
- The programm creates matrices with the predefined dimensions S*S (S=1000) and performes a matrix multiplication between them.
- The workload can therefore only be changed, by modifying the program itself. 

## nbody
### Input

- Doesn't require any input arguments
- However the parameters N, M and L can be set through the environment
- N is the number of particles, whereas L determines the number of movable particles.


### Scalability
- N - the number of particles
- M - number of iterations
- L - number of movable particles

The workload scales with M * N * min(N, L)


## qap
### Input

- An argument is optional and determines the path to the dataset
- If no argument is provided the file "problems/chr10a.dat" is used per default
- Additional args seem to be ignored \[+t\]

### Scalability
- The scalability of the workload is dependent on the size of the data set that contains the problem that needs to be solved.  