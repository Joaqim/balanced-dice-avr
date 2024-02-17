#include <Arduino.h>
#include <stdint.h>

// https://www.codeproject.com/Articles/5311070/A-True-Random-Number-Generator-in-Arduino-AVR-ATme
uint8_t random_uint8()
{
    uint8_t V;

    int N = 20;
    // 20 works really fine for uint8, can be increased to reduce patterns.
    // Each cicle takes around 80us on 16Mhz main clock
    // which give a random number almost every 1.5ms.
    for (int i = 0; i < N; i++)
    {
        // Synthesize a voltage on the input
        if (i % 2 == 0)
            ADMUX = 78; // 0b01001110; // [A] // High (1.1V). // See Datasheet Table 23-3 and 23-4
                        // for Atmega328p
        else
            ADMUX = 79; // 0b01001111; // [A] //  Low (0V)

        ADCSRA |= 1 << ADSC; // Start a conversion. See Datasheet for Atmega328p Page 207
        uint8_t low, high;
        // ADSC is cleared when the conversion finishes
        while ((ADCSRA >> ADSC) % 2)
            ;        // wait for the conversion to complete
        low = ADCL;  // do not swap this sequence. Low has to be fetched first.
        high = ADCH; // the value is always between 0-3
        V ^= low;
        V ^= high;

        // Let's shift rotate the number;

        uint8_t last = V % 2;
        V >>= 1;
        V |= last << 7; // "7" will need to change to K-1 to use a K bits wide datatype
        // Disable the ADC
        ADCSRA = 0;

        // Enable the ADC with a randomly selected clock Prescaler between 2 and 128.
        // Since each conversion takes 13 ADC cycles, at 16Mhz system clock,
        // the ADC will now take something in between 1.6us and 104us
        // for each conversion (75us on the average).
        // ADCSRA = 0b10000000 | ((V % 4) << 1); // See Datasheet Table 23-5 for Atmega328p
        ADCSRA = 128 | ((V % 4) << 1); // See Datasheet Table 23-5 for Atmega328p
    }
    return V;
}
