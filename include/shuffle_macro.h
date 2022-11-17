#pragma once
#include "random_utils.h"

#define decl_shuffle(type)                                     \
    void shuffle_##type(type *list, uint8_t len, uint16_t seed) \
    {                                                          \
        uint8_t j;                                                 \
        type tmp;                                              \
        while (len)                                            \
        {                                                      \
            j = rand_uint8_range(seed, len);                              \
            if (j != len - 1U)                                  \
            {                                                  \
                tmp = list[j];                                 \
                list[j] = list[len - 1];                       \
                list[len - 1] = tmp;                           \
            }                                                  \
            len--;                                             \
        }                                                      \
    }
