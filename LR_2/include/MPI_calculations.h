#include <cstddef>
#include <mpi.h>
#include "matrix.h"
#include "Random.h"

namespace MPI {
    void fill_matrix(double**, int);
    double** multiplication_matrix(double**, double**, int, int, int);
    double** perform_multiplication_matrix(double**, double**, int, int, int);
}
