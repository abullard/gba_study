#ifndef __RANDOM__
#define __RANDOM__

int __qran_seed = 42; // Seed / rnd holder

// update the seed on our random generator and return the old one
static inline int replaceRandomSeed(int seed)
{
    int old = __qran_seed;
    __qran_seed = seed;

    return old;
}

// linear congruential generator ripped from TONC
static inline int random()
{
    __qran_seed = 1664525 * __qran_seed + 1013904223;
    return (__qran_seed >> 16) & 0x7FFF;
}

// random numbers generated between min and max
static inline int randomInRange(int min, int max)
{
    return (random() * (max - min) >> 15) + min;
}

#endif // __RANDOM__
