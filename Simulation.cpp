#include <iostream>
#include "Animator.h"
#include "VehicleBase.h"
#include "RandomClass.h"
#include <vector>
#include <map>
#include "readinput.h"
#include <string>

// decides what direction the car will be going (0 for right or 1 for straight)
int getTurnDirection(int carType, double proportion_right_turn_SUVs, double proportion_right_turn_trucks, double proportion_right_turn_cars, double randNum)
{

    if (carType == 0)
    { // if suv, car or straight
        if (randNum < proportion_right_turn_SUVs)
        {
            // cout << "right: suv" << endl;
            return 0;
        }
        else
        {
            // cout << "straight: suv" << endl;
            return 1;
        }
    }
    if (carType == 1)
    { // if car, right or straight
        if (randNum < proportion_right_turn_cars)
        {
            // cout << "right: car" << endl;
            return 0;
        }
        else
        {
            // cout << "straight: car" << endl;
            return 1;
        }
    }
    if (carType == 2)
    { // if truck, assign right or straight
        if (randNum < proportion_right_turn_trucks)
        {
            // cout << "right: truck" << endl;
            return 0;
        }
        else
        {
            // cout << "straight: truck" << endl;
            return 1;
        }
    }
}

// decides if a vehicle is an suv, car, or truck
int assignVehicle(double proportion_of_SUVs, double proportion_of_cars, double randNum)
{
    if (randNum < proportion_of_SUVs)
    { // suv is 0
        return 0;
    }
    else if (proportion_of_SUVs < randNum && (randNum < (proportion_of_SUVs + proportion_of_cars)))
    { // car is 1
        return 1;
    }
    else
    { // truck is 2
        return 2;
    }
}

