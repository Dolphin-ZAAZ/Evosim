#ifndef MATRIX_H
#define MATRIX_H

#include "helper/helper.h"

struct Matrix {
    sByte* data;
    byte rows;
    byte columns;

    ~Matrix() { delete[] data; }
    Matrix(byte r, byte c) : rows(r), columns(c) {}
    Matrix(const Matrix& other) : rows(other.rows), columns(other.columns) {}
    Matrix& operator=(const Matrix& other) {}

    sByte& operator()(byte r, byte c) {}

    sByte* getData() {}
};

#endif
