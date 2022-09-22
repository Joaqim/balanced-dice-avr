#include <BalancedDice.h>
#include <Dice.h>
#include <dice_constants.h>
#include <random_utils.h>

#include <time.h>

#include <stdint.h>
#include <stdio.h>

void printDiceResult(DiceResult &result)
{
    printf("%u + %u = %u\n", result.dice1, result.dice2, result.value);
    assert(result.dice1 != 0);
    assert(result.dice2 != 0);
    assert(result.dice1 != result.value);
    assert(result.dice2 != result.value);

    assert(result.dice1 + result.dice2 == result.value);
}

int main()
{

    srand(time(NULL));
#if 1
    for (int n{0}; n < 11; n += 1)
    {
        struct Dice dice = {PAIRS_INITIAL_CONST[n]};

        uint32_t diceBits = dice.bits;
        dice.reset();
        // printf("%u == %u\n", dice.bits, diceBits);
        assert(dice.bits == diceBits);

        // dice.shuffle(static_cast<uint8_t>(time(NULL)));
        const uint8_t seed = irand(static_cast<uint8_t>(rand()), UINT8_MAX - 1);

        // dice.shuffle(seed);

#if 0
        printf("%u, pairs: %u, roll_count: %u, Dice: %u, %u, %u, %u, %u, %u\n", dice.value(), dice.count(), dice.roll_count(),
               dice.p1d1(),
               dice.p2d1(),
               dice.p3d1(),
               dice.p4d1(),
               dice.p5d1(),
               dice.p6d1());
#endif

        assert(dice.roll_count() == 0);
        assert(dice.value() == n + 2);

        auto result = dice.popDice();
        // printDiceResult(result);
    }
#endif

    const uint16_t seed = static_cast<uint16_t>(rand() % UINT16_MAX);

    printf("Seed: %u\n", seed);
    printf("randfloat(): %f\n", randfloat(seed));
    // const uint16_t seed = ;
    int counts[11] = {0};
    BalancedDice ctr{seed};
    assert(ctr.cardsInDeck > 0);
    assert(ctr.rollCount == 0);
#if 0
    printf("----\ndraws: \n\t");
    for (int n{0}; n < 36; n += 1)
    {
        printf("%u, ", ctr.draws[n]);
    }
    printf("\n----\n");
#endif

    const auto sampleSize = 26;
    for (int n{0}; n < sampleSize; n += 1)
    {
        // printf("Drawing index: %u\n", ctr.draws[n]);
        const uint16_t newSeed = randfloat(time(NULL));

        const auto probabilityWeight = ctr.getTotalProbabilityWeight();
        if(probabilityWeight > 0) {
            printf("%f\n", ctr.getTotalProbabilityWeight());
        }
        auto result = ctr.rollDie(newSeed);
        assert(result.value > 0);


        // printDiceResult(result);
        counts[result.value - 2] += 1;
        //printf("%u ", result.value);
    }
    for (int n{0}; n < 11; n += 1)
    {
        printf("%i, ", counts[n]+2);
    }

    return 0;
}
