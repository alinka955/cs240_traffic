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

/*
void checkCarSpawn() {
    if (random() < prob_new_vehicle_eastbound)
    {
	int carType = assignVehicle();
	if (carType == 0)
	{ // suv // needs an assigned direction
	    VehicleBase v = new VehicleBase(VehicleType::suv, Direction::east);
	    eastbound.push_back(&v);
	}
	else if (carType == 1)
	{ // car // needs an assigned direction
	    VehicleBase v = new VehicleBase(VehicleType::car, Direction::east);
	    eastbound.push_back(&v);
	}
	else
	{
	    VehicleBase v = new VehicleBase(VehicleType::truck, Direction::east);
	    eastbound.push_back(&v);
	}
    }
}

*/
// decides if a vehicle is an suv, car, or truck
int assignVehicle(double proportion_of_SUVs, double proportion_of_cars)
{
    RandomClass random(123); 
    double randNum = random.getRandom();
    //double randNum = 0.23;   
    cout<< "random number " << randNum<< endl; 

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
        //RandomClass random;
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

        std::cout << "halfsize" << halfsize << std::endl;
        Animator anim(halfsize);

        
        std::vector<VehicleBase *> westbound(halfsize * 2 + 2, nullptr);
        std::vector<VehicleBase *> eastbound(halfsize * 2 + 2, nullptr);
        std::vector<VehicleBase *> southbound(halfsize * 2 + 2, nullptr);
        std::vector<VehicleBase *> northbound(halfsize * 2 + 2, nullptr);

	int car =  assignVehicle(proportion_of_SUVs, proportion_of_cars);
	cout << car << endl;


        char dummy;
        anim.setVehiclesNorthbound(northbound);
        anim.setVehiclesWestbound(westbound);
        anim.setVehiclesSouthbound(southbound);
        anim.setVehiclesEastbound(eastbound);
        anim.draw(8);
        
        /*southbound.assign(halfsize * 2 + 2, nullptr); // reset vector
        northbound.assign(halfsize * 2 + 2, nullptr); // reset
        eastbound.assign(halfsize * 2 + 2, nullptr);  // reset
        westbound.assign(halfsize * 2 + 2, nullptr);  // reset */

        // std::cin.get(dummy);
}
