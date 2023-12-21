#include "IntelTBB.h"

void TBB::fill_matrix(double** m, size_t size, size_t threads) {
    std::size_t chunk_size;

    if (size > threads) {
        chunk_size = size / threads;
    } else {
        chunk_size = 1;
    }

    tbb::parallel_for(
        tbb::blocked_range<std::size_t>(0, size, chunk_size),
        [m, size] (tbb::blocked_range<std::size_t> range) noexcept -> void {
            for (std::size_t i = range.begin(); i < range.end(); i++) {
                for (int j = 0; j < size; j++) {
                    m[i][j] = Random::get_rand_val_double();
                }
            }
        }
    );
}

double** TBB::multiplication_matrix(double** m_1, double** m_2, size_t size, size_t threads){
    std::size_t chunk_size;

    if (size > threads) {
        chunk_size = size / threads;
    } else {
        chunk_size = 1;
    }

    double** res = new double* [size];

    tbb::parallel_for(
        tbb::blocked_range<std::size_t>(0, size, chunk_size),
        [res, size] (tbb::blocked_range<std::size_t> range) noexcept -> void {
            for (std::size_t i = range.begin(); i < range.end(); i++) {
                res[i] = new double[size];
            }
        }
    );

    tbb::parallel_for(
        tbb::blocked_range<std::size_t>(0, size, chunk_size),
        [m_1, m_2, res, size] (tbb::blocked_range<std::size_t> range) noexcept -> void {
            for (std::size_t i = range.begin(); i < range.end(); i++) {
                for (int j = 0; j < size; j++) {
                    for (int k = 0; k < size; k++) {
                        res[i][j] = m_1[i][k] * m_2[k][j];
                    }
                }
            }
        }
    );

    return res;
}