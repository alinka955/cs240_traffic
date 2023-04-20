Daniel Katz, Juneseo Choi, Alina Enikeeva
April 2023
CS240 Professor Douglas Szajda

This is a traffic simulation program. It models the behavior of the vehicles of different types (cars, SUVs, trucks) on a 4-way intersection, regulated by the traffic lights.

To run this program you will need a Makefile, which produces an executable, called 'simulation'. To run the program, type executable followed by the name of the input file and the random number seed.

Main design decisions:
1. Separate files for random generator, reading input and simulation.
2. The main method in Simulation.cpp contains everything needed for the simulation, except for the helper methods to assign the vehicle types and turning directions.
3. Vehicles in this simulation can go only straight or right.


We have tested a few scenarios. The following ones result in unexpected behavior:
1. Intersection lengths of less than or equal to 4 result in segmentation fault, for which we throw an exception. This is due to the fact that we check for the back of a car, starting from index halfsize-4. 
2. The yellow light should be on for at least 1 tick. In other words, yellow_north_east and yellow_east_west parameters should be >=1.
3. Probabilities in input can only be 0.0 to 1.0 and they have to be of type double.
