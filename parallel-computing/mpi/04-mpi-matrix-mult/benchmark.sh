#! /usr/bin/env bash
for numprocs in 1 2 4 5 8 10 20 50 100; do
    echo "Now run \"mpirun -n ${numprocs} ./mpi_matrix_mult 1000\""
    mpirun -n $numprocs ./mpi_matrix_mult 1000 2>/dev/null
done
echo "Now run \"./ordinary_matrix_mult 1000\""
./ordinary_matrix_mult 1000

