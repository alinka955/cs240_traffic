

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

void moveCars(std::vector<VehicleBase*>& vehicles, int size){
	if(size > 1){
	   
	   for(int i = size - 1; i > 0; i--){
		vehicles[i] = vehicles[i - 1];
		
	  }
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
    bool greenNS;
    bool yellowNS;
    bool yellowEW;
    bool redEW;
    bool redNS = true;


    size_t light_ticksEW = 0;
    size_t light_ticksNS = 0; //tracks light switches
    while (numClicks < maximum_simulated_time)
    {
        double randNum = random.getRandom();
        moveCars(eastbound,halfsize);
	if(eastbound[0] -> getVehicleType() == VehicleType::car){
                carSizeEast++;
           }
           else if(eastbound[0] -> getVehicleType() == VehicleType::suv){
                suvSizeEast++;
           }
           else if(eastbound[0] -> getVehicleType() == VehicleType::truck){
                truckSizeEast++;
           }

           if(eastbound[1] -> getVehicleType() == VehicleType::car && (carSizeEast == 2) &&
									 (eastbound[1] != nullptr) ){        
                eastbound[0] = nullptr;
                carSizeEast = 0;
           }
           else if(eastbound[1] -> getVehicleType() == VehicleType::suv && (suvSizeEast == 3) &&
									 (eastbound[1] != nullptr)){    
                eastbound[0] = nullptr;
                suvSizeEast = 0;
           }
           else if(eastbound[1] -> getVehicleType() == VehicleType::truck && (truckSizeEast == 4) &&
									 (eastbound[1] != nullptr)){
                eastbound[0] = nullptr;
                truckSizeEast = 0;
           }
	moveCars(northbound,halfsize);
	if(northbound[0] -> getVehicleType() == VehicleType::car){
                carSizeNorth++;
           }
           else if(northbound[0] -> getVehicleType() == VehicleType::suv){
                suvSizeNorth++;
           }
           else if(northbound[0] -> getVehicleType() == VehicleType::truck){
                truckSizeNorth++;
           }

           if(northbound[1] -> getVehicleType() == VehicleType::car && (carSizeNorth == 2) &&
                                                                         (northbound[1] != nullptr) ){
                northbound[0] = nullptr;
                carSizeNorth = 0;
           }
           else if(northbound[1] -> getVehicleType() == VehicleType::suv && (suvSizeNorth == 3) &&
                                                                         (northbound[1] != nullptr)){
                northbound[0] = nullptr;
                suvSizeNorth = 0;
           }
           else if(northbound[1] -> getVehicleType() == VehicleType::truck && (truckSizeNorth == 4) &&
                                                                         (northbound[1] != nullptr)){
                northbound[0] = nullptr;
                truckSizeNorth = 0;
	   }
	moveCars(southbound,halfsize);
	if(southbound[0] -> getVehicleType() == VehicleType::car){
                carSizeSouth++;
           }
           else if(southbound[0] -> getVehicleType() == VehicleType::suv){
                suvSizeSouth++;
           }
           else if(southbound[0] -> getVehicleType() == VehicleType::truck){
                truckSizeSouth++;
           }

           if(southbound[1] -> getVehicleType() == VehicleType::car && (carSizeSouth == 2) &&
                                                                         (southbound[1] != nullptr) ){
                southbound[0] = nullptr;
                carSizeSouth = 0;
           }
           else if(southbound[1] -> getVehicleType() == VehicleType::suv && (suvSizeSouth == 3) &&
                                                                         (southbound[1] != nullptr)){
                southbound[0] = nullptr;
                suvSizeSouth = 0;
           }
           else if(southbound[1] -> getVehicleType() == VehicleType::truck && (truckSizeSouth == 4) &&
                                                                         (southbound[1] != nullptr)){
                southbound[0] = nullptr;
                truckSizeSouth = 0;
	   }
	moveCars(westbound,halfsize);
	if(westbound[0] -> getVehicleType() == VehicleType::car){
                carSizeWest++;
           }
           else if(westbound[0] -> getVehicleType() == VehicleType::suv){
                suvSizeWest++;
           }
           else if(westbound[0] -> getVehicleType() == VehicleType::truck){
                truckSizeWest++;
           }

           if(westbound[1] -> getVehicleType() == VehicleType::car && (carSizeWest == 2) &&
                                                                         (westbound[1] != nullptr) ){
                westbound[0] = nullptr;
                carSizeWest = 0;
           }
           else if(westbound[1] -> getVehicleType() == VehicleType::suv && (suvSizeWest == 3) &&
                                                                         (westbound[1] != nullptr)){
                westbound[0] = nullptr;
                suvSizeWest = 0;
           }
           else if(westbound[1] -> getVehicleType() == VehicleType::truck && (truckSizeWest == 4) &&
                                                                         (westbound[1] != nullptr)){
                westbound[0] = nullptr;
                truckSizeWest = 0;
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
        light_ticksNS++; //checks conditions for NS, EW red, yellow, green
	light_ticksEW++;
        if (redNS && light_ticksNS >= NSredTicks){
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

        anim.setVehiclesNorthbound(northbound); //reconstructs intersection with appropriate numClicks
        anim.setVehiclesWestbound(westbound);
        anim.setVehiclesSouthbound(southbound);
        anim.setVehiclesEastbound(eastbound);


	//switching traffic lights       
        if(greenEW && redNS){
            anim.setLightNorthSouth(LightColor::red);
            anim.setLightEastWest(LightColor::green);
        }
        else if(yellowEW && redNS){
            anim.setLightNorthSouth(LightColor::red);
            anim.setLightEastWest(LightColor::yellow);
        }
        else if(greenNS && redEW){
            anim.setLightNorthSouth(LightColor::green);
            anim.setLightEastWest(LightColor::red);
        }
        else if (yellowNS && redEW){
            anim.setLightNorthSouth(LightColor::yellow);
            anim.setLightEastWest(LightColor::red);
        }

	else if (greenNS && yellowEW){
            anim.setLightNorthSouth(LightColor::green);
            anim.setLightEastWest(LightColor::yellow);
	}
	else if (yellowNS && greenEW){
            anim.setLightNorthSouth(LightColor::yellow);
            anim.setLightEastWest(LightColor::green);
	}
	

        
        anim.draw(numClicks);
    }
}

