#include <iostream>
#include "Animator.h"
#include "VehicleBase.h"
#include "RandomClass.h"
#include <vector>
#include <map>
#include <sstream>
#include <fstream>
#include "readinput.h"
#include "intersection.h"
#include <string>

// decides if a vehicle is an suv, car, or truck
int assignVehicle(double proportion_of_SUVs, double proportion_of_cars, double randNum)
{

    if (randNum < proportion_of_SUVs)
    { // suv is 0
        return 0;
    }
    else if (proportion_of_SUVs < randNum < (proportion_of_SUVs + proportion_of_cars))
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
    int numClicks = 0;
    
    anim.setVehiclesNorthbound(northbound);
    anim.setVehiclesWestbound(westbound);
    anim.setVehiclesSouthbound(southbound);
    anim.setVehiclesEastbound(eastbound); //initial construction of intersection
    anim.setLightNorthSouth(LightColor::red);
    anim.setLightEastWest(LightColor::green);
    anim.draw(numClicks);
    RandomClass random(1000);
    int NSredTicks = green_east_west + yellow_east_west;
    int EWredTicks = green_north_south + yellow_north_south;
    bool greenEW = true; //bool values for if its green, yellow, red
    bool greenNS = false;
    bool yellowNS = false;
    bool yellowEW = false;
    bool redEW = false;
    bool redNS = true;
    size_t light_ticks = 0; //tracks light switches
    while (numClicks < maximum_simulated_time)
    {
        double randNum = random.getRandom();
        if (random.getRandom() < prob_new_vehicle_eastbound) // checks prob of eastbound spawn
        {
            int carType = assignVehicle(proportion_of_SUVs, proportion_of_cars, 
            random.getRandom()); // chooses car type
            if (carType == 0)
            { 
                VehicleBase *v = new VehicleBase(VehicleType::suv, Direction::east);
                eastbound.push_back(v); // pushes suv 3 times
                eastbound.push_back(v);
                eastbound.push_back(v);
            }
            else if (carType == 1)
            { 
                VehicleBase *v = new VehicleBase(VehicleType::car, Direction::east);
                eastbound.push_back(v); // pushes car 2 times
                eastbound.push_back(v);
            }
            else
            {
                VehicleBase *v = new VehicleBase(VehicleType::truck, Direction::east);
                eastbound.push_back(v); // pushes truck 4 times
                eastbound.push_back(v);
                eastbound.push_back(v);
                eastbound.push_back(v);
            }
            VehicleBase::vehicleCount++;
        }
        if (random.getRandom() < prob_new_vehicle_northbound)
        { //checks prob of northbound spawn
            int carType = assignVehicle(proportion_of_SUVs, proportion_of_cars,
           random.getRandom()); // chooses car type
            if (carType == 0)  // suv north
            { 
                VehicleBase *v = new VehicleBase(VehicleType::suv, Direction::north);
                northbound.push_back(v); //pushes suv 3 times
                northbound.push_back(v);
                northbound.push_back(v);
            }
            else if (carType == 1) //car
            { 
                VehicleBase *v = new VehicleBase(VehicleType::car, Direction::north);
                northbound.push_back(v); //pushes car 2 times
                northbound.push_back(v);
            }
            else
            { //truck
                VehicleBase *v = new VehicleBase(VehicleType::truck, Direction::north);
                northbound.push_back(v); //pushes truck 4 times
                northbound.push_back(v);
                northbound.push_back(v);
                northbound.push_back(v);
            }
            VehicleBase::vehicleCount++;
        }
        if (random.getRandom() < prob_new_vehicle_southbound)
        {//checks prob of southbound spawn
            int carType = assignVehicle(proportion_of_SUVs, proportion_of_cars,
            random.getRandom()); // chooses car type
            if (carType == 0)
            { //suv
                VehicleBase *v = new VehicleBase(VehicleType::suv, Direction::south);
		southbound.push_back(v); // pushes suv 3 times
                southbound.push_back(v);
                southbound.push_back(v);
            	
	    }
            else if (carType == 1)
            { //car
                VehicleBase *v = new VehicleBase(VehicleType::car, Direction::south);
                southbound.push_back(v); //pushes car 2 times
                southbound.push_back(v);
            }
            else
            { //truck
                VehicleBase *v = new VehicleBase(VehicleType::truck, Direction::south);
                southbound.push_back(v); //pushes truck 4 times
                southbound.push_back(v);
                southbound.push_back(v);
                southbound.push_back(v);
            }
            VehicleBase::vehicleCount++;
        }
        if (random.getRandom() < prob_new_vehicle_westbound)
        {
            int carType = assignVehicle(proportion_of_SUVs, proportion_of_cars,
            random.getRandom()); // chooses car type
            if (carType == 0) //suv
            { 
                VehicleBase *v = new VehicleBase(VehicleType::suv, Direction::west);
                westbound.push_back(v); // pushes suv 3 times
                westbound.push_back(v); 
                westbound.push_back(v);
            }
            else if (carType == 1)
            { // car // needs an assigned direction
                VehicleBase *v = new VehicleBase(VehicleType::car, Direction::west);
                westbound.push_back(v); // pushes car 2 times
                westbound.push_back(v);
            }
            else
            { //truck
                VehicleBase *v = new VehicleBase(VehicleType::truck, Direction::west);
                westbound.push_back(v); // pushes truck 4 times
                westbound.push_back(v);
                westbound.push_back(v);
                westbound.push_back(v);
            }
            VehicleBase::vehicleCount++;
        }
        std::cin.get(dummy);

        numClicks++;
        light_ticks++; //checks conditions for NS, EW red, yellow, green
        if (redNS && light_ticks >= NSredTicks){
            redNS = false;
            yellowNS = true;
            light_ticks = 0;
        }
        if (yellowNS && light_ticks >= yellow_north_south)
        {
            yellowNS = false;
            greenNS = true;
            light_ticks = 0;
        }
        if (greenNS && light_ticks >= green_north_south)
        {
            greenNS = false;
            yellowNS = true;
            light_ticks = 0;
        }
        if (yellowNS && light_ticks >= yellow_north_south)
        {
            yellowNS = false;
            redNS = true;
            light_ticks = 0;
        }
        if (redEW && light_ticks >= EWredTicks)
        {
            redEW = false;
            yellowEW = true;
            light_ticks = 0;
        }
        if (yellowEW && light_ticks >= yellow_east_west)
        {
            yellowEW = false;
            greenEW = true;
            light_ticks = 0;
        }
        if (greenEW && light_ticks >= green_east_west)
        {
            greenEW = false;
            yellowEW = true;
            light_ticks = 0;
        }
        if (yellowEW && light_ticks >= yellow_east_west)
        {
            yellowEW = false;
            redEW = true;
            light_ticks = 0;
        }

        anim.setVehiclesNorthbound(northbound); //reconstructs intersection with appropriate numClicks
        anim.setVehiclesWestbound(westbound);
        anim.setVehiclesSouthbound(southbound);
        anim.setVehiclesEastbound(eastbound);
        
        if(greenEW && redNS){
            cout << "greenEW" << endl;
            anim.setLightNorthSouth(LightColor::red);
            anim.setLightEastWest(LightColor::green);
        }
        else if(yellowEW && redNS){
            cout << "yellowEW" << endl;
            anim.setLightNorthSouth(LightColor::red);
            anim.setLightEastWest(LightColor::yellow);
        }
        else if(greenNS && redEW){
            cout << "greeNS" << endl;
            anim.setLightNorthSouth(LightColor::green);
            anim.setLightEastWest(LightColor::red);
        }
        else if (yellowNS && redEW){
            cout << "yelowNS" << endl;
            anim.setLightNorthSouth(LightColor::yellow);
            anim.setLightEastWest(LightColor::red);
        }
       
        
        anim.draw(numClicks);
    }
}
