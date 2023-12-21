#include "Single.h"

void Single::fill_matrix(double** m, size_t size) {
    for (size_t i = 0; i < size;i++)
        for (size_t j = 0; j < size; j++)
            m[i][j] = Random::get_rand_val_double();
}

double** Single::multiplication_matrix(double** m_1, double** m_2, size_t size){
    double** res = new double* [size];
    for (size_t i = 0; i < size; i++)
        res[i] = new double[size];

    for (size_t i = 0; i < size;i++)
        for (size_t j = 0; j < size; j++)
            for (size_t k = 0; k < size; k++)
                res[i][j] = m_1[i][k] * m_2[k][j];

    return res;
}