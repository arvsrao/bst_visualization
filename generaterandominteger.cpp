#include "generaterandominteger.h"

// default constructor
GenerateRandomInteger::GenerateRandomInteger() {
    int RANGE = 100;
    std::random_device rd;
    std::default_random_engine generator(rd());
    std::uniform_int_distribution<int> distribution(0, RANGE);
    gen = generator;
    dist = distribution;
}

GenerateRandomInteger::GenerateRandomInteger(int _N) : Range(_N) {
  std::random_device rd;
  std::default_random_engine generator(rd());
  std::uniform_int_distribution<int> distribution(0, Range);
  gen = generator;
  dist = distribution;
}

int GenerateRandomInteger::operator()() {
    return dist(gen);
}
