#include <iostream>
#include <random>
#include <string>

using namespace std;

class Random{

        private:
             int initialSeed;
             mt19937 rng;
        public Random::Random(){
        }
        public Random::Random(int seed){
             initialSeed = seed;
             uniform_real_distribution<double> rand_double(0.0, 1.0);
             rng.seed(intialSeed);
        }

        public ~Random::Random(){
             delete[] rng;
             delete[] initialSeed;
        }
}
