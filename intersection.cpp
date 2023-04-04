#include <iostream>
#include "Animator.h"
#include "VehicleBase.h"
#include "readinput.cpp"
#include <vector>

// import dictionary



int halfsize = number_of_sections_before_intersection;

Animator anim(halfSize);

// construct vectors of VehicleBase* of appropriate size, init to nullptr
std::vector<VehicleBase*> westbound(halfSize * 2 + 2, nullptr);
std::vector<VehicleBase*> eastbound(halfSize * 2 + 2, nullptr);
std::vector<VehicleBase*> southbound(halfSize * 2 + 2, nullptr);
std::vector<VehicleBase*> northbound(halfSize * 2 + 2, nullptr);

// random number generator


if (prob_new_vehicle_northbound) {
   if (proportion_of_cars) {
      VehicleBase v(VehicleType::car, Direction::NorthBound); 
   }
   else if (proportion_of_SUVs){
     VehicleBase v(VehicleType::suv, Direction::NorthBound); 
   }
  else{
    VehicleBase v(VehicleType::truck, Direction::NorthBound); 
  }
}



