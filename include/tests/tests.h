#ifndef TESTS_H
#define TESTS_H

#include "../helper/helper.h"

#define TEST_CASE(name) \
    struct TestCase_##name { \
        static bool verdict; \
        static bool get_verdict() { return verdict; } \
        static const char* get_name() { return #name; } \
        static void run(); \
        static int requireCount; \
        static bool requirements[1000]; \
    }; \
    bool TestCase_##name::verdict = true; \
    int TestCase_##name::requireCount = 0; \
    bool TestCase_##name::requirements[1000]; \
    static TestRegistrar registrar_##name(#name, TestCase_##name::run, TestCase_##name::get_verdict); \
    void TestCase_##name::run()

#define REQUIRE(expression) \
    if (!(expression)) { \
        print_concat(get_name(), "Test Requirement Failed: "); \
        print_concat("expression: ", #expression); \
        requirements[requireCount] = false; \
        requireCount++; \
        verdict = false; \
    } else { \
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
    print_line("Requirements Result: "); \
    print(passed); \
    print(" out of "); \
    print(passed+failed); \
    print_line(" requirements passed."); \
    print_line("");

struct TestCase {
    const char* name;
    bool (*verdict)();
    void (*function)();
    TestCase() {}
    TestCase(const char* new_name, void (*func)(), bool (*verd)()) : name(new_name), function(func), verdict(verd) {}
};

class TestRunner {
    public:
        static int testAmount;
        static TestCase tests[1000];
        static int failed;
        static int passed;

        static TestCase* getTests() {
            return tests;
        }

        static void registerTest(const char* name, void (*func)(), bool (*verdict)()) {
            TestCase test(name, func, verdict);
            tests[testAmount] = test;
            testAmount++;
        }

        static void run_all_tests() {
            for (int i = 0; i < testAmount; i++) {
                #ifdef DESKTOP
                    print_line("------------");
                    print("Running Test For: ");
                    print_line(tests[i].name);
                    print_line("------------");
                    try {
                        void (*func)() = tests[i].function;
                        func();
                        bool (*verdict)() = tests[i].verdict;
                        if (verdict()) {
                            passed++;
                        } else {
                            failed++;
                        }
                    } catch (const std::exception& e) {
                        print_concat("test threw exception: ", tests[i].name);
                        print_concat("Exception: " , e.what());
                    }
                #else
                    void (*func)() = tests[i].function;
                    func();
                #endif
            }
            print_line("");
            print_line("Final Results: ");
            print(passed);
            print(" out of "); 
            print(passed+failed);
            print_line(" tests passed.");
            print_line("");
        }
};

struct TestRegistrar {
    TestRegistrar(const char* name, void (*func)(), bool (*verdict)()) {
        TestRunner::registerTest(name, func, verdict);
    }
};

int TestRunner::passed = 0;
int TestRunner::failed = 0;
int TestRunner::testAmount = 0;
TestCase TestRunner::tests[1000];

#endif