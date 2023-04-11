
#include "RandomClass.h"

        RandomClass::RandomClass(){
        }

        RandomClass::RandomClass(int seed){
             initialSeed = seed;
             uniform_real_distribution<double> rand_double(0.0, 1.0);
             rng.seed(initialSeed);
        }

        RandomClass::~RandomClass(){
        }

        int main(){
             return 0;
        }
