#include <cstdlib>
#include "Random.h"

#define MAX_RAND ((2UL << 31) - 1)

double Random::get_rand_val_double() {
    return (double)random() / MAX_RAND;
}