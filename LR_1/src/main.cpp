#include <iostream>
#include <cstring>
#include <cassert>
#include <sstream>
#include "matrix.h"
#include "Single.h"
#include "OpenMP.h"
#include "POSIXthread.h"
#include "IntelTBB.h"

using namespace std;

size_t to_size_t(const char* arg) {
    stringstream stream(arg);
    size_t result;
    stream >> result;

    return result;
}

int main(int argc, char const *argv[]) {
    size_t size = to_size_t(argv[1]);
    size_t n_threads = to_size_t(argv[2]);

    cout << endl << "Size: " <<  size << ";   Num threads: " << n_threads << endl;

    double **m_A = Matrix::init_matrix(size);
    double **m_B = Matrix::init_matrix(size);

    double start;
    //Single
    start = omp_get_wtime();

    Single::fill_matrix(m_A, size);
    Single::fill_matrix(m_B, size);

    double **Single_res = Single::multiplication_matrix(m_A, m_B, size);

    cout << "Single -> " << omp_get_wtime() - start << endl;

    //OpenMP
    start = omp_get_wtime();

    OpenMP::fill_matrix(m_A, size, n_threads);
    OpenMP::fill_matrix(m_B, size, n_threads);

    double **OpenMP_res = OpenMP::multiplication_matrix(m_A, m_B, size, n_threads);

    cout << "OpenMP -> " << omp_get_wtime() - start << endl;

    //pthread
    start = omp_get_wtime();

    Pthread::fill_matrix(m_A, size, n_threads);
    Pthread::fill_matrix(m_B, size, n_threads);

    double **Pthread_res = Pthread::multiplication_matrix(m_A, m_B, size, n_threads);

    cout << "Pthread -> " << omp_get_wtime() - start << endl;

    //TBB
    start = omp_get_wtime();

    TBB::fill_matrix(m_A, size, n_threads);
    TBB::fill_matrix(m_B, size, n_threads);

    double **TBB_res = TBB::multiplication_matrix(m_A, m_B, size, n_threads);

    cout << "TBB -> " << omp_get_wtime() - start << endl;

    Matrix::clear_matrix(m_A, size);
    Matrix::clear_matrix(m_B, size);
    Matrix::clear_matrix(Single_res, size);
    Matrix::clear_matrix(OpenMP_res, size);
    Matrix::clear_matrix(Pthread_res, size);
    Matrix::clear_matrix(TBB_res, size);

    return 0;
}