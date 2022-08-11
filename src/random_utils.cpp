#include "random_utils.h"

// TODO: Check that this is correct
float randfloat(uint16_t seed)
{
    // return (float)(rand() / (RAND_MAX)) + 1.0;
    return (float)(seed) / ((float)UINT16_MAX / 1.0f);
}

#if 0
uint32_t randint(uint32_t max, uint32_t min)
{
    // return int(max * rand() / (RAND_MAX + 1.0));
    return min + rand() / (RAND_MAX / (max - min) + 1);
}
#endif

/* random integer from 0 to n-1 */
// TODO: Is this correct? Is 8 bits enough to generate convincing pseudo random 8 bit numbers?
uint8_t irand(uint8_t seed, uint8_t n)
{
    return seed / ((UINT8_MAX / n) + 1);
}
