#include "random_utils.h"

/* Number of bits in inttype_MAX, or in any (1<<k)-1 where 0 <= k < 2040 */
#define IMAX_BITS(m) ((m) / ((m) % 255 + 1) / 255 % 255 * 8 + 7 - 86 / ((m) % 255 + 12))
#define RAND_MAX_BITWIDTH (IMAX_BITS(RAND_MAX))

/**
 * Generate a random float value using the given seed.
 *
 * @param seed The seed used to generate the random float value.
 *
 * @return The random float value generated based on the seed.
 *
 * @throws None
 */
float randfloat(uint16_t seed)
{
    return (float)seed / (static_cast<float>(UINT16_MAX) / 1.0f);
}

#if 0
uint32_t randint(uint32_t max, uint32_t min)
{
    // return int(max * rand() / (RAND_MAX + 1.0));
    return min + rand() / (RAND_MAX / (max - min) + 1);
}
#endif

/* random integer from 0 to max */
// TODO: Is this correct? Is an 8 bit seed enough to generate a good pseudo random 8 bit numbers?
uint8_t rand_uint8_range(uint8_t seed, uint8_t max){
    //return static_cast<uint8_t>(rand()) / (UINT8_MAX + (max) + 1U);
    return seed / ((UINT8_MAX / max) + 1);
}

/**
 * Generates a random 16-bit unsigned integer.
 *
 * @return random 16-bit unsigned integer
 *
 * @throws None
 */
uint16_t rand_uint16()
{
    uint16_t r = 0;
    for (uint16_t i = 0; i < IMAX_BITS(UINT16_MAX); i += RAND_MAX_BITWIDTH)
    {
        r <<= RAND_MAX_BITWIDTH;
        r |= rand();
    }
    return r;
}

/**
 * Generates a random 32-bit unsigned integer using the rand() function.
 *
 * @return the generated random 32-bit unsigned integer
 */
uint32_t rand_uint32()
{
    uint32_t r = 0;
    for (uint32_t i = 0; i < IMAX_BITS(UINT32_MAX); i += RAND_MAX_BITWIDTH)
    {
        r <<= RAND_MAX_BITWIDTH;
        r |= rand();
    }
    return r;
}

/**
 * Generates a random unsigned 8-bit integer.
 *
 * @return random unsigned 8-bit integer
 *
 * @throws None
 */
uint8_t rand_uint8()
{
    uint8_t r = 0;
    for (uint8_t i = 0; i < IMAX_BITS(UINT8_MAX); i += RAND_MAX_BITWIDTH)
    {
        r <<= RAND_MAX_BITWIDTH;
        r |= rand();
    }
    return r;
}