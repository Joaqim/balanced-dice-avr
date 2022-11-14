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

void printDraws(uint8_t draws[36])
{
    printf("----\ndraws: \n\t");
    for (int n{0}; n < 36; n += 1)
    {
        printf("%u, ", draws[n]);
    }
    printf("\n----\n");
}

// Histogram - https://stackoverflow.com/a/9990787
void printHistogram(int draws[])
{
    int max_value = draws[0];
    for (int n{1}; n < 11; n += 1)
    {
        if (draws[n] > max_value)
            max_value = draws[n];
    }

    const int chart_height = max_value;

    for (int current_height = chart_height; current_height > 0; --current_height)
    {
        for (int n{0}; n < 11; n += 1)
        {
            const int value = draws[n];
            const int bar_height = (value * chart_height) / max_value;
            if (bar_height < current_height)
                printf("     "); // we're still above the bar
            else if (bar_height == current_height)
                printf("  _  "); // reached the top of the bar
            else                 // bar_height > current_height
                printf(" | | "); // now the rest of the bar ...
        }
        printf("\n");
    }
    printf("  -    -    -    -    -    -    -    -    -    -    -\n");
    printf("  2    3    4    5    6    7    8    9   10   11   12\n");
}

int main()
{

    srand(time(NULL));
#if 1
    float result{0.f};
    for (unsigned int n{0U}; n < 11U; n += 1U)
    {

        struct Dice dice = {PAIRS_INITIAL_CONST[n]};

        uint32_t diceBits = dice.bits;
        dice.reset();
        // printf("%u == %u\n", dice.bits, diceBits);
        assert(dice.bits == diceBits);
        const uint8_t diceCount = static_cast<uint8_t>(dice.count());
        if (diceCount > 0U)
        {
            printf("%u\t", diceCount);
            printf("%f\n", static_cast<float>(diceCount) / 36.f);
            result += static_cast<float>(diceCount) / 36.f;
        }

        // dice.shuffle(static_cast<uint8_t>(time(NULL)));
        // const uint8_t seed = irand(static_cast<uint8_t>(rand()), UINT8_MAX - 1);

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

        assert(dice.recentRollsCount() == 0);
        assert(dice.value() == n + 2U);
        assert(dice.recentRollsCount() == 0);

        auto result = dice.popDice();
        printDiceResult(result);
    }
    printf("TotalProbability: %f\n", result);
#endif

    const auto seed = rand_uint32();

    // printf("Seed: %u\n", seed);
    // printf("randfloat(): %f\n", randfloat(seed));
    //  const uint16_t seed = ;
    int counts[11] = {0};
    BalancedDice ctr{seed};
    assert(ctr.cardsInDeck > 0);
    assert(ctr.rollCount == 0);
    printf("%f\n", ctr.updateDiceProbabilities());
#if 1
    printDraws(ctr.draws);
    ctr.shuffleDraws(rand_uint16());
    printDraws(ctr.draws);
#endif

    const auto sampleSize = 50;
    uint32_t numberOfDoubles = 0;
    int doubles[11] = {0};
    uint8_t lastDiceValue = 0;
    for (int n{0}; n < sampleSize; n += 1)
    {
        // printf("Drawing index: %u\n", ctr.draws[n]);
        // const uint16_t newSeed = static_cast<uint16_t>(rand());
        const auto newSeed = rand_uint32();

        const auto probabilityWeight = ctr.updateDiceProbabilities();
        const float rngModifier = randfloat(newSeed);
        printf("%f * %f = %f\n", probabilityWeight, rngModifier, rngModifier * probabilityWeight);
        printf("Target Random Value: %f\n", rngModifier * probabilityWeight);
        auto result = ctr.rollDie(newSeed);
        assert(result.value > 0);

        // assert(ctr.recentRolls[ctr.recentRollsCount] == result.value - 2);
        printf("Dice Probability: %f\n", ctr.diceProbabilities[result.value - 2]);
        printDiceResult(result);
        printf("\nRecent rolls: \n");
        for (int i{0}; i < ctr.recentRollsCount; i += 1)
        {
            printf("%u, ", ctr.recentRolls[i] + 2);
        }
        printf("\n----\n");

        if (lastDiceValue == result.value)
        {
            numberOfDoubles += 1;
            doubles[lastDiceValue - 2] += 1;
        }
        lastDiceValue = result.value;
        counts[result.value - 2] += 1;
        // printf("%u ", result.value);
    }

    printf("\n");
#if 0
    for (int n{0}; n < 11; n += 1)
    {
        printf("%i, ", counts[n]);
    }
    printf("\n");
#endif
#if 1

    printf("\n\nProbabilities:\n");
    for (int n{0}; n < 11; n += 1)
    {
        printf("%f", ctr.diceProbabilities[n]);
        if (n < 10)
        {
            printf(", ");
        }
    }

    printf("\n\nDoubles:\n");
    printf("Total: %lu \n", numberOfDoubles);
    for (int n{0}; n < 11; n += 1)
    {
        printf("%i, ", doubles[n]);
    }
    printf("\n Balanced Dice Histogram:\n");

#endif

    printHistogram(counts);

    int normalDiceDoublesResults[11] = {0};
    int normalDiceResults[11] = {0};
    int lastResult = -1;
    for (int n{0}; n < sampleSize; n += 1)
    {
        const int diceResult = rand() % 13;
        normalDiceResults[diceResult] += 1;
        if (diceResult == lastResult)
        {
            normalDiceDoublesResults[diceResult] += 1;
        }
        lastResult = diceResult;
    }

    printf("\n Unbalanced Dice Histogram:\n");
    printHistogram(normalDiceResults);

    printf("\n Balanced Dice Doubles Histogram:\n");
    printHistogram(doubles);

    printf("\n Unbalanced Dice Doubles Histogram:\n");
    printHistogram(normalDiceDoublesResults);

    return 0;
}
