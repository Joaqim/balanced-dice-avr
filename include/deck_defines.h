#pragma once

// NOTE: Implementation is dependant on these values being lower than certain byte sized thesholds i.e:
// DECK_SIZE is expected to be maximum of 4 bits (0..15)
// See BalancedDice.h: BalancedDice::rollCount,

#define DECK_SIZE 11
#define PROBABILITY_REDUCTION_FOR_RECENTLY_ROLLED 0.3f
#define DECK_SIZE_PAIRS 36
#define MINIMUM_CARDS_LEFT_BEFORE_RESHUFFLING 12

#define MAXIMUM_RECENT_ROLL_MEMORY 5

#define INITIAL_DECK \
         { {2}, {3}, {4}, {5}, {6}, {7}, {8}, {9}, {10}, {11}, { 12 } }
