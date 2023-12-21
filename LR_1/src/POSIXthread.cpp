#include "POSIXthread.h"

struct FillMatrixArgs {
    double** m;
    size_t size;
    size_t chunk_size;
    size_t tid;
};

struct multiplicationMatrixArgs {
    double** m_1;
    double** m_2;
    double** res;
    size_t size;
    size_t chunk_size;
    size_t tid;
};

void Pthread::fill_matrix(double** m, size_t size, size_t threads) {
    size_t chunk_size;
    size_t rest_chunk_size;

    if (size > threads) {
        chunk_size = size / threads;
        rest_chunk_size = size % threads;
    } else {
        threads = size;
        chunk_size = 1;
        rest_chunk_size = 0;
    }

    auto* pthreads = new pthread_t[threads];
    auto* pthreads_args = new FillMatrixArgs[threads];

    for (size_t tid = 0; tid < threads; tid++) {
        pthreads_args[tid] = (FillMatrixArgs){
            .m = m,
            .size = size,
            .chunk_size = chunk_size,
            .tid = tid
        };

        pthread_create(&pthreads[tid], nullptr, fill_matrix_worker, &pthreads_args[tid]);
    }

    for (size_t i = size - rest_chunk_size; i < size; i++)
        for (size_t j = 0; j < size; j++)
            m[i][j] = Random::get_rand_val_double();


    for (size_t tid = 0; tid < threads; tid++)
        pthread_join(pthreads[tid], nullptr);

    delete[] pthreads;
    delete[] pthreads_args;
}

void* Pthread::fill_matrix_worker(void* args) {
    FillMatrixArgs fill_matrix_args = *(FillMatrixArgs*)args;
    double** m = fill_matrix_args.m;
    size_t size = fill_matrix_args.size;
    size_t chunk_size = fill_matrix_args.chunk_size;
    size_t tid = fill_matrix_args.tid;

    size_t start = tid * chunk_size;
    size_t end = start + chunk_size;

    for (size_t i = start; i < end; i++)
        for (size_t j = 0; j < size; j++)
            m[i][j] = Random::get_rand_val_double();

    return nullptr;
}

double** Pthread::multiplication_matrix(double** m_1, double** m_2, size_t size, size_t threads){
    double** res = new double* [size];
    for (size_t i = 0; i < size; i++)
        res[i] = new double[size];

    size_t chunk_size;
    size_t rest_chunk_size;

    if (size > threads) {
        chunk_size = size / threads;
        rest_chunk_size = size % threads;
    } else {
        threads = size;
        chunk_size = 1;
        rest_chunk_size = 0;
    }

    auto* pthreads = new pthread_t[threads];
    auto* pthreads_args = new multiplicationMatrixArgs[threads];

    for (size_t tid = 0; tid < threads; tid++) {
        pthreads_args[tid] = (multiplicationMatrixArgs){
            .m_1 = m_1,
            .m_2 = m_2,
            .res = res,
            .size = size,
            .chunk_size = chunk_size,
            .tid = tid
        };

        pthread_create(&pthreads[tid], nullptr, multiplication_matrix_worker, &pthreads_args[tid]);
    }

    for (size_t i = size - rest_chunk_size; i < size; i++)
        for (size_t j = 0; j < size; j++)
            for (size_t k = 0; k < size; k++)
                res[i][j] = m_1[i][k] * m_2[k][j];

    for (size_t tid = 0; tid < threads; tid++)
        pthread_join(pthreads[tid], nullptr);

    delete[] pthreads;
    delete[] pthreads_args;

    return res;
}

void* Pthread::multiplication_matrix_worker(void* args) {
    multiplicationMatrixArgs multiplication_matrix_args = *(multiplicationMatrixArgs*)args;
    double** m_1 = multiplication_matrix_args.m_1;
    double** m_2 = multiplication_matrix_args.m_2;
    double** res = multiplication_matrix_args.res;
    size_t size = multiplication_matrix_args.size;
    size_t chunk_size = multiplication_matrix_args.chunk_size;
    size_t tid = multiplication_matrix_args.tid;

    size_t start = tid * chunk_size;
    size_t end = start + chunk_size;

    for (size_t i = start; i < end; i++)
        for (size_t j = 0; j < size; j++)
            for (size_t k = 0; k < size; k++)
                res[i][j] = m_1[i][k] * m_2[k][j];

    return nullptr;
}