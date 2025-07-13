#ifndef HELPER_H
#define HELPER_H

#define DESKTOP;

#ifdef DESKTOP
#include <iostream>
#include <stdexcept>
#include <ostream>
#endif

using byte = unsigned char;
using sByte = signed char;

inline int rand() {
    static unsigned int seed = 1;
    seed = (110351245 * seed + 12345) % (1 << 31);
    return seed;
}

inline int rand_within(int max_number) {
    return rand() % max_number;
}

inline void print(const char* line) {
    #ifdef DESKTOP
        int anything;
        std::cout << line << std::endl;
        std::cin >> anything;
    #else
        Serial.print(line);
    #endif
}

inline void print_concat(const char* line, const char* line2) {
    #ifdef DESKTOP
        int anything;
        std::cout << line << line2 << std::endl;
        std::cin >> anything;
    #else
        Serial.print(line);
    #endif
}

#endif