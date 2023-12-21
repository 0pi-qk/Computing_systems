#include <cstddef>
#include <omp.h>
#include "Random.h"

namespace OpenMP {
    void fill_matrix(double**, size_t, size_t);
    double** multiplication_matrix(double**, double**, size_t, size_t);
}
