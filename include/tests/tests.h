#ifndef TESTS_H
#define TESTS_H

#include "../helper/helper.h"

#define TEST_CASE(name) \
    struct TestCase_##name { \
        static const char* get_name() { return #name; } \
        static void run(); \
        static int requireCount; \
        static bool requirements[1000]; \
    }; \
    int TestCase_##name::requireCount = 0; \
    bool TestCase_##name::requirements[1000]; \
    static TestRegistrar registrar_##name(#name, TestCase_##name::run); \
    void TestCase_##name::run()

#define REQUIRE(expression) \
    if (!(expression)) { \
        print_concat("expression failed: ", #expression); \
        requirements[requireCount] = false; \
        requireCount++; \
    } else { \
        print_concat("expression passed: ", #expression); \
        requirements[requireCount] = true; \
        requireCount++; \
    }

#define END_TEST \
    int passed = 0; \
    int failed = 0; \
    for(int i = 0; i < requireCount; i++) { \
        if (requirements[i] == true) { \
            passed++; \
        } else { \
            failed++; \
        } \
    } \
    print("Result: "); \
    print(passed); \
    print(" out of "); \
    print(passed+failed); \
    print_line(" requirements passed."); 

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
        static bool passed;

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
                        passed = false;
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
    TestRegistrar(const char* name, void (*func)()) {
        TestRunner::registerTest(name, func);
    }
};

int TestRunner::testAmount = 0;
TestCase TestRunner::tests[1000];
bool TestRunner::passed = false;

#endif