#include "../include/neural-network/network.h"
#include "../include/tests/tests.h"

int main() {
    TestRunner::run_all_tests();
    sizeBenchmarkInfo();
    waitForExit();
    return 1;
}

void sizeBenchmarkInfo() {

}

TEST_CASE(network_config_default) {
    NetworkConfig netCon;
    REQUIRE(netCon.inputs = 16);
    REQUIRE(netCon.count = 4);
    REQUIRE(netCon.sizes[0] == 12);
    REQUIRE(netCon.sizes[1] == 8);
    REQUIRE(netCon.sizes[2] == 4);
    REQUIRE(netCon.sizes[3] == 8);
    END_TEST;
}

TEST_CASE(network_config_params) {
    byte sizes[3] = {3,3,3};
    NetworkConfig* netCon = new NetworkConfig(3,3, sizes);
    byte sizes2[4] = {3,4,5,4};
    NetworkConfig* netCon2 = new NetworkConfig(3,4, sizes2);
    byte sizes3[5] = {5,4,3,2,3};
    NetworkConfig* netCon3 = new NetworkConfig(5,5, sizes3);
    REQUIRE(netCon->count == 3);
    const int count = netCon->count;
    print(count);
    REQUIRE(netCon->inputs == 3);
    for (int i = 0; i < 3; i++) {
        REQUIRE(netCon->sizes[i] == sizes[i]);
    }
    REQUIRE(netCon2->count == 4);
    REQUIRE(netCon2->inputs == 3);
    for (int i = 0; i < 4; i++) {
        REQUIRE(netCon2->sizes[i] == sizes2[i]);
    }
    REQUIRE(netCon3->count == 5);
    REQUIRE(netCon3->inputs == 5);
    for (int i = 0; i < 5; i++) {
        REQUIRE(netCon3->sizes[i] == sizes3[i]);
    }
    END_TEST;
}

TEST_CASE(network_config_memory_leak) {
    int initial_count = get_allocation_count();
    {
        NetworkConfig net;
    }
    int final_count = get_allocation_count();
    REQUIRE(initial_count == final_count);
    END_TEST;
}

TEST_CASE(network_with_config) {
    
}

TEST_CASE(network_with_params) {

}

TEST_CASE(network_copy_constructor) {

}

TEST_CASE(network_assignment_ooperator) {

}

TEST_CASE(activation_function) {

}

TEST_CASE(forward_function) {

}

TEST_CASE(network_memory_leak) {

}