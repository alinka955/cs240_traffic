#include <iostream>
#include "Animator.h"
#include "VehicleBase.h"
#include "RandomClass.h"
#include "readinput.h"
#include <string>
#include <stdexcept>
#include <vector>
#include <map>

/**
 * @brief This class is intended to construct a working simulation of a traffic intersection as well as a
 * corresponding animation. 
 * 
 * This code requires any vehicle class(es) created to be of the VehicleBase reference type, Similarly, 
 * this code requires the animation class and readinput class used to be an instance of the Animator and ReadInput
 * class, respectively, and requires the random generation class instances to be of the RandomClass reference type. 
 * 
 * @author Daniel Katz
 * @author Alina Enikeeva
 * @author Juneseo Choi
 * 
 * Variables:
 * ReadInput readinput - instance of ReadInput class that creates a dictionary of all probability values given in input file
 * int halfsize - determines number of spaces on road before the intersection
 * int maximum_simulated_time - determines maximum number of ticks the simulation can run for
 * int green_east_west - number of ticks the east-west traffic light remains green
 * int green_north_south - number of ticks the north-south traffic light remains green
 * int yellow_east_west - number of ticks the east-west traffic light remains yellow
 * int yellow_north_south - number of ticks the north-south traffic light remains yellow
 * vector<VehicleBase*> northbound - vector of VehicleBase instance addresses representing the northbound lane
 * of the intersection
 * vector<VehicleBase*> southbound - vector of VehicleBase instance addresses representing the southbound lane
 * of the intersection
 * vector<VehicleBase*> eastbound - vector of VehicleBase instance addresses representing the eastbound lane
 * of the intersection
 * vector<VehicleBase*> westbound - vector of VehicleBase instance addresses representing the westbound lane
 * of the intersection
 * double prob_new_vehicle_northbound - probability of new vehicle created to spawn in the northbound lane
 * double prob_new_vehicle_southbound - probability of new vehicle created to spawn in the southbound lane
 * double prob_new_vehicle_eastbound - probability of new vehicle created to spawn in the eastbound lane
 * double prob_new_vehicle_westbound - probability of new vehicle created to spawn in the westbound lane
 * double proportion_of_cars - probability of new vehicle created to be a car
 * double proportion_of_SUVs - probability of new vehicle created to be an SUV
 * double proportion_right_turn_cars - probability of car vehicle to turn right at the intersection
 * double proportion_right_turn_SUVs - probability of SUV vehicle to turn right at the intersection
 * double proportion_right_turn_trucks - probability of truck vehicle to turn right at the intersection
 */

// decides what direction the car will be going (0 for right or 1 for straight)
int getTurnDirection(int carType, double proportion_right_turn_SUVs, double proportion_right_turn_trucks, double proportion_right_turn_cars, double randNum)
{

    if (carType == 0)
    { // if suv, car or straight
        if (randNum < proportion_right_turn_SUVs)
        {
            return 0;
        }
        else
        {
            return 1;
        }
    }
    if (carType == 1)
    { // if car, right or straight
        if (randNum < proportion_right_turn_cars)
        {
            return 0;
        }
        else
        {
            return 1;
        }
    }
    if (carType == 2)
    { // if truck, assign right or straight
        if (randNum < proportion_right_turn_trucks)
        {
            return 0;
        }
        else
        {
            return 1;
        }
    }
    return 0;
}

// decides if a vehicle is an suv, car, or truck
int assignVehicle(double proportion_of_SUVs, double proportion_of_cars, double randNum)
{
    if (randNum <= proportion_of_SUVs)
    { // suv is 0
        return 0;
    }
    else if (proportion_of_SUVs <= randNum && (randNum <= (proportion_of_SUVs + proportion_of_cars)))
    { // car is 1
        return 1;
    }
    else
    { // truck is 2
        return 2;
    }
}

