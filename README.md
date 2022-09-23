# Balanced Dice

:warning: WIP :warning:

This Library uses a deck of cards to simulate two 6-sided dice being rolled.

The Deck consists of 36 pairs of Dice, ranging from 2 to 12 in value, with 2 and twelve only having one possible pair each (1+1 = 2 and 6 + 6 = 12).

The Card of the value 7 is the most common with 6 pairs in deck.

The output tries to simulate a more fitting normal distribution of expected results even with fewer dice rolls.

Methodology involves calculating probability of drawing a value of previous rolls and changing the outcome afterwards. The deck is shuffled and reset after every 13 draw, allowing occasionall successive rolls of 2's and 12's to occur.

Heres is the reference I followed in implementation: [Colonist.io - Designing Balanced Dice](https://blog.colonist.io/designing-balanced-dice/)

## TODO
- Consider using [std::normal_distribution](https://en.cppreference.com/w/cpp/numeric/random/normal_distribution)
- Show Test of Fitness for normal distribution.
- Test if 16-bit as seed is enough to generate float value (0.f - 1.f), and if it would be valid to overlap some bits to use same seed twice.