#include <iostream>
#include "Animator.h"
#include "VehicleBase.h"
//#include "Random.cpp"
#include <vector>
#include <map>
#include <sstream>
#include <fstream>
#include"readinput.h"
#include <string>

// Forward declarations

class Intersection {
public:
	Intersection();
	Intersection(const Intersection& other);
	Intersection& operator=(Intersection& other);
	Intersection(Intersection&& other);
	Intersection& operator=(Intersection&& other);
	~Intersection();
	getHalfsize();
	

private:
    void checkCarSpawn();
    double random();
    int assignVehicle();
    std::map<std::string, double> inputDict;
    // Member variables
    std::vector<VehicleBase *> westbound;
    std::vector<VehicleBase *> eastbound;
    std::vector<VehicleBase *> southbound;
    std::vector<VehicleBase *> northbound;
    double halfsize;
    double maximum_simulated_time;
    double green_east_west;
    double green_north_south;
    double prob_new_vehicle_eastbound;
    double prob_new_vehicle_northbound;
    double prob_new_vehicle_southbound;
    double prob_new_vehicle_westbound;
    double proportion_of_SUVs;
    double proportion_of_cars;
    double proportion_right_turn_SUVs;
    double proportion_right_turn_cars;
    double proportion_right_turn_trucks;
    double yellow_east_west;
    double yellow_north_south;
    double proportion_left_turn_SUVs;
    double proportion_left_turn_cars;
    double proportion_left_turn_trucks;
    ReadInput readinput;

};
