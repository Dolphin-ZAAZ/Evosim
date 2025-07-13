#ifndef HELPER_H
#define HELPER_H

#define DESKTOP

#ifdef DESKTOP
#include <iostream>
#include <stdexcept>
#include <ostream>
#endif

using byte = unsigned char;
using sByte = signed char;

static int allocation_count = 0;

inline int rand() {
    static unsigned int seed = 1;
    seed = (110351245 * seed + 12345) % (1 << 31);
    return seed;
}

inline int rand_within(int max_number) {
    return rand() % max_number;
}

template<typename T>
inline void print(const T& anything) {
    std::cout << anything;
}

template<typename T>
inline void print_line(const T& anything) {
    std::cout << anything << std::endl;
}

inline void print_concat(const char* line, const char* line2) {
    #ifdef DESKTOP
        int anything;
        std::cout << line << line2 << std::endl;
    #else
        Serial.print(line);
    #endif
}

inline void waitForExit() {
    std::string exit = "";
    while (exit != "e" && exit != "exit") {
        exit = "";
        print_line("type (e)xit and press enter to quit.");
        std::cin >> exit;
    }
}

inline void* operator new(size_t size) {
    allocation_count++;
    return malloc(size);
}

inline void operator delete(void* ptr) {
    if (ptr) {
        allocation_count--;
        free(ptr);
    }
}

inline int get_allocation_count() {
    return allocation_count;
}

#endif