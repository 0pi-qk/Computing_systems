#include "MPI_calculations.h"

void MPI::fill_matrix(double** m, int matrixSize) {
    for (size_t i = 0; i < matrixSize; i++)
        for (size_t j = 0; j < matrixSize; j++)
            m[i][j] = Random::get_rand_val_double();
}

double** MPI::multiplication_matrix(double** m_1, double** m_2, int matrixSize, int start, int end) {
    double** res = Matrix::init_matrix(matrixSize);

    for (size_t i = start; i < end; i++)
        for (size_t j = 0; j < matrixSize; j++) {
            res[i][j] = 0;

            for (size_t k = 0; k < matrixSize; k++)
                res[i][j] += m_1[i][k] * m_2[k][j];
        }

    return res;
}

double** MPI::perform_multiplication_matrix(double** m_1, double** m_2, int rank, int size, int matrixSize) {

    char processor_name[MPI_MAX_PROCESSOR_NAME];
    int name_len;
    MPI_Get_processor_name(processor_name, &name_len);

    // cout << "Process " << rank + 1 << " / " << size << " is running on " << processor_name << endl;

    double** result = Matrix::init_matrix(matrixSize);

    MPI::fill_matrix(m_1, matrixSize);
    MPI::fill_matrix(m_2, matrixSize);

    int per_process = matrixSize / size;
    int start = rank * per_process;
    int end = (rank + 1) * per_process;

    double** local_result = MPI::multiplication_matrix(m_1, m_2, matrixSize, start, end);

    MPI_Gather(local_result[start], per_process * matrixSize, MPI_DOUBLE, result[start], per_process * matrixSize, MPI_DOUBLE, 0, MPI_COMM_WORLD);

    Matrix::clear_matrix(local_result, matrixSize);

    return result;
}

