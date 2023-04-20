Daniel Katz, Juneseo Choi, Alina Enikeeva
April 2023
CS240 Professor Douglas Szajda

This is a traffic simulation program. It models the behavior of the vehicles of different types (cars, SUVs, trucks) on a 4-way intersection, regulated by the traffic lights.

To run this program you will need a Makefile, which produces an executable, called 'simulation'. To run the program type executable followed by the name of the input file and the random number seed.

We have tested a few scenarios:
1. Different lengths of intersections, from 3 to 10
        Note: intersection lengths of 3 and 4 result in segmentation fault.
                This is due to the fact that we check for the back of a car, starting from index halfsize-4.
2. The yellow light should be on for at least 1 tick. In other words, yellow_north_east and yellow_east_west parameters should be >=1.
3. In very specific insatnces, when green and yellow lights are set to small values, vehicles split.
