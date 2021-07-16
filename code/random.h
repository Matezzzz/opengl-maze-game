#ifndef RANDOM_H
#define RANDOM_H
#include <random>
#include <ctime>

using std::mt19937;

class Random
{
    mt19937* mersenne;
public:
    Random();
    int randint(int from, int to);
    int randint(int to);
};

#endif // RANDOM_H
