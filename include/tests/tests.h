#ifndef TESTS_H
#define TESTS_H

#include "../helper/helper.h"

#define TEST_CASE(name) \
    void test_function_##name(); \
    static TestRegistrar registrar_##name(#name, test_function_##name); \
    void test_function_##name() 

#define REQUIRE(expression) \
    if (!(expression)) { \
        print_concat("expression failed: ", #expression); \
    } else { \
        print_concat("expression passed: ", #expression); \
    }

struct TestCase {
    const char* name;
    void (*function)();
    TestCase() {}
    TestCase(const char* new_name, void (*func)()) : name(new_name), function(func) {}
};

class TestRunner {
    public:
        static int testAmount;
        static TestCase tests[1000];

        static TestCase* getTests() {
            return tests;
        }

        static void registerTest(const char* name, void (*func)()) {
            TestCase test(name, func);
            tests[testAmount] = test;
            testAmount++;
        }

        static void run_all_tests() {
            for (int i = 0; i < testAmount; i++) {
                #ifdef DESKTOP
                    try {
                        void (*func)() = tests[i].function;
                        func();
                    } catch (const std::exception& e) {
                        print_concat("test threw exception: ", tests[i].name);
                        print_concat("Exception: " , e.what());
                    }
                #else
                    void (*func)() = tests[i].function;
                    func();
                #endif
            }
        }
};

struct TestRegistrar {
    TestRegistrar(char* name, void (*func)()) {
        TestRunner::registerTest(name, func);
    }
};

int TestRunner::testAmount = 0;
TestCase TestRunner::tests[1000];

#endif