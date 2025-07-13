#include "../include/neural-network/matrix.h"
#include "../include/tests/tests.h"

TEST_CASE(instantiation) {
    int size = 12;
    Matrix matrix(4,3);
    REQUIRE(sizeof(matrix.data) == size);
    REQUIRE(matrix.rows*matrix.columns == size);
    for (int i = 0; i < size; i++) {
        REQUIRE(matrix.data[0] == 0);
    }
}

int main() {
    TestRunner::run_all_tests();
}