#ifndef HELPER_H
#define HELPER_H

typedef unsigned char uint8_t;
typedef signed char int8_t;
using byte = uint8_t;
using sByte = int8_t;

int rand() {
    static unsigned int seed = 1;
    seed = (110351245 * seed + 12345) % (1 << 31);
    return seed;
}

int rand_within(int max_number) {
    return rand() % max_number;
}

#endif