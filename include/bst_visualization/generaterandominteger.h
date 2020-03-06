#ifndef GENERATERANDOMINTEGER_H
#define GENERATERANDOMINTEGER_H

#include <random>

struct GenerateRandomInteger
{
    std::default_random_engine gen;
    std::uniform_int_distribution<int> dist;
    int Range;

    GenerateRandomInteger();
    GenerateRandomInteger(int _N);

    int operator()();

};

#endif // GENERATERANDOMINTEGER_H
