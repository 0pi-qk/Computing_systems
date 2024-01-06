#include <iostream>
#include <cassert>
#include <omp.h>
#include "MPI_calculations.h"

using namespace std;

int main(int argc, char *argv[]) {

    MPI_Init(&argc, &argv);

    int rank, size;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    const int matrixSize = atoi(argv[1]);

    if (matrixSize % size != 0) {
        if (rank == 0) {
            cout << "Размер матрицы должен быть кратен количеству процессов(" << size << ")!" << endl;
        }
        MPI_Finalize();
        return 1;
    }

    double **m_A = Matrix::init_matrix(matrixSize);
    double **m_B = Matrix::init_matrix(matrixSize);

    double start;
    //MPI
    start = omp_get_wtime();

    double **MPI_res = MPI::perform_multiplication_matrix(m_A, m_B, rank, size, matrixSize);
    if (rank == 0)
    	cout << "MPI -> " << omp_get_wtime() - start << "     [ size - " << matrixSize << " ]" << endl;

    MPI_Finalize();

    Matrix::clear_matrix(m_A, size);
    Matrix::clear_matrix(m_B, size);
    Matrix::clear_matrix(MPI_res, size);

    return 0;
}
