#include <cstddef>
#include <pthread.h>
#include "Random.h"

namespace Pthread {
    void fill_matrix(double**, size_t, size_t);
    void* fill_matrix_worker(void*);
    double** multiplication_matrix(double**, double**, size_t, size_t);
    void* multiplication_matrix_worker(void*);
}
