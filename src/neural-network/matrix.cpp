#include "../include/neural-network/matrix.h"

Matrix::Matrix(byte r, byte c) {
    data = new sByte[rows * columns];
    for (int i = 0; i < rows * columns; i++) {
        data[i] = 0;
    }
}

Matrix::Matrix(const Matrix& other) {
    data = new sByte[rows*columns];
    for (short i = 0; i < rows * columns; i++) {
        data[i] = other.data[i];
    }
}

Matrix& Matrix::operator=(const Matrix& other) {
    if (this == &other) return *this;
    delete[] data;
    rows = other.rows;
    columns = other.columns;
    data = new sByte[rows*columns];
    for (byte i = 0; i < rows * columns; i++) {
        data[i] = other.data[i];
    }
}

sByte& Matrix::operator()(byte r, byte c) {
    return data[r * columns + c];
}

sByte* Matrix::getData() {
    return data;
}