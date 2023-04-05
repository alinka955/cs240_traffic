#include <iostream>
#include <random>

using namespace std;

    int main(){
        int initialSeed{24601};
        mt19937 rng;
        uniform_real_distribution<double> rand_double(0.0, 1.0);
        // rand_double will use rng to generate uniform(0,1) variates
        rng.seed(initialSeed);
        return 0;
    }