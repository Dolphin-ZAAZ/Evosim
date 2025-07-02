#include "../include/universe/universe.h"

Universe::Universe() {
    for(int i = 0; i < 480; i++) {
        xAxis[i] = i;
    }
    for(int i = 0; i < 360; i++) {
        yAxis[i] = i;
    }
}