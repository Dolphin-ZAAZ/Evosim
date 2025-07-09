#ifndef MATRIX_H
#define MATRIX_H

#include "helper/helper.h"

struct Matrix {
    sByte* data;
    byte rows;
    byte columns;

    ~Matrix() { delete[] data; }

    Matrix(byte r, byte c) : rows(r), columns(c) {
        data = new sByte[rows * columns];
        for (int i = 0; i < rows * columns; i++) {
            data[i] = 0;
        }
    }

    Matrix(const Matrix& other) : rows(other.rows), columns(other.columns) {
        data = new sByte[rows*columns];
        for (short i = 0; i < rows * columns; i++) {
            data[i] = other.data[i];
        }
    }

    Matrix& operator=(const Matrix& other) {
        if (this == &other) return *this;
        delete[] data;
        rows = other.rows;
        columns = other.columns;
        data = new sByte[rows*columns];
        for (byte i = 0; i < rows * columns; i++) {
            data[i] = other.data[i];
        }
        
    }

    sByte& operator()(byte r, byte c) {
        return data[r * columns + c];
    }

    sByte* getData() {
        return data;
    }
};

#endif
