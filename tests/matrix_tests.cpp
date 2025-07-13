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

int main() {
    TestRunner::run_all_tests();
    waitForExit();
}