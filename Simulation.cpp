#include <iostream>
#include "Animator.h"
#include "VehicleBase.h"
#include "RandomClass.h"
#include <vector>
#include <map>
#include <sstream>
#include <fstream>
#include "readinput.h"
#include <string>


// decides what direction the car will be going (0 for right or 1 for straight)
int getTurnDirection(int carType, double proportion_right_turn_SUVs, double proportion_right_turn_trucks, double proportion_right_turn_cars, double randNum){

if (carType == 0){
	if (randNum < proportion_right_turn_SUVs){
		return 0;
	}
	else{
		return 1;
	}
}
if (carType == 1){
        if (randNum < proportion_right_turn_cars){
                return 0;
        }
        else{
                return 1;
        }
}
if (carType == 2){
        if (randNum < proportion_right_turn_trucks){
                return 0;
        }
        else{
                return 1;
        }
}
}

// decides if a vehicle is an suv, car, or truck
int assignVehicle(double proportion_of_SUVs, double proportion_of_cars, double randNum)
{
    cout << proportion_of_SUVs << endl;
    cout << proportion_of_cars << endl;
    cout << randNum << endl;

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

void moveCars(std::vector<VehicleBase *> &vehicles, int size)
{
    if (size > 1)
    {

        for (int i = size - 1; i > 0; i--)
        {
            vehicles[i] = vehicles[i - 1];
        }
    }
    vehicles[0] = nullptr;
}

int main(int argc, char *argv[])
{
    ReadInput readinput;
    // RandomClass random;
    std::map<std::string, double> inputDict = readinput.getDict(argv[1]);
    // find the values of each variable, read from input
    size_t halfsize = inputDict["number_of_sections_before_intersection:"];
    double maximum_simulated_time = inputDict["maximum_simulated_time:"];

    double green_east_west = inputDict["green_east_west:"];
    double green_north_south = inputDict["green_north_south:"];

    double prob_new_vehicle_eastbound = inputDict["prob_new_vehicle_eastbound:"];
    double prob_new_vehicle_northbound = inputDict["prob_new_vehicle_northbound:"];
    double prob_new_vehicle_southbound = inputDict["prob_new_vehicle_southbound:"];
    double prob_new_vehicle_westbound = inputDict["prob_new_vehicle_westbound:"];

    double proportion_of_SUVs = inputDict["proportion_of_SUVs:"];
    double proportion_of_cars = inputDict["proportion_of_cars:"];

    double proportion_right_turn_SUVs = inputDict["proportion_right_turn_SUVs:"];
    double proportion_right_turn_cars = inputDict["proportion_right_turn_cars:"];
    double proportion_right_turn_trucks = inputDict["proportion_right_turn_trucks:"];

    double yellow_east_west = inputDict["yellow_east_west:"];
    double yellow_north_south = inputDict["yellow_north_south:"];

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

    int i = 0;
    int numClicks = 0;
    anim.setVehiclesNorthbound(northbound);
    anim.setVehiclesWestbound(westbound);
    anim.setVehiclesSouthbound(southbound);
    anim.setVehiclesEastbound(eastbound); // initial construction of intersection
    anim.setLightNorthSouth(LightColor::red);
    anim.setLightEastWest(LightColor::green);
    anim.draw(numClicks);
    RandomClass random(std::stoi(argv[2]));
    int NSredTicks = green_east_west + yellow_east_west;
    int EWredTicks = green_north_south + yellow_north_south;
    bool greenEW = true; // bool values for if its green, yellow, red
    bool greenNS;
    bool yellowNS;
    bool yellowEW;
    bool redEW;
    bool redNS = true;

    size_t light_ticksEW = 0;
    size_t light_ticksNS = 0; // tracks light switches
    while (numClicks < maximum_simulated_time)
    {
        double randNum = random.getRandom();
        moveCars(eastbound, halfsize);
        moveCars(westbound, halfsize);
        moveCars(northbound, halfsize);
        moveCars(southbound, halfsize);
        for (; i < halfsize - 1; i++)
        {
            eastbound[i + 1] = eastbound[i];
            northbound[i + 1] = northbound[i];
            southbound[i + 1] = southbound[i];
            westbound[i + 1] = westbound[i];
        }
        if (random.getRandom() < prob_new_vehicle_eastbound) // checks prob of eastbound spawn
        {
            int carType = assignVehicle(proportion_of_SUVs, proportion_of_cars,
            random.getRandom()); // chooses car type
         
	    turnDirect = getTurnDirection(int carType, proportion_right_turn_SUVs, proportion_right_turn_trucks, proportion_right_turn_cars, random.getRandom());

	    if (carType == 0 && turnDirect == 0) //spawns SUV and turns right 
            { //suv
                if (tempEastbound.empty())
                { //pushes to temp vector the correct size of an suv, first checks if temp is empty
                    VehicleBase *v = new VehicleBase(VehicleType::suv, Direction::east, turnDirection::right);
                    tempEastbound.push_back(v);
                    tempEastbound.push_back(v);
                    tempEastbound.push_back(v);
                }
            }
	    
            if (carType == 0 && turnDirect == 0) //spawns SUV and goes straight
            { //suv
                if (tempEastbound.empty())
                { //pushes to temp vector the correct size of an suv, first checks if temp is empty
                    VehicleBase *v = new VehicleBase(VehicleType::suv, Direction::east, turnDirection::straight);
                    tempEastbound.push_back(v);
                    tempEastbound.push_back(v);
                    tempEastbound.push_back(v);
                }
            }	
if (carType == 0 && turnDirect == 1) //spawns SUV and goes straight
            { //suv
                if (tempEastbound.empty())
                { //pushes to temp vector the correct size of an suv, first checks if temp is empty
                    VehicleBase *v = new VehicleBase(VehicleType::suv, Direction::east, turnDirection::straight);
                    tempEastbound.push_back(v);
                    tempEastbound.push_back(v);
                    tempEastbound.push_back(v);
                }
            }


            else if (carType == 1 && turnDirect == 0)
            {
                if (tempEastbound.empty())
                {
                    VehicleBase *v = new VehicleBase(VehicleType::car, Direction::east);
                    tempEastbound.push_back(v);
                    tempEastbound.push_back(v);
                }
            }
            else
            {
                if (tempEastbound.empty())
                { 
                    VehicleBase *v = new VehicleBase(VehicleType::truck, Direction::east);
                    tempEastbound.push_back(v);
                    tempEastbound.push_back(v);
                    tempEastbound.push_back(v);
                    tempEastbound.push_back(v);
                }
            }
            VehicleBase::vehicleCount++;
        }
        
        if (random.getRandom() < prob_new_vehicle_northbound)
        { // checks prob of northbound spawn
            int carType = assignVehicle(proportion_of_SUVs, proportion_of_cars,
                                        random.getRandom()); // chooses car type
            if (carType == 0)
            { //suv
                if (tempNorthbound.empty())
                { //pushes to temp vector the correct size of an suv, first checks if temp is empty
                    VehicleBase *v = new VehicleBase(VehicleType::suv, Direction::north);
                    tempNorthbound.push_back(v);
                    tempNorthbound.push_back(v);
                    tempNorthbound.push_back(v);
                }
            }
            else if (carType == 1)
            {
                if (tempNorthbound.empty())
                {
                    VehicleBase *v = new VehicleBase(VehicleType::car, Direction::north);
                    tempNorthbound.push_back(v);
                    tempNorthbound.push_back(v);
                }
            }
            else
            {
                if (tempNorthbound.empty())
                { 
                    VehicleBase *v = new VehicleBase(VehicleType::truck, Direction::north);
                    tempNorthbound.push_back(v);
                    tempNorthbound.push_back(v);
                    tempNorthbound.push_back(v);
                    tempNorthbound.push_back(v);
                }
	    }
            VehicleBase::vehicleCount++;
        }
        if (random.getRandom() < prob_new_vehicle_southbound)
        { // checks prob of southbound spawn
            int carType = assignVehicle(proportion_of_SUVs, proportion_of_cars,
                                        random.getRandom()); // chooses car type
            if (carType == 0)
            { //suv
                if (tempSouthbound.empty())
                { //pushes to temp vector the correct size of an suv, first checks if temp is empty
                    VehicleBase *v = new VehicleBase(VehicleType::suv, Direction::south);
                    tempSouthbound.push_back(v);
                    tempSouthbound.push_back(v);
                    tempSouthbound.push_back(v);
                }
            }
            else if (carType == 1)
            {
                if (tempSouthbound.empty())
                {
                    VehicleBase *v = new VehicleBase(VehicleType::car, Direction::south);
                    tempSouthbound.push_back(v);
                    tempSouthbound.push_back(v);
                }
            }
            else
            {
                if (tempSouthbound.empty())
                { 
                    VehicleBase *v = new VehicleBase(VehicleType::truck, Direction::south);
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
            int carType = assignVehicle(proportion_of_SUVs, proportion_of_cars,
                                        random.getRandom()); // chooses car type
            if (carType == 0)
            { //suv
                if (tempWestbound.empty())
                { //pushes to temp vector the correct size of an suv, first checks if temp is empty
                    VehicleBase *v = new VehicleBase(VehicleType::suv, Direction::west);
                    tempWestbound.push_back(v);
                    tempWestbound.push_back(v);
                    tempWestbound.push_back(v);
                }
            }
            else if (carType == 1)
            {
                if (tempWestbound.empty())
                {
                    VehicleBase *v = new VehicleBase(VehicleType::car, Direction::west);
                    tempWestbound.push_back(v);
                    tempWestbound.push_back(v);
                }
            }
            else
            {
                if (tempWestbound.empty())
                { 
                    VehicleBase *v = new VehicleBase(VehicleType::truck, Direction::west);
                    tempWestbound.push_back(v);
                    tempWestbound.push_back(v);
                    tempWestbound.push_back(v);
                    tempWestbound.push_back(v);
                }
	    }
            VehicleBase::vehicleCount++;
        } //end of adding cars
        
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
            light_ticksNS = 0;
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
            light_ticksEW = 0;
        }

        else if (yellowEW && light_ticksEW >= yellow_east_west)
        {
            yellowEW = false;
            redEW = true;
            light_ticksEW = 0;
        }

        if(!tempEastbound.empty()){ //checks that temp is not empty
           eastbound[0] = tempEastbound.back(); //sets to actual value
           tempEastbound.pop_back(); //removes temp
        }
	if(!tempNorthbound.empty()){ //checks that temp is not empty
           northbound[0] = tempNorthbound.back(); //sets to actual value
           tempNorthbound.pop_back(); //removes temp
        }
	if(!tempSouthbound.empty()){ //checks that temp is not empty
           southbound[0] = tempSouthbound.back(); //sets to actual value
           tempSouthbound.pop_back(); //removes temp
        }
	if(!tempWestbound.empty()){ //checks that temp is not empty
           westbound[0] = tempWestbound.back(); //sets to actual value
           tempWestbound.pop_back(); //removes temp
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

