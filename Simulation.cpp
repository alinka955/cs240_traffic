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
    anim.draw(numClicks);
    RandomClass random(1000);
    while (numClicks < maximum_simulated_time)
    {
        double randNum = random.getRandom();
        for(; i < halfSize-1; i++){
            eastbound[i] = eastbound[i+1];
            northbound[i] = northbound[i+1];
            southbound[i] = southbound[i+1];
            westbound[i] = westbound [i+1];
        }
        if (random.getRandom() < prob_new_vehicle_eastbound) // checks prob of eastbound spawn
        {
            int carType = assignVehicle(proportion_of_SUVs, proportion_of_cars, 
            random.getRandom()); // chooses car type
            if (carType == 0)
            { 
                VehicleBase *v = new VehicleBase(VehicleType::suv, Direction::east);
                if(eastbound[1] == null){  
                    eastbound[0] = v;
                }
                else if (eastbound[1].getVehicleType() == suv){
                    eastbound[0] = eastbound [1];
                } 
                
            }
            else if (carType == 1)
            { 
                VehicleBase *v = new VehicleBase(VehicleType::car, Direction::east);
                if(eastbound[1] == null){  
                    eastbound[0] = v;
                }
                else if (eastbound[1].getVehicleType() == car){
                    eastbound[0] = eastbound [1];
                } 
            }
            else
            {
                VehicleBase *v = new VehicleBase(VehicleType::truck, Direction::east);
                if(eastbound[1] == null){  
                    eastbound[0] = v;
                }
                else if (eastbound[1].getVehicleType() == truck){
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
                VehicleBase *v = new VehicleBase(VehicleType::suv, Direction::north);
                if(northbound[1] == null){  
                    northbound[0] = v;
                }
                else if (northbound[1].getVehicleType() == suv){
                    northbound[0] = northbound [1];
                } 
            }
            else if (carType == 1) //car
            { 
                VehicleBase *v = new VehicleBase(VehicleType::car, Direction::north);
                if(northbound[1] == null){  
                    northbound[0] = v;
                }
                else if (northbound[1].getVehicleType() == car){
                    northbound[0] = northbound [1];
                } 
            }
            else
            { //truck
                VehicleBase *v = new VehicleBase(VehicleType::truck, Direction::north);
                if(northbound[1] == null){  
                    northbound[0] = v;
                }
                else if (northbound[1].getVehicleType() == truck){
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
                VehicleBase *v = new VehicleBase(VehicleType::suv, Direction::south);
                if(southbound[1] == null){  
                    southbound[0] = v;
                }
                else if (southbound[1].getVehicleType() == suv){
                    southbound[0] = southbound [1];
                } 
            }
            else if (carType == 1)
            { //car
                VehicleBase *v = new VehicleBase(VehicleType::car, Direction::south);
                if(southbound[1] == null){  
                    southbound[0] = v;
                }
                else if (southbound[1].getVehicleType() == car){
                    southbound[0] = southbound [1];
                }
            }
            else
            { //truck
                VehicleBase *v = new VehicleBase(VehicleType::truck, Direction::south);
                if(southbound[1] == null){  
                    southbound[0] = v;
                }
                else if (southbound[1].getVehicleType() == truck){
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
                VehicleBase *v = new VehicleBase(VehicleType::suv, Direction::west);
                if(westbound[1] == null){  
                    westbound[0] = v;
                }
                else if (westbound[1].getVehicleType() == suv){
                    westbound[0] = westbound [1];
                }
            }
            else if (carType == 1)
            { // car // needs an assigned direction
                VehicleBase *v = new VehicleBase(VehicleType::car, Direction::west);
                if(westbound[1] == null){  
                    westbound[0] = v;
                }
                else if (westbound[1].getVehicleType() == car){
                    westbound[0] = westbound [1];
                }
            }
            else
            { //truck
                VehicleBase *v = new VehicleBase(VehicleType::truck, Direction::west);
                if(westbound[1] == null){  
                    westbound[0] = v;
                }
                else if (westbound[1].getVehicleType() == truck){
                    westbound[0] = westbound [1];
                }
            }
            VehicleBase::vehicleCount++;
        }
        std::cin.get(dummy);
        numClicks++;
        anim.setVehiclesNorthbound(northbound); //reconstructs intersection with appropriate numClicks
        anim.setVehiclesWestbound(westbound);
        anim.setVehiclesSouthbound(southbound);
        anim.setVehiclesEastbound(eastbound);
        anim.draw(numClicks);
    }
}
