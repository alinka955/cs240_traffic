

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


    int i = 0;
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
        for(; i < halfsize-1; i++){
            eastbound[i+1] = eastbound[i];
            northbound[i+1] = northbound[i];
            southbound[i+1] = southbound[i];
            westbound[i+1] = westbound [i];
        }
        if (random.getRandom() < prob_new_vehicle_eastbound) // checks prob of eastbound spawn
        {
            int carType = assignVehicle(proportion_of_SUVs, proportion_of_cars, 
            random.getRandom()); // chooses car type
            if (carType == 0)
            { 
                if(eastbound[1] == nullptr){  
                    VehicleBase *v = new VehicleBase(VehicleType::suv, Direction::east);
                    eastbound[0] = v;
                }
                else if (eastbound[1]->getVehicleType() == VehicleType::suv){
                    eastbound[0] = eastbound [1];
                }
            }
            else if (carType == 1)
            { 
                if(eastbound[1] == nullptr){  
                    VehicleBase *v = new VehicleBase(VehicleType::car, Direction::east);
                    eastbound[0] = v;
                }
                else if (eastbound[1]->getVehicleType() == VehicleType::car){
                    eastbound[0] = eastbound [1];
                }
            }
            else
            {
               
                if(eastbound[1] == nullptr){ 
                    VehicleBase *v = new VehicleBase(VehicleType::truck, Direction::east);
                    eastbound[0] = v;
                }
                else if (eastbound[1]->getVehicleType() == VehicleType::truck){
                    eastbound[0] = eastbound [1];
                } 
            }
            VehicleBase::vehicleCount++;
        }
        if (random.getRandom() < prob_new_vehicle_northbound)
        { //checks prob of northbound spawn
            int carType = assignVehicle(proportion_of_SUVs, proportion_of_cars,
           random.getRandom()); // chooses car type
            if (carType == 0)  // suv north
            { 
                if(northbound[1] == nullptr){  
                    VehicleBase *v = new VehicleBase(VehicleType::suv, Direction::north);
                    northbound[0] = v;
                }
                else if (northbound[1]->getVehicleType() == VehicleType::suv){
                    northbound[0] = northbound [1];
                }
            }
            else if (carType == 1) //car
            { 
                if(northbound[1] == nullptr){  
                    VehicleBase *v = new VehicleBase(VehicleType::car, Direction::north);
                    northbound[0] = v;
                }
                else if (northbound[1]->getVehicleType() == VehicleType::car){
                    northbound[0] = northbound [1];
                }
            }
            else
            { //truck
                if(northbound[1] == nullptr){  
                    VehicleBase *v = new VehicleBase(VehicleType::truck, Direction::north);
                    northbound[0] = v;
                }
                else if (northbound[1]->getVehicleType() == VehicleType::truck){
                    northbound[0] = northbound [1];
                }
            }
            VehicleBase::vehicleCount++;
        }
        if (random.getRandom() < prob_new_vehicle_southbound)
        {//checks prob of southbound spawn
            int carType = assignVehicle(proportion_of_SUVs, proportion_of_cars,
            random.getRandom()); // chooses car type
            if (carType == 0)
            { //suv
                if(southbound[1] == nullptr){
                    VehicleBase *v = new VehicleBase(VehicleType::suv, Direction::south);
                    southbound[0] = v;
                }
                else if (southbound[1]->getVehicleType() == VehicleType::suv){
                    southbound[0] = southbound [1];
                }
            }
            else if (carType == 1)
            { //car
                if(southbound[1] == nullptr){  
                    VehicleBase *v = new VehicleBase(VehicleType::car, Direction::south);                    
                    southbound[0] = v;
                }
                else if (southbound[1]->getVehicleType() == VehicleType::car){
                    southbound[0] = southbound [1];
                }
            }
            else
            { //truck
                if(southbound[1] == nullptr){  
                    VehicleBase *v = new VehicleBase(VehicleType::truck, Direction::south);
                    southbound[0] = v;
                }
                else if (southbound[1]->getVehicleType() == VehicleType::truck){
                    southbound[0] = southbound [1];
                }
            }
            VehicleBase::vehicleCount++;
        }
        if (random.getRandom() < prob_new_vehicle_westbound)
        {
            int carType = assignVehicle(proportion_of_SUVs, proportion_of_cars,
            random.getRandom()); // chooses car type
            if (carType == 0) //suv
            { 
                if(westbound[1] == nullptr){  
                    VehicleBase *v = new VehicleBase(VehicleType::suv, Direction::west);
                    westbound[0] = v;
                }
                else if (westbound[1]->getVehicleType() == VehicleType::suv){
                    westbound[0] = westbound [1];
                }
            }
            else if (carType == 1)
            { // car // needs an assigned direction
                if(westbound[1] == nullptr){  
                    VehicleBase *v = new VehicleBase(VehicleType::car, Direction::west);
                    westbound[0] = v;
                }
                else if (westbound[1]->getVehicleType() == VehicleType::car){
                    westbound[0] = westbound [1];
                }
            }
            else
            { //truck
                if(westbound[1] == nullptr){  
                    VehicleBase *v = new VehicleBase(VehicleType::truck, Direction::west);
                    westbound[0] = v;
                }
                else if (westbound[1]->getVehicleType() == VehicleType::truck){
                    westbound[0] = westbound [1];
                }
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

