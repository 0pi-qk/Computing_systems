#include "OpenMP.h"

void OpenMP::fill_matrix(double** m, size_t size, size_t threads) {
#pragma omp parallel for shared(size, m) num_threads(threads) default(none)
    for (size_t i = 0; i < size;i++)
        for (size_t j = 0; j < size; j++)
            m[i][j] = Random::get_rand_val_double();
}

double** OpenMP::multiplication_matrix(double** m_1, double** m_2, size_t size, size_t threads){
    double** res = new double* [size];

    #pragma omp parallel for shared(res, size) num_threads(threads) default(none)
    for (size_t i = 0; i < size; i++)
        res[i] = new double[size];

    #pragma omp parallel for shared(m_1, m_2, res, size) num_threads(threads) default(none)
    for (size_t i = 0; i < size;i++)
        for (size_t j = 0; j < size; j++)
            for (size_t k = 0; k < size; k++)
                res[i][j] = m_1[i][k] * m_2[k][j];

    return res;
}