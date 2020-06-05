#!/usr/bin/env bash

IFS='' read -r -d '' HELLO_MPI_TXT << EOF
#include <boost/mpi.hpp>
#include <iostream>

int main(int argc, char *argv[]) {
  boost::mpi::environment env{argc, argv};
  boost::mpi::communicator world;
  std::cout << world.rank() << ", " << world.size() << '\n';
}
EOF

set -e

SYSROOT_DIR=/opt/apollo/sysroot
mpi_test_cpp="$(mktemp /tmp/hello.XXXXXX.cpp)"
echo "${HELLO_MPI_TXT}" > "${mpi_test_cpp}"
${SYSROOT_DIR}/bin/mpic++ "${mpi_test_cpp}" -o hello_mpi \
	-L${SYSROOT_DIR}/lib \
	-lboost_mpi

${SYSROOT_DIR}/bin/mpirun -np 2 ./hello_mpi
rm -rf hello_mpi
