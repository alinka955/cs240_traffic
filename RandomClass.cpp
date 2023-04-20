#include "RandomClass.h"
        
        /**
        * This program is an instance of the Random class that generates 
        * random double values between 0.0 and 1.0. 
        * @author Juneseo Choi
        */
        //default constructor
        RandomClass::RandomClass(){
        }

        //constructor that receives a seed input parameter
        RandomClass::RandomClass(int seed){
             initialSeed = seed;
             rng.seed(initialSeed);
        }
        
        //destructor
        RandomClass::~RandomClass(){
        }
        //getter method, creates one random variable 
        double RandomClass::getRandom(){
             uniform_real_distribution<double> rand_double(0.0, 1.0);
             return rand_double(rng);
        }
