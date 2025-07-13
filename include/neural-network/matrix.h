#ifndef MATRIX_H
#define MATRIX_H

#include "../helper/helper.h"

struct Matrix {
    sByte* data;
    byte rows;
    byte columns;

    ~Matrix();
    Matrix(byte r, byte c);
    Matrix(const Matrix& other);
    Matrix& operator=(const Matrix& other);

    sByte& operator()(byte r, byte c);

    sByte* getData();
};

#endif
