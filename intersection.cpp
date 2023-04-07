#include <iostream>
#include "Animator.h"
#include "VehicleBase.h"
#include "Random.cpp"
#include <vector>
#include <map>
#include <sstream>
#include <fstream>
void error(string err, string arg) {
        cerr << err << arg << endl;
        exit(0);
} 

// dictionary input
map<string, double> inputToDict(string input){

        //Open the input file
        ifstream infile{input};

        //Check if infile cannot be open
        if (!infile.is_open()){
                error("Unable to open the following file: ", input);
        }
        string parameter;
        double value;
   
        //Create a dictionary to store values
        map<string, double> dict;
        while (infile >> parameter >> value){
                dict.insert({parameter, value});
        }
        infile.close();
        return dict;
}

// find the values of each variable, read from input
double halfsize = inputDict["number_of_sections_before_intersection"];
double maximum_simulated_time = inputDict["maximum_simulated_time"]

double green_east_west = inputDict["green_east_west"]
double green_north_south = inputDict["green_north_south"]

double prob_new_vehicle_eastbound = inputDict["prob_new_vehicle_eastbound"]
double prob_new_vehicle_northbound = inputDict["prob_new_vehicle_northbound"]
double prob_new_vehicle_southbound = inputDict["prob_new_vehicle_southbound"]
double prob_new_vehicle_westbound = inputDict["prob_new_vehicle_westbound"]

double proportion_of_SUVs = inputDict["proportion_of_SUVs"]
double proportion_of_cars = inputDict["proportion_of_cars"]

double proportion_right_turn_SUVs = inputDict["proportion_right_turn_SUVs"]
double proportion_right_turn_cars = inputDict["proportion_right_turn_cars"]
double proportion_right_turn_trucks = inputDict["proportion_right_turn_trucks"]

double yellow_east_west = inputDict["yellow_east_west"]
double yellow_north_south = inputDict["yellow_north_south"]

double proportion_left_turn_SUVs = inputDict["proportion_left_turn_SUVs"]
double proportion_left_turn_cars = inputDict["proportion_left_turn_cars"]
double proportion_left_turn_trucks = inputDict["proportion_left_turn_trucks"]


Animator anim(halfSize);

// construct vectors of VehicleBase* of appropriate size, init to nullptr
std::vector<VehicleBase*> westbound(halfSize * 2 + 2, nullptr);
std::vector<VehicleBase*> eastbound(halfSize * 2 + 2, nullptr);
std::vector<VehicleBase*> southbound(halfSize * 2 + 2, nullptr);
std::vector<VehicleBase*> northbound(halfSize * 2 + 2, nullptr);


 void checkCarSpawn(){
                if(random() < prob_new_vehicle_eastbound){
                        int carType = assignVehicle();
                        if(carType == 0){ //suv // needs an assigned direction
                                VehicleBase v = new VehicleBase(suv, None);
                                eastbound.push_back(v&);
                        }
                        else if(carType == 1){ //car // needs an assigned direction
                                VehicleBase v = new VehicleBase(car, None);
                                eastbound.push_back(v&);
                        }
                        else{
                                VehicleBase v = new VehicleBase(truck, None);
                                eastbound.push_back(v&);
                        }
                }

        }

        int assignVehicle(){
                double randNum = random();
                if (randNum < proportion_of_SUVs){ //suv is 0
                        return 0;
                }
                else if(proportion_of_SUVs < randNum < (proportion_of_SUVs + proportion_of_cars)){ // car is 1
                        return 1;
                }
                else{ // truck is 2
                        return 2;
                }
        }


int main (int argc, char* argv[]){
   // get dictionary with input
   map<string,double> inputDict{inputToDict(argv[1])};
   
}