int main(int argc, char *argv[])
{
    ReadInput readinput;
    // RandomClass random;
    std::map<std::string, double> inputDict = readinput.getDict(argv[1]);
    // find the values of each variable, read from input
    size_t halfsize = inputDict["number_of_sections_before_intersection:"];
    size_t maximum_simulated_time = inputDict["maximum_simulated_time:"];

    size_t green_east_west = inputDict["green_east_west:"];
    size_t green_north_south = inputDict["green_north_south:"];

    double prob_new_vehicle_eastbound = inputDict["prob_new_vehicle_eastbound:"];
    double prob_new_vehicle_northbound = inputDict["prob_new_vehicle_northbound:"];
    double prob_new_vehicle_southbound = inputDict["prob_new_vehicle_southbound:"];
    double prob_new_vehicle_westbound = inputDict["prob_new_vehicle_westbound:"];

    double proportion_of_SUVs = inputDict["proportion_of_SUVs:"];
    double proportion_of_cars = inputDict["proportion_of_cars:"];

    double proportion_right_turn_SUVs = inputDict["proportion_right_turn_SUVs:"];
    double proportion_right_turn_cars = inputDict["proportion_right_turn_cars:"];
    double proportion_right_turn_trucks = inputDict["proportion_right_turn_trucks:"];

    size_t yellow_east_west = inputDict["yellow_east_west:"];
    size_t yellow_north_south = inputDict["yellow_north_south:"];

    double proportion_left_turn_SUVs = inputDict["proportion_left_turn_SUVs:"];
    double proportion_left_turn_cars = inputDict["proportion_left_turn_cars:"];
    double proportion_left_turn_trucks = inputDict["proportion_left_turn_trucks:"];

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
    RandomClass random(std::stoi(argv[2])); //reads random seed for arg 2
    int NSredTicks = green_east_west + yellow_east_west;
    int EWredTicks = green_north_south + yellow_north_south;
    bool greenEW = true;  // bool values for if its green, yellow, red
    bool greenNS = false; // initialized at green for east/west and red for north/south
    bool yellowNS = false;
    bool yellowEW = false;
    bool redEW = false;
    bool redNS = true;

    size_t light_ticksEW = 0;
    size_t light_ticksNS = 0; // tracks light switches

    //start of while loop for each iteration
    while (numClicks < maximum_simulated_time)
    {
        double randNum = random.getRandom();

        
        for (int i = halfsize * 2 + 2; i > halfsize; i--) // moves all eastbound after intersection
        {
            eastbound[i] = eastbound[i - 1];
        }
        eastbound[halfsize] = nullptr;
    

        //moves car into intersection
        if (NSredTicks - light_ticksEW > 2 && eastbound[halfsize - 1] != nullptr
                                            && ((yellowEW) || greenEW))
        {
            cout << "halfsize: " << halfsize << endl;
            int backOfCar = halfsize - 1;

            // checks to find the back of car/truck/suv
            while (halfsize - 4 < backOfCar)
            { 
                if ((eastbound[backOfCar - 1] != nullptr) && (eastbound[backOfCar] != nullptr) &&
                    (eastbound[backOfCar]->getVehicleID() != eastbound[backOfCar - 1]->getVehicleID()))
                {
                    cout << "stopped" << endl;
                    break;
                }
                else if (eastbound[backOfCar] == nullptr || eastbound[backOfCar] == nullptr)
                {
                    cout << "null" << endl;
                    break;
                }
                backOfCar--;
                cout << "current backOfCar: " << backOfCar << endl;
            }
            backOfCar++;

	    if((halfsize - 1) - backOfCar + 3 <= (NSredTicks - light_ticksEW)){
            	eastbound[halfsize] = eastbound[halfsize - 1];
            	eastbound[halfsize - 1] = nullptr;
                //cout << 'AHHH' << endl;
		}
            
        }

        // moves all eastbound up to halfsize
        
        for (int i = halfsize - 1; i > 0; i--) 
            {
            if ((redEW && (eastbound[i] == nullptr)) || greenEW || yellowEW)
            {
                eastbound[i] = eastbound[i - 1];
                eastbound[i - 1] = nullptr;
            }
        }




        if (random.getRandom() < prob_new_vehicle_eastbound) // checks prob of eastbound spawn
        {
            int carType = assignVehicle(proportion_of_SUVs, proportion_of_cars,
                                        random.getRandom()); // chooses car type

            int turnDirect = getTurnDirection(carType, proportion_right_turn_SUVs, proportion_right_turn_trucks, proportion_right_turn_cars, random.getRandom());

            if (carType == 0 && turnDirect == 0) // spawns SUV and turns right
            {                                    // suv
                if (tempEastbound.empty())
                { // pushes to temp vector the correct size of an suv, first checks if temp is empty
                    VehicleBase *v = new VehicleBase(VehicleType::suv, Direction::east, turnDirection::right);
                    tempEastbound.push_back(v);
                    tempEastbound.push_back(v);
                    tempEastbound.push_back(v);
                }
            }

            if (carType == 0 && turnDirect == 1) // spawns SUV and goes straight
            {                                    // suv
                if (tempEastbound.empty())
                { // pushes to temp vector the correct size of an suv, first checks if temp is empty
                    VehicleBase *v = new VehicleBase(VehicleType::suv, Direction::east, turnDirection::straight);
                    tempEastbound.push_back(v);
                    tempEastbound.push_back(v);
                    tempEastbound.push_back(v);
                }
            }
            if (carType == 1 && turnDirect == 0) // spawns car and goes right
            {                                    // suv
                if (tempEastbound.empty())
                { // pushes to temp vector the correct size of an suv, first checks if temp is empty
                    VehicleBase *v = new VehicleBase(VehicleType::car, Direction::east, turnDirection::right);
                    tempEastbound.push_back(v);
                    tempEastbound.push_back(v);
                }
            }

            else if (carType == 1 && turnDirect == 1) // spawns car and goes straight
            {
                if (tempEastbound.empty())
                {
                    VehicleBase *v = new VehicleBase(VehicleType::car, Direction::east, turnDirection::straight);
                    tempEastbound.push_back(v);
                    tempEastbound.push_back(v);
                }
            }
            else if (carType == 2 && turnDirect == 0) // truck and right
            {
                if (tempEastbound.empty())
                {
                    VehicleBase *v = new VehicleBase(VehicleType::truck, Direction::east, turnDirection::right);
                    tempEastbound.push_back(v);
                    tempEastbound.push_back(v);
                    tempEastbound.push_back(v);
                    tempEastbound.push_back(v);
                }
            }
            else
            { // truck and straight
                if (tempEastbound.empty())
                {
                    VehicleBase *v = new VehicleBase(VehicleType::truck, Direction::east, turnDirection::straight);
                    tempEastbound.push_back(v);
                    tempEastbound.push_back(v);
                    tempEastbound.push_back(v);
                    tempEastbound.push_back(v);
                }
            }
            VehicleBase::vehicleCount++;
        }
        /*
        // northbound spawning
        if (random.getRandom() < prob_new_vehicle_northbound)
        {
            int carType = assignVehicle(proportion_of_SUVs, proportion_of_cars, random.getRandom()); // chooses car type
            int turnDirect = getTurnDirection(carType, proportion_right_turn_SUVs,
                                              proportion_right_turn_trucks, proportion_right_turn_cars, random.getRandom());

            if (carType == 0 && turnDirect == 0) // spawns SUV and turns right
            {
                if (tempEastbound.empty())
                { // pushes to temp vector the correct size of an SUV, first checks if temp is empty
                    VehicleBase *v = new VehicleBase(VehicleType::suv, Direction::north, turnDirection::right);
                    tempNorthbound.push_back(v);
                    tempNorthbound.push_back(v);
                    tempNorthbound.push_back(v);
                }
            }
            else if (carType == 0 && turnDirect == 1) // spawns SUV and goes straight
            {
                if (tempEastbound.empty())
                { // pushes to temp vector the correct size of an SUV, first checks if temp is empty
                    VehicleBase *v = new VehicleBase(VehicleType::suv, Direction::north, turnDirection::straight);
                    tempNorthbound.push_back(v);
                    tempNorthbound.push_back(v);
                    tempNorthbound.push_back(v);
                }
            }

            else if (carType == 1 && turnDirect == 0) // spawns car and turns right
            {
                if (tempEastbound.empty())
                { // pushes to temp vector the correct size of a car, first checks if temp is empty
                    VehicleBase *v = new VehicleBase(VehicleType::car, Direction::north, turnDirection::right);
                    tempNorthbound.push_back(v);
                    tempNorthbound.push_back(v);
                }
            }
            else if (carType == 1 && turnDirect == 1) // spawns car and goes straight
            {
                if (tempEastbound.empty())
                { // pushes to temp vector the correct size of a car, first checks if temp is empty
                    VehicleBase *v = new VehicleBase(VehicleType::car, Direction::north, turnDirection::straight);
                    tempNorthbound.push_back(v);
                    tempNorthbound.push_back(v);
                }
            }
            else if (carType == 2 && turnDirect == 0) // spawns car and goes straight
            {
                if (tempEastbound.empty())
                { // pushes to temp vector the correct size of a car, first checks if temp is empty
                    VehicleBase *v = new VehicleBase(VehicleType::truck, Direction::north, turnDirection::right);
                    tempNorthbound.push_back(v);
                    tempNorthbound.push_back(v);
                    tempNorthbound.push_back(v);
                    tempNorthbound.push_back(v);
                }
            }
            else
            {
                if (tempNorthbound.empty())
                { // pushes to temp vector the correct size of a truck, first checks if temp is empty
                    VehicleBase *v = new VehicleBase(VehicleType::truck, Direction::north, turnDirection::straight);
                    tempNorthbound.push_back(v);
                    tempNorthbound.push_back(v);
                    tempNorthbound.push_back(v);
                    tempNorthbound.push_back(v);
                }
            }
            VehicleBase::vehicleCount++;
        }

        // southbound spawning
        if (random.getRandom() < prob_new_vehicle_southbound)
        { // checks prob of southbound spawn
            int carType = assignVehicle(proportion_of_SUVs, proportion_of_cars,
                                        random.getRandom()); // chooses car type
            int turnDirect = getTurnDirection(carType, proportion_right_turn_SUVs,
                                              proportion_right_turn_trucks, proportion_right_turn_cars, random.getRandom());

            if (carType == 0 && turnDirect == 0) // spawns SUV and turns right
            {
                if (tempSouthbound.empty())
                { // pushes to temp vector the correct size of an suv, first checks if temp is empty
                    VehicleBase *v = new VehicleBase(VehicleType::suv, Direction::south, turnDirection::right);
                    tempSouthbound.push_back(v);
                    tempSouthbound.push_back(v);
                    tempSouthbound.push_back(v);
                }
            }
            else if (carType == 0 && turnDirect == 1) // spawns SUV and goes straight
            {
                if (tempSouthbound.empty())
                { // pushes to temp vector the correct size of an suv, first checks if temp is empty
                    VehicleBase *v = new VehicleBase(VehicleType::suv, Direction::south, turnDirection::straight);
                    tempSouthbound.push_back(v);
                    tempSouthbound.push_back(v);
                    tempSouthbound.push_back(v);
                }
            }
            else if (carType == 1 && turnDirect == 0) // spawns car and turns right
            {
                if (tempSouthbound.empty())
                { // pushes to temp vector the correct size of an car, first checks if temp is empty
                    VehicleBase *v = new VehicleBase(VehicleType::car, Direction::south, turnDirection::right);
                    tempSouthbound.push_back(v);
                    tempSouthbound.push_back(v);
                }
            }
            else if (carType == 1 && turnDirect == 1) // spawns car and goes straight
            {
                if (tempSouthbound.empty())
                { // pushes to temp vector the correct size of an car, first checks if temp is empty
                    VehicleBase *v = new VehicleBase(VehicleType::car, Direction::south, turnDirection::straight);
                    tempSouthbound.push_back(v);
                    tempSouthbound.push_back(v);
                }
            }
            else if (carType == 2 && turnDirect == 0) // truck and turns right
            {
                if (tempSouthbound.empty())
                {
                    VehicleBase *v = new VehicleBase(VehicleType::truck, Direction::south, turnDirection::right);
                    tempSouthbound.push_back(v);
                    tempSouthbound.push_back(v);
                    tempSouthbound.push_back(v);
                    tempSouthbound.push_back(v);
                }
            }
            else // truck and goes straight
            {
                if (tempSouthbound.empty())
                {
                    VehicleBase *v = new VehicleBase(VehicleType::truck, Direction::south, turnDirection::straight);
                    tempSouthbound.push_back(v);
                    tempSouthbound.push_back(v);
                    tempSouthbound.push_back(v);
                    tempSouthbound.push_back(v);
                }
            }
            VehicleBase::vehicleCount++;
        }
        if (random.getRandom() < prob_new_vehicle_westbound)
        {
            int carType = assignVehicle(proportion_of_SUVs, proportion_of_cars, random.getRandom()); // chooses car type
            int turnDirect = getTurnDirection(carType, proportion_right_turn_SUVs,
                                              proportion_right_turn_trucks, proportion_right_turn_cars, random.getRandom());

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
                if (tempWestbound.empty())
                { // pushes to temp vector the correct size of a car, first checks if temp is empty
                    VehicleBase *v = new VehicleBase(VehicleType::car, Direction::west, turnDirection::right);
                    tempWestbound.push_back(v);
                    tempWestbound.push_back(v);
                }
            }
            else if (carType == 1 && turnDirect == 1) // spawns car and goes straight
            {
                if (tempWestbound.empty())
                { // pushes to temp vector the correct size of a car, first checks if temp is empty
                    VehicleBase *v = new VehicleBase(VehicleType::car, Direction::west, turnDirection::straight);
                    tempWestbound.push_back(v);
                    tempWestbound.push_back(v);
                }
            }
            else if (carType == 2 && turnDirect == 0) // spawns car and goes straight
            {
                if (tempWestbound.empty())
                { // pushes to temp vector the correct size of a car, first checks if temp is empty
                    VehicleBase *v = new VehicleBase(VehicleType::truck, Direction::west, turnDirection::right);
                    tempWestbound.push_back(v);
                    tempWestbound.push_back(v);
                    tempWestbound.push_back(v);
                    tempWestbound.push_back(v);
                }
            }
            else
            {
                if (tempWestbound.empty())
                { // pushes to temp vector the correct size of a truck, first checks if temp is empty
                    VehicleBase *v = new VehicleBase(VehicleType::truck, Direction::west, turnDirection::straight);
                    tempWestbound.push_back(v);
                    tempWestbound.push_back(v);
                    tempWestbound.push_back(v);
                    tempWestbound.push_back(v);
                }
            }
            VehicleBase::vehicleCount++;
        }
        */
        // end of adding cars

        std::cin.get(dummy);
        numClicks++;
        light_ticksNS++; // checks conditions for NS, EW red, yellow, green
        light_ticksEW++;
        if (redNS && light_ticksNS >= NSredTicks)
        {
            redNS = false;
            greenNS = true;
            light_ticksNS = 0;
        }
        else if (greenNS && light_ticksNS >= green_north_south)
        {
            greenNS = false;
            yellowNS = true;
            //light_ticksNS = 0;
        }
        else if (yellowNS && light_ticksNS >= yellow_north_south)
        {
            yellowNS = false;
            redNS = true;
            light_ticksNS = 0;
        }

        if (redEW && light_ticksEW >= EWredTicks)

        {
            redEW = false;
            greenEW = true;
            light_ticksEW = 0;
        }

        else if (greenEW && light_ticksEW >= green_east_west)
        {
            greenEW = false;
            yellowEW = true;
            //light_ticksEW = 0;
        }

        else if (yellowEW && light_ticksEW >= yellow_east_west)
        {
            yellowEW = false;
            redEW = true;
            light_ticksEW = 0;
        }

        if (!tempEastbound.empty())
        {                                        // checks that temp is not empty
            eastbound[0] = tempEastbound.back(); // sets to actual value
            tempEastbound.pop_back();            // removes temp
        }
        if (!tempNorthbound.empty())
        {                                          // checks that temp is not empty
            northbound[0] = tempNorthbound.back(); // sets to actual value
            tempNorthbound.pop_back();             // removes temp
        }
        if (!tempSouthbound.empty())
        {                                          // checks that temp is not empty
            southbound[0] = tempSouthbound.back(); // sets to actual value
            tempSouthbound.pop_back();             // removes temp
        }
        if (!tempWestbound.empty())
        {                                        // checks that temp is not empty
            westbound[0] = tempWestbound.back(); // sets to actual value
            tempWestbound.pop_back();            // removes temp
        }

        if ((eastbound[halfsize + 1] != nullptr) && (eastbound[halfsize + 1])->getVehicleTurnDirection() == turnDirection::right)
        {
            southbound[halfsize + 2] = std::move(eastbound[halfsize + 1]);
            eastbound[halfsize + 1] = nullptr;
        }
        if ((westbound[halfsize + 1] != nullptr) && (westbound[halfsize + 1])->getVehicleTurnDirection() == turnDirection::right)
        {
            northbound[halfsize + 2] = std::move(westbound[halfsize + 1]);
            westbound[halfsize + 1] = nullptr;
        }
        if ((northbound[halfsize + 1] != nullptr) && (northbound[halfsize + 1])->getVehicleTurnDirection() == turnDirection::right)
        {
            eastbound[halfsize + 2] = std::move(northbound[halfsize + 1]);
            northbound[halfsize + 1] = nullptr;
        }
        if ((southbound[halfsize + 1] != nullptr) && (southbound[halfsize + 1])->getVehicleTurnDirection() == turnDirection::right)
        {
            westbound[halfsize + 2] = std::move(southbound[halfsize + 1]);
            southbound[halfsize + 1] = nullptr;
        }

        anim.setVehiclesNorthbound(northbound); // reconstructs intersection with appropriate numClicks
        anim.setVehiclesWestbound(westbound);
        anim.setVehiclesSouthbound(southbound);
        anim.setVehiclesEastbound(eastbound);

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
