# Balanced Dice

:warning: WIP :warning:

This Library uses a deck of cards to simulate two 6-sided dice being rolled.

The Deck consists of 36 pairs of Dice, ranging from 2 to 12 in value, with for instance 2 and 12 only having one possible pair each (1+1 = 2 and 6 + 6 = 12).

The Card with value 7 has 6 possible pairs: 1+6,2+5,3+4 and the reverse 6+1,5+2,4+3.

The output tries to simulate a more fitting normal distribution of expected results even with fewer dice rolls.

Methodology involves calculating probability of drawing a value of previous rolls and changing the outcome afterwards. The deck is shuffled when there are only 12 cards left in the deck, allowing occasionally successive rolls of 2's and 12's to occur.

# Histograms

Each is a sample of 50 dice being thrown.


## Balanced Dice:
```
                           _                           
                          | |                          
                      _   | |   _                      
                     | |  | |  | |                     
                     | |  | |  | |                     
                     | |  | |  | |                     
            _        | |  | |  | |                     
           | |   _   | |  | |  | |                     
           | |  | |  | |  | |  | |   _         _       
       _   | |  | |  | |  | |  | |  | |   _   | |      
  _   | |  | |  | |  | |  | |  | |  | |  | |  | |   _  
  -    -    -    -    -    -    -    -    -    -    -
  2    3    4    5    6    7    8    9   10   11   12
```
<p>
	<em>NOTE: 2 and 12 have the lowest value of 1 in their respective column.</em>
</p>

## Unbalanced Dice, naive implementation:
```
                      _
                     | |
                     | |                  _
                     | |   _    _    _   | |
       _    _        | |  | |  | |  | |  | |
      | |  | |       | |  | |  | |  | |  | |
      | |  | |       | |  | |  | |  | |  | |
      | |  | |       | |  | |  | |  | |  | |        _
      | |  | |   _   | |  | |  | |  | |  | |   _   | |
      | |  | |  | |  | |  | |  | |  | |  | |  | |  | |
  -    -    -    -    -    -    -    -    -    -    -
  2    3    4    5    6    7    8    9   10   11   12
```

# References

Heres is the reference I followed in implementation: [Colonist.io - Designing Balanced Dice](https://blog.colonist.io/designing-balanced-dice/)

## TODO
- Consider using [std::normal_distribution](https://en.cppreference.com/w/cpp/numeric/random/normal_distribution)
- Show Test of Fitness for normal distribution.
- Test if 16-bit as seed is enough to generate float value (0.f - 1.f), and if it would be valid to overlap some bits to use same seed twice, i.e pass a 16-bit seed and use as two distinct 8-bit seed in two different cases.
