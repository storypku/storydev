# Simple summation using MPI

## Problem Description

Calculate the sum of numbers in range [1, 1000] using MPI.

```
1 + 2 + 3 + ... + 1000 = 500500
```

## How To Run

1. Make sure you have `mpicc` installed.

On Ubuntu 18.04, you can install it via

```
sudo apt-get install mpich
```

Or build it from source. [MPICH Download Page](https://www.mpich.org/downloads/)

2. Type `make`

3. Type `make mpi_run`. Or

```
mpirun -n 10 ./mpi_sum_opt
```
