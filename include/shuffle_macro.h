#pragma once
#include "random_utils.h"

#define decl_shuffle(type)                                     \
    void shuffle_##type(type *list, size_t len, uint16_t seed) \
    {                                                          \
        int j;                                                 \
        type tmp;                                              \
        while (len)                                            \
        {                                                      \
            j = irand(seed, len);                              \
            if (j != len - 1)                                  \
            {                                                  \
                tmp = list[j];                                 \
                list[j] = list[len - 1];                       \
                list[len - 1] = tmp;                           \
            }                                                  \
            len--;                                             \
        }                                                      \
    }
