#pragma once
#include <stdint.h>

// NOTE: Implementation is dependant on these values being lower than certain byte sized thesholds i.e:
// MIN_ROLLS_BEFORE_SHUFFLING, DECK_SIZE and MAX_ROLLS_COUNT is expected to be maximum of 4 bits (0..15)
// See BalancedDice.h, rollCount,

#define DECK_SIZE 11
#define DECK_SIZE_PAIRS 36
#define MAX_ROLLS_COUNT 8
#define MIN_ROLLS_BEFORE_RESHUFFLING 13
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