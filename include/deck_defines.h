#pragma once
#include <stdint.h>

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
        {2}, {3}, {4}, {5}, {6}, {7}, {8}, {9}, {10}, {11}, { 12 } \
    }

#define INITIAL_DRAWS { \
        2, 3, 4, 5, 6, 7, 8, 9, 10, 11,  12 , \
        3, 4, 5, 6, 7, 8, 9, 10, 11, \
        4, 5, 6, 7, 8, 9, 10, \
        5, 6, 7, 8, 9, \
        6, 7, 8, \
        7 \
        }

static const uint8_t DICE_PAIRS_CONST[DECK_SIZE][6][2] =
    {
        {{1, 1}},
        {{1, 2}, {2, 1}},
        {{1, 3}, {3, 1}, {2, 2}},
        {{1, 4}, {4, 1}, {2, 3}, {3, 2}},
        {{1, 5}, {5, 1}, {2, 4}, {4, 2}, {3, 3}},
        {{1, 6}, {6, 1}, {2, 5}, {5, 2}, {3, 4}, {4, 3}},
        {{2, 6}, {6, 2}, {3, 5}, {5, 3}, {4, 4}},
        {{3, 6}, {6, 3}, {5, 4}, {4, 5}},
        {{4, 6}, {6, 4}, {5, 5}},
        {{5, 6}, {6, 5}},
        {{6, 6}}};