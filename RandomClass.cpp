#include "RandomClass.h"

        RandomClass::RandomClass(){
        }

        RandomClass::RandomClass(int seed){
             initialSeed = seed;
             rng.seed(initialSeed);
        }

        RandomClass::~RandomClass(){
        }
        double RandomClass::getRandom(){
             uniform_real_distribution<double> rand_double(0.0, 1.0);
             return rand_double(rng);
        }
