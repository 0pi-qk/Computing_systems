#include "matrix.h"

double** Matrix::init_matrix(size_t size) {
    double** m = new double* [size];
    for (size_t i = 0; i < size; i++)
        m[i] = new double[size];
    return m;
}

void Matrix::clear_matrix(double** m, size_t size) {
    for (size_t i = 0; i < size; i++)
        delete[] m[size];
    delete[] m;
}

void Matrix::print_matrix(double** m, size_t size) {
    for (size_t i = 0; i < size;i++){
        for (size_t j = 0; j < size; j++)
            cout << m[i][j] << "   ";
        cout << endl;
        }
    cout << endl;
}