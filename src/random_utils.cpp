#include "random_utils.h"
#include <stdlib.h>

/* Number of bits in inttype_MAX, or in any (1<<k)-1 where 0 <= k < 2040 */
#define IMAX_BITS(m) ((m) / ((m) % 255 + 1) / 255 % 255 * 8 + 7 - 86 / ((m) % 255 + 12))
#define RAND_MAX_BITWIDTH (IMAX_BITS(RAND_MAX))

float randfloat(uint16_t seed)
{
    // return static_cast<float>(seed) / (static_cast<float>(UINT16_MAX) / 1.0f);
    return (float)seed / ((float)UINT16_MAX / 1.0f);
}

#if 0
uint32_t randint(uint32_t max, uint32_t min)
{
    // return int(max * rand() / (RAND_MAX + 1.0));
    return min + rand() / (RAND_MAX / (max - min) + 1);
}
#endif

/* random integer from 0 to n-1 */
// TODO: Is this correct? Is an 8 bit seed enough to generate convincing pseudo random 8 bit numbers?
uint8_t irand(uint8_t seed, uint8_t n)
{
    return seed / ((UINT8_MAX / n) + 1);
}

uint16_t rand_uint16()
{
    uint16_t r = 0;
    for (int i = 0; i < IMAX_BITS(UINT16_MAX); i += RAND_MAX_BITWIDTH)
    {
        r <<= RAND_MAX_BITWIDTH;
        r |= rand();
    }
    return r;
}

uint32_t rand_uint32()
{
    uint32_t r = 0;
    for (int i = 0; i < IMAX_BITS(UINT32_MAX); i += RAND_MAX_BITWIDTH)
    {
        r <<= RAND_MAX_BITWIDTH;
        r |= rand();
    }
    return r;
}

uint8_t rand_uint8()
{
    uint8_t r = 0;
    for (int i = 0; i < IMAX_BITS(UINT8_MAX); i += RAND_MAX_BITWIDTH)
    {
        r <<= RAND_MAX_BITWIDTH;
        r |= rand();
    }
    return r;
}