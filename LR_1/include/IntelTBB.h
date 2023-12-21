#include <cstddef>
#include <tbb/tbb.h>
#include "Random.h"

namespace TBB {
    void fill_matrix(double**, size_t, size_t);
    double** multiplication_matrix(double**, double**, size_t, size_t);
}
