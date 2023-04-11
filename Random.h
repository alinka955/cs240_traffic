#include <iostream>
#include <random>
#include <string>

using namespace std;

class Random{
    private:
        int initialSeed;
        mt19937 rng;
    public:
        Random();
        Random(int seed);
        ~Random();

};