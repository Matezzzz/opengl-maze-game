#include "random.h"

Random::Random() : mersenne(new mt19937(time(new time_t)))
{
    //time_t timer;
    //mersenne = new mt19937(time(&timer));
}

Random::randint(int from, int to)
{
    std::uniform_int_distribution<> range(from, to);
    return range(*mersenne);
}

Random::randint(int to)
{
    return randint(0, to);
}
