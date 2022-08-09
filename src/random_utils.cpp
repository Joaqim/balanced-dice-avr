#pragma once
#include <Arduino.h>
#include "random_utils.h"

float randfloat()
{
    // return (float)(rand() / (RAND_MAX)) + 1.0;
    return (float)(rand()) / ((float)(RAND_MAX / (1.0)));
}

int randint(int max, int min = 0)
{
    // return int(max * rand() / (RAND_MAX + 1.0));
    return min + rand() / (RAND_MAX / (max - min) + 1);
}

/* random integer from 0 to n-1 */
int irand(int n)
{
    int r, rand_max = RAND_MAX - (RAND_MAX % n);
    /* reroll until r falls in a range that can be evenly
     * distributed in n bins.  Unless n is comparable to
     * to RAND_MAX, it's not *that* important really. */
    while ((r = rand()) >= rand_max)
        ;
    return r / (rand_max / n);
}