//main method, runs the simulation as well as the animation
int main(int argc, char *argv[])
{
    ReadInput readinput;
    // RandomClass random;
    std::map<std::string, double> inputDict = readinput.getDict(argv[1]);
    // find the values of each variable, read from input
    int halfsize = inputDict["number_of_sections_before_intersection:"];
    int maximum_simulated_time = inputDict["maximum_simulated_time:"];

    int green_east_west = inputDict["green_east_west:"];
    int green_north_south = inputDict["green_north_south:"];

    double prob_new_vehicle_eastbound = inputDict["prob_new_vehicle_eastbound:"];
    double prob_new_vehicle_northbound = inputDict["prob_new_vehicle_northbound:"];
    double prob_new_vehicle_southbound = inputDict["prob_new_vehicle_southbound:"];
    double prob_new_vehicle_westbound = inputDict["prob_new_vehicle_westbound:"];

    double proportion_of_SUVs = inputDict["proportion_of_SUVs:"];
    double proportion_of_cars = inputDict["proportion_of_cars:"];

    double proportion_right_turn_SUVs = inputDict["proportion_right_turn_SUVs:"];
    double proportion_right_turn_cars = inputDict["proportion_right_turn_cars:"];
    double proportion_right_turn_trucks = inputDict["proportion_right_turn_trucks:"];

    int yellow_east_west = inputDict["yellow_east_west:"];
    int yellow_north_south = inputDict["yellow_north_south:"];

    if (halfsize < 5)
    {
        throw std::invalid_argument("halfsize is too small to run the program, please input with a halfsize greater than 4");
        return 0;
    }

    Animator anim(halfsize);

    std::vector<VehicleBase *> westbound(halfsize * 2 + 2, nullptr);
    std::vector<VehicleBase *> eastbound(halfsize * 2 + 2, nullptr);
    std::vector<VehicleBase *> southbound(halfsize * 2 + 2, nullptr);
    std::vector<VehicleBase *> northbound(halfsize * 2 + 2, nullptr);
    char dummy;

    std::vector<VehicleBase *> tempWestbound;
    std::vector<VehicleBase *> tempEastbound;
    std::vector<VehicleBase *> tempSouthbound;
    std::vector<VehicleBase *> tempNorthbound;

    int numClicks = 0;
    anim.setVehiclesNorthbound(northbound);
    anim.setVehiclesWestbound(westbound);
    anim.setVehiclesSouthbound(southbound);
    anim.setVehiclesEastbound(eastbound); // initial construction of intersection
    anim.setLightNorthSouth(LightColor::red);
    anim.setLightEastWest(LightColor::green);
    anim.draw(numClicks);
    RandomClass random(std::stoi(argv[2])); // reads random seed for arg 2
    int GYticksEW = green_east_west + yellow_east_west;
    int GYticksNS = green_north_south + yellow_north_south;
    bool greenEW = true;  // bool values for if its green, yellow, red
    bool greenNS = false; // initialized at green for east/west and red for north/south
    bool yellowNS = false;
    bool yellowEW = false;
    bool redEW = false;
    bool redNS = true;

    int light_ticksEW = 0;
    int light_ticksNS = 0;
    // tracks light switches

    // start of while loop for each iteration
    while (numClicks < maximum_simulated_time)
    {
        //eastbound lane move
        for (int i = halfsize * 2 + 2; i >halfsize; i--) // moves all eastbound after intersection
        {
            eastbound[i] = eastbound[i - 1];
        }
        eastbound[halfsize] = nullptr;

        // moves car into intersection eastbound
        if (GYticksEW - light_ticksEW > 2 && eastbound[halfsize - 1] != nullptr && (yellowEW || greenEW))
        {
            int backOfCar = halfsize - 1;

            // checks to find the back of car/truck/suv
            while (halfsize - 1 >= backOfCar)
            {
                if ((eastbound[backOfCar - 1] != nullptr) && (eastbound[backOfCar] != nullptr) &&
                    (eastbound[backOfCar]->getVehicleID() != eastbound[backOfCar - 1]->getVehicleID()))
                {
                    break;
                }
                else if (eastbound[backOfCar] == nullptr)
                {
                    break;
                }
                backOfCar--;
            }

            if ((halfsize - 1 - backOfCar + 3) <= (GYticksEW - light_ticksEW))
            {
                eastbound[halfsize] = eastbound[halfsize - 1];
                eastbound[halfsize - 1] = nullptr;
            }
        }

        // moves all eastbound up to halfsize

        for (int i = halfsize - 1; i > 0; i--)
        {
            if (eastbound[i] == nullptr)
            {
                eastbound[i] = eastbound[i - 1];
                eastbound[i - 1] = nullptr;
            }
        }

        // northbound lane move
        for (int i = halfsize * 2 + 2; i >= halfsize; i--) // moves all northbound after intersection
        {
            northbound[i] = northbound[i - 1];
        }
        northbound[halfsize] = nullptr;

        // moves car into intersection
        if ((GYticksNS - light_ticksNS > 2) && (northbound[halfsize - 1] != nullptr) && (yellowNS || greenNS))
        {
            int backOfCar = halfsize - 1;

            // checks to find the back of car/truck/suv
            while (halfsize - 1 >= backOfCar)
            {
                if ((northbound[backOfCar - 1] != nullptr) && (northbound[backOfCar] != nullptr) &&
                    (northbound[backOfCar]->getVehicleID() != northbound[backOfCar - 1]->getVehicleID()))
                {
                    break;
                }
                else if (northbound[backOfCar] == nullptr)
                {
                    break;
                }
                backOfCar--;
            }

            if ((halfsize - 1 - backOfCar + 3) <= (GYticksNS - light_ticksNS))  
            {
                northbound[halfsize] = northbound[halfsize - 1];
                northbound[halfsize - 1] = nullptr;
            }
        }

        // moves all northbound up to halfsize

        for (int i = halfsize - 1; i > 0; i--)
        {
            if ((northbound[i] == nullptr))
            {
                northbound[i] = northbound[i - 1];
                northbound[i - 1] = nullptr;
            }
        }

    
        //southbound lane move
        for (int i = halfsize * 2 + 2; i >= halfsize; i--) // moves all southbound after intersection
        {
            southbound[i] = southbound[i - 1];
        }
        southbound[halfsize] = nullptr;

        // moves car into intersection
        if (GYticksNS - light_ticksNS > 2 && southbound[halfsize - 1] != nullptr && (yellowNS || greenNS))
        {
            int backOfCar = halfsize - 1;

            // checks to find the back of car/truck/suv
            while (halfsize - 1 >= backOfCar)
            {
                if ((southbound[backOfCar - 1] != nullptr) && (southbound[backOfCar] != nullptr) &&
                    (southbound[backOfCar]->getVehicleID() != southbound[backOfCar - 1]->getVehicleID()))
                {
                    break;
                }
                else if (southbound[backOfCar] == nullptr)
                {
                    break;
                }
                backOfCar--;
            }

            if ((halfsize - 1 - backOfCar + 3) <= (GYticksNS - light_ticksNS))
            {
                southbound[halfsize] = southbound[halfsize - 1];
                southbound[halfsize - 1] = nullptr;
            }
        }

        // moves all southbound up to halfsize

        for (int i = halfsize - 1; i > 0; i--)
        {
            if (southbound[i] == nullptr)
            {
                southbound[i] = southbound[i - 1];
                southbound[i - 1] = nullptr;
            }
        }

        // westbound lane move
        for (int i = halfsize * 2 + 2; i >= halfsize; i--) // moves all westbound after intersection
        {
            westbound[i] = westbound[i - 1];
        }
        westbound[halfsize] = nullptr;

        // moves car into intersection
        if (GYticksEW - light_ticksEW > 2 && westbound[halfsize - 1] != nullptr &&
            (yellowEW || greenEW))
        {
            int backOfCar = halfsize - 1;

            // checks to find the back of car/truck/suv
            while (halfsize - 1 >= backOfCar)
            {
                if ((westbound[backOfCar - 1] != nullptr) && (westbound[backOfCar] != nullptr) &&
                    (westbound[backOfCar]->getVehicleID() != westbound[backOfCar - 1]->getVehicleID()))
                {
                    break;
                }
                else if (westbound[backOfCar] == nullptr)
                {
                    break;
                }
                backOfCar--;
            }

            if ((halfsize - 1 - backOfCar + 3) <= (GYticksEW - light_ticksEW))
            {
                westbound[halfsize] = westbound[halfsize - 1];
                westbound[halfsize - 1] = nullptr;
            }
        }

        // moves all westbound up to halfsize

        for (int i = halfsize - 1; i > 0; i--)
        {
            if (westbound[i] == nullptr)
            {
                westbound[i] = westbound[i - 1];
                westbound[i - 1] = nullptr;
            }
        }
        // start of spawning
        // eastbound spawning
        if (random.getRandom() < prob_new_vehicle_eastbound)
        {
            int carType = assignVehicle(proportion_of_SUVs, proportion_of_cars, random.getRandom()); // chooses car type
            int turnDirect = getTurnDirection(carType, proportion_right_turn_SUVs,
                                              proportion_right_turn_trucks, proportion_right_turn_cars, random.getRandom());

            if (tempEastbound.empty())
            {
                if (carType == 0 && turnDirect == 0) // spawns SUV and turns right
                {
                    // pushes to temp vector the correct size of an SUV, first checks if temp is empty
                    VehicleBase *v = new VehicleBase(VehicleType::suv, Direction::east, turnDirection::right);
                    tempEastbound.push_back(v);
                    tempEastbound.push_back(v);
                    tempEastbound.push_back(v);
                }
                else if (carType == 0 && turnDirect == 1) // spawns SUV and goes straight
                {
                    // pushes to temp vector the correct size of an SUV, first checks if temp is empty
                    VehicleBase *v = new VehicleBase(VehicleType::suv, Direction::east, turnDirection::straight);
                    tempEastbound.push_back(v);
                    tempEastbound.push_back(v);
                    tempEastbound.push_back(v);
                }

                else if (carType == 1 && turnDirect == 0) // spawns car and turns right
                {

                    // pushes to temp vector the correct size of a car, first checks if temp is empty
                    VehicleBase *v = new VehicleBase(VehicleType::car, Direction::east, turnDirection::right);
                    tempEastbound.push_back(v);
                    tempEastbound.push_back(v);
                }
                else if (carType == 1 && turnDirect == 1) // spawns car and goes straight
                {
                    // pushes to temp vector the correct size of a car, first checks if temp is empty
                    VehicleBase *v = new VehicleBase(VehicleType::car, Direction::east, turnDirection::straight);
                    tempEastbound.push_back(v);
                    tempEastbound.push_back(v);
                }
                else if (carType == 2 && turnDirect == 0) // spawns car and goes straight
                {
                    // pushes to temp vector the correct size of a car, first checks if temp is empty
                    VehicleBase *v = new VehicleBase(VehicleType::truck, Direction::east, turnDirection::right);
                    tempEastbound.push_back(v);
                    tempEastbound.push_back(v);
                    tempEastbound.push_back(v);
                    tempEastbound.push_back(v);
                }
                else
                {
                    // pushes to temp vector the correct size of a truck, first checks if temp is empty
                    VehicleBase *v = new VehicleBase(VehicleType::truck, Direction::east, turnDirection::straight);
                    tempEastbound.push_back(v);
                    tempEastbound.push_back(v);
                    tempEastbound.push_back(v);
                    tempEastbound.push_back(v);
                }
                VehicleBase::vehicleCount++;
            }
        }

        // northbound spawning
        if (random.getRandom() < prob_new_vehicle_northbound)
        {
            int carType = assignVehicle(proportion_of_SUVs, proportion_of_cars, random.getRandom()); // chooses car type
            int turnDirect = getTurnDirection(carType, proportion_right_turn_SUVs,
                                              proportion_right_turn_trucks, proportion_right_turn_cars, random.getRandom());

            if (tempNorthbound.empty())
            {
                if (carType == 0 && turnDirect == 0) // spawns SUV and turns right
                {
                    // pushes to temp vector the correct size of an SUV, first checks if temp is empty
                    VehicleBase *v = new VehicleBase(VehicleType::suv, Direction::north, turnDirection::right);
                    tempNorthbound.push_back(v);
                    tempNorthbound.push_back(v);
                    tempNorthbound.push_back(v);
                }
                else if (carType == 0 && turnDirect == 1) // spawns SUV and goes straight
                {
                    // pushes to temp vector the correct size of an SUV, first checks if temp is empty
                    VehicleBase *v = new VehicleBase(VehicleType::suv, Direction::north, turnDirection::straight);
                    tempNorthbound.push_back(v);
                    tempNorthbound.push_back(v);
                    tempNorthbound.push_back(v);
                }

                else if (carType == 1 && turnDirect == 0) // spawns car and turns right
                {

                    // pushes to temp vector the correct size of a car, first checks if temp is empty
                    VehicleBase *v = new VehicleBase(VehicleType::car, Direction::north, turnDirection::right);
                    tempNorthbound.push_back(v);
                    tempNorthbound.push_back(v);
                }
                else if (carType == 1 && turnDirect == 1) // spawns car and goes straight
                {
                    // pushes to temp vector the correct size of a car, first checks if temp is empty
                    VehicleBase *v = new VehicleBase(VehicleType::car, Direction::north, turnDirection::straight);
                    tempNorthbound.push_back(v);
                    tempNorthbound.push_back(v);
                }
                else if (carType == 2 && turnDirect == 0) // spawns car and goes straight
                {
                    // pushes to temp vector the correct size of a car, first checks if temp is empty
                    VehicleBase *v = new VehicleBase(VehicleType::truck, Direction::north, turnDirection::right);
                    tempNorthbound.push_back(v);
                    tempNorthbound.push_back(v);
                    tempNorthbound.push_back(v);
                    tempNorthbound.push_back(v);
                }
                else
                {
                    // pushes to temp vector the correct size of a truck, first checks if temp is empty
                    VehicleBase *v = new VehicleBase(VehicleType::truck, Direction::north, turnDirection::straight);
                    tempNorthbound.push_back(v);
                    tempNorthbound.push_back(v);
                    tempNorthbound.push_back(v);
                    tempNorthbound.push_back(v);
                }
                VehicleBase::vehicleCount++;
            }
        }

        // southbound spawning
        if (random.getRandom() < prob_new_vehicle_southbound)
        { // checks prob of southbound spawn
            int carType = assignVehicle(proportion_of_SUVs, proportion_of_cars,
                                        random.getRandom()); // chooses car type
            int turnDirect = getTurnDirection(carType, proportion_right_turn_SUVs,
                                              proportion_right_turn_trucks, proportion_right_turn_cars, random.getRandom());

            if (tempSouthbound.empty())
            {

                if (carType == 0 && turnDirect == 0) // spawns SUV and turns right
                {
                    // pushes to temp vector the correct size of an suv, first checks if temp is empty
                    VehicleBase *v = new VehicleBase(VehicleType::suv, Direction::south, turnDirection::right);
                    tempSouthbound.push_back(v);
                    tempSouthbound.push_back(v);
                    tempSouthbound.push_back(v);
                }
                else if (carType == 0 && turnDirect == 1) // spawns SUV and goes straight
                {
                    // pushes to temp vector the correct size of an suv, first checks if temp is empty
                    VehicleBase *v = new VehicleBase(VehicleType::suv, Direction::south, turnDirection::straight);
                    tempSouthbound.push_back(v);
                    tempSouthbound.push_back(v);
                    tempSouthbound.push_back(v);
                }
                else if (carType == 1 && turnDirect == 0) // spawns car and turns right
                {
                    // pushes to temp vector the correct size of an car, first checks if temp is empty
                    VehicleBase *v = new VehicleBase(VehicleType::car, Direction::south, turnDirection::right);
                    tempSouthbound.push_back(v);
                    tempSouthbound.push_back(v);
                }
                else if (carType == 1 && turnDirect == 1) // spawns car and goes straight
                {
                    // pushes to temp vector the correct size of an car, first checks if temp is empty
                    VehicleBase *v = new VehicleBase(VehicleType::car, Direction::south, turnDirection::straight);
                    tempSouthbound.push_back(v);
                    tempSouthbound.push_back(v);
                }
                else if (carType == 2 && turnDirect == 0) // truck and turns right
                {

                    VehicleBase *v = new VehicleBase(VehicleType::truck, Direction::south, turnDirection::right);
                    tempSouthbound.push_back(v);
                    tempSouthbound.push_back(v);
                    tempSouthbound.push_back(v);
                    tempSouthbound.push_back(v);
                }
                else // truck and goes straight
                {

                    VehicleBase *v = new VehicleBase(VehicleType::truck, Direction::south, turnDirection::straight);
                    tempSouthbound.push_back(v);
                    tempSouthbound.push_back(v);
                    tempSouthbound.push_back(v);
                    tempSouthbound.push_back(v);
                }
                VehicleBase::vehicleCount++;
            }
        }
        //westbound spawning
        if (random.getRandom() < prob_new_vehicle_westbound)
        {
            int carType = assignVehicle(proportion_of_SUVs, proportion_of_cars, random.getRandom()); // chooses car type
            int turnDirect = getTurnDirection(carType, proportion_right_turn_SUVs,
                                              proportion_right_turn_trucks, proportion_right_turn_cars, random.getRandom());

            if (tempWestbound.empty())
            {
                if (carType == 0 && turnDirect == 0) // spawns SUV and turns right
                {
                    if (tempWestbound.empty())
                    { // pushes to temp vector the correct size of an SUV, first checks if temp is empty
                        VehicleBase *v = new VehicleBase(VehicleType::suv, Direction::west, turnDirection::right);
                        tempWestbound.push_back(v);
                        tempWestbound.push_back(v);
                        tempWestbound.push_back(v);
                    }
                }
                else if (carType == 0 && turnDirect == 1) // spawns SUV and goes straight
                {
                    if (tempWestbound.empty())
                    { // pushes to temp vector the correct size of an SUV, first checks if temp is empty
                        VehicleBase *v = new VehicleBase(VehicleType::suv, Direction::west, turnDirection::straight);
                        tempWestbound.push_back(v);
                        tempWestbound.push_back(v);
                        tempWestbound.push_back(v);
                    }
                }

                else if (carType == 1 && turnDirect == 0) // spawns car and turns right
                {
                    // pushes to temp vector the correct size of a car, first checks if temp is empty
                    VehicleBase *v = new VehicleBase(VehicleType::car, Direction::west, turnDirection::right);
                    tempWestbound.push_back(v);
                    tempWestbound.push_back(v);
                }
                else if (carType == 1 && turnDirect == 1) // spawns car and goes straight
                {
                    // pushes to temp vector the correct size of a car, first checks if temp is empty
                    VehicleBase *v = new VehicleBase(VehicleType::car, Direction::west, turnDirection::straight);
                    tempWestbound.push_back(v);
                    tempWestbound.push_back(v);
                }
                else if (carType == 2 && turnDirect == 0) // spawns car and goes straight
                {
                    // pushes to temp vector the correct size of a car, first checks if temp is empty
                    VehicleBase *v = new VehicleBase(VehicleType::truck, Direction::west, turnDirection::right);
                    tempWestbound.push_back(v);
                    tempWestbound.push_back(v);
                    tempWestbound.push_back(v);
                    tempWestbound.push_back(v);
                }
                else
                {
                    // pushes to temp vector the correct size of a truck, first checks if temp is empty
                    VehicleBase *v = new VehicleBase(VehicleType::truck, Direction::west, turnDirection::straight);
                    tempWestbound.push_back(v);
                    tempWestbound.push_back(v);
                    tempWestbound.push_back(v);
                    tempWestbound.push_back(v);
                }
                VehicleBase::vehicleCount++;
            }
        }

        // end of adding cars
        
        //code to update light ticks and light colors
        std::cin.get(dummy);
        numClicks++;
        light_ticksNS++;
        light_ticksEW++;
        // checks conditions for NS, EW red, yellow, green
        if (redNS && light_ticksNS >= GYticksEW)
        {
            redNS = false;
            greenNS = true;
            light_ticksNS = 0;
        }
        else if (greenNS && light_ticksNS >= green_north_south)
        {
            greenNS = false;
            yellowNS = true;
        }
        else if (yellowNS && light_ticksNS >= GYticksNS)
        {
            yellowNS = false;
            redNS = true;
            light_ticksNS = 0;
        }

        if (redEW && light_ticksEW >= GYticksNS)

        {
            redEW = false;
            greenEW = true;
            light_ticksEW = 0;
        }

        else if (greenEW && light_ticksEW >= green_east_west)
        {
            greenEW = false;
            yellowEW = true;
        }

        else if (yellowEW && light_ticksEW >= GYticksEW)
        {
            yellowEW = false;
            redEW = true;
            light_ticksEW = 0;
        }

        if (!tempEastbound.empty() && eastbound[0] == nullptr)
        {                                        // checks that temp is not empty
            eastbound[0] = tempEastbound.back(); // sets to actual value
            tempEastbound.pop_back();            // removes temp
        }
        if (!tempNorthbound.empty() && northbound[0] == nullptr)
        {                                          // checks that temp is not empty
            northbound[0] = tempNorthbound.back(); // sets to actual value
            tempNorthbound.pop_back();             // removes temp
        }
        if (!tempSouthbound.empty() && southbound[0] == nullptr)
        {                                          // checks that temp is not empty
            southbound[0] = tempSouthbound.back(); // sets to actual value
            tempSouthbound.pop_back();             // removes temp
        }
        if (!tempWestbound.empty() && westbound[0] == nullptr)
        {                                        // checks that temp is not empty
            westbound[0] = tempWestbound.back(); // sets to actual value
            tempWestbound.pop_back();            // removes temp
        }
        
        //checks if vehicle is turning right, moves to appropriate lane if vehicle is turning right at intersection
        if ((eastbound[halfsize] != nullptr) && (eastbound[halfsize])->getVehicleTurnDirection() == turnDirection::right)
        {
            southbound[halfsize + 1] = eastbound[halfsize];
            eastbound[halfsize] = nullptr;
        }
        if ((westbound[halfsize] != nullptr) && (westbound[halfsize])->getVehicleTurnDirection() == turnDirection::right)
        {
            northbound[halfsize + 1] = westbound[halfsize];
            westbound[halfsize] = nullptr;
        }
        if ((northbound[halfsize] != nullptr) && (northbound[halfsize])->getVehicleTurnDirection() == turnDirection::right)
        {
            eastbound[halfsize + 1] = northbound[halfsize];
            northbound[halfsize] = nullptr;
        }
        if ((southbound[halfsize] != nullptr) && (southbound[halfsize])->getVehicleTurnDirection() == turnDirection::right)
        {
            westbound[halfsize + 1] = southbound[halfsize];
            southbound[halfsize] = nullptr;
        }

        anim.setVehiclesNorthbound(northbound); // reconstructs intersection with appropriate numClicks
        anim.setVehiclesWestbound(westbound);
        anim.setVehiclesSouthbound(southbound);
        anim.setVehiclesEastbound(eastbound);
        
        //sets light color of animation to appropriate color 
        if (greenEW && redNS)
        {
            anim.setLightNorthSouth(LightColor::red);
            anim.setLightEastWest(LightColor::green);
        }
        else if (yellowEW && redNS)
        {
            anim.setLightNorthSouth(LightColor::red);
            anim.setLightEastWest(LightColor::yellow);
        }
        else if (greenNS && redEW)
        {
            anim.setLightNorthSouth(LightColor::green);
            anim.setLightEastWest(LightColor::red);
        }
        else if (yellowNS && redEW)
        {
            anim.setLightNorthSouth(LightColor::yellow);
            anim.setLightEastWest(LightColor::red);
        }

        else if (greenNS && yellowEW)
        {
            anim.setLightNorthSouth(LightColor::green);
            anim.setLightEastWest(LightColor::yellow);
        }
        else if (yellowNS && greenEW)
        {
            anim.setLightNorthSouth(LightColor::yellow);
            anim.setLightEastWest(LightColor::green);
        }
        anim.draw(numClicks);
    }
}
