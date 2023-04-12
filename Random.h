#include <iostream>
#include <random>
#include <string>

using namespace std;

class RandomClass{
    private:
        int initialSeed;
        mt19937 rng;

        public:
        RandomClass();
        RandomClass(int seed);
        ~RandomClass();
        double getRandom();
};
