#include "../include/neural-network/matrix.h"
#include "../include/tests/tests.h"

TEST_CASE(instantiation) {
    int size = 12;
    Matrix matrix(4,3);
    int actualSize = matrix.columns * matrix.rows * sizeof(sByte);
    REQUIRE(actualSize == size);
    REQUIRE(matrix.rows*matrix.columns == size);
    for (int i = 0; i < actualSize; i++) {
        REQUIRE(matrix.data[i] == 0);
    }
    END_TEST;
}

TEST_CASE(passing_data) {
    sByte data[12] = {1,-1,2,
                    -2,3,-3,
                    4,-4,5,
                    -5,6,-6};
    Matrix matrix(4,3, data);
    REQUIRE(matrix(0,0) == 1);
    REQUIRE(matrix(1,0) == -2);
    REQUIRE(matrix(1,2) == -3);
    REQUIRE(matrix(2,0) == 4);
    REQUIRE(matrix(2,1) == -4);
    REQUIRE(matrix(3,2) == -6);
    END_TEST;
}

TEST_CASE(copy_constructor) {
    sByte data[12] = {1,-1,2,
                    -2,3,-3,
                    4,-4,5,
                    -5,6,-6};
    Matrix firstMatrix(4,3, data);
    Matrix secondMatrix(firstMatrix);
    REQUIRE(firstMatrix(0,0) == secondMatrix(0,0));
    REQUIRE(firstMatrix(1,0) == secondMatrix(1,0));
    REQUIRE(firstMatrix(1,2) == secondMatrix(1,2));
    REQUIRE(firstMatrix(2,0) == secondMatrix(2,0));
    REQUIRE(firstMatrix(2,1) == secondMatrix(2,1));
    REQUIRE(firstMatrix(3,2) == secondMatrix(3,2));
    END_TEST;
}

TEST_CASE(assignment_operator) {
    sByte data[12] = {1,-1,2,
                    -2,3,-3,
                    4,-4,5,
                    -5,6,-6};
    sByte secondData[12] = {-6,6,-5,
                            5,-4,4,
                            -3,3,-2,
                            2,-1,1};
    Matrix firstMatrix(4,3, data);
    Matrix secondMatrix(4,3, secondData);
    secondMatrix = firstMatrix;
    REQUIRE(firstMatrix(0,0) == 1);
    REQUIRE(firstMatrix(1,0) == -2);
    REQUIRE(firstMatrix(1,2) == -3);
    REQUIRE(firstMatrix(2,0) == 4);
    REQUIRE(firstMatrix(2,1) == -4);
    REQUIRE(firstMatrix(3,2) == -6);
    REQUIRE(firstMatrix(0,0) == secondMatrix(0,0));
    REQUIRE(firstMatrix(1,0) == secondMatrix(1,0));
    REQUIRE(firstMatrix(1,2) == secondMatrix(1,2));
    REQUIRE(firstMatrix(2,0) == secondMatrix(2,0));
    REQUIRE(firstMatrix(2,1) == secondMatrix(2,1));
    REQUIRE(firstMatrix(3,2) == secondMatrix(3,2));
    END_TEST;
}

TEST_CASE(get_data) {
    sByte data[12] = {1,-1,2,
                    -2,3,-3,
                    4,-4,5,
                    -5,6,-6};
    Matrix matrix(4,3, data);
    sByte* matData = matrix.getData();
    for (int i = 0; i < 12; i++) {
        REQUIRE(data[i] == matData[i]);
    }
    END_TEST;
}

TEST_CASE(memory_leak) {
    int initial_count = get_allocation_count();
    {
        Matrix matrix(4,3);
    }
    int final_count = get_allocation_count();
    REQUIRE(initial_count == final_count);
    END_TEST;
}

void sizeBenchmarkInfo() {
    print_line("Benchmark Results: ");
    Matrix matrix(16,12);
    Matrix matrix2(12,8);
    Matrix matrix3(8,4);
    Matrix matrix4(4,8);
    print("size of 16x12 matrix: ");
    print_line(sizeof(matrix) + (matrix.rows*matrix.columns*sizeof(sByte)));
    print("size of 12x8 matrix: ");
    print_line(sizeof(matrix2) + (matrix2.rows*matrix2.columns*sizeof(sByte)));
    print("size of 8x4 matrix: ");
    print_line(sizeof(matrix3) + (matrix3.rows*matrix3.columns*sizeof(sByte)));
    print("size of 4x8 matrix: ");
    print_line(sizeof(matrix4) + (matrix4.rows*matrix4.columns*sizeof(sByte)));
    print_line("");
}

int main() {
    TestRunner::run_all_tests();
    sizeBenchmarkInfo();
    waitForExit();
    return 1;
}