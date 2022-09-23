#pragma once
#include <stdint.h>

// NOTE: Implementation is dependant on these values being lower than certain byte sized thesholds i.e:
// DECK_SIZE is expected to be maximum of 4 bits (0..15)
// See BalancedDice.h, rollCount,

#define DECK_SIZE 11
#define DECK_SIZE_PAIRS 36
#define MIN_ROLLS_BEFORE_RESHUFFLING 24 // 12 cards remaining in deck when we reshuffle
#define PROBABILITY_REDUCTION_FOR_RECENTLY_ROLLED 0.3

#define WITH_UNDO
#ifdef WITH_UNDO
#define MAXIMUM_UNDO 1
#else
#define MAXIMUM_UNDO 0
#endif
#define MAXIMUM_RECENT_ROLL_MEMORY 5 + MAXIMUM_UNDO

#define INITIAL_DECK                                               \
    {                                                              \
        {2}, {3}, {4}, {5}, {6}, {7}, {8}, {9}, {10}, {11}, { 12 } }

#define INITIAL_DRAWS {                     \
        2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, \
        3, 4, 5, 6, 7, 8, 9, 10, 11,        \
        4, 5, 6, 7, 8, 9, 10,               \
        5, 6, 7, 8, 9,                      \
        6, 7, 8,                            \
        7                                   \
    }