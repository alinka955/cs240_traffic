#ifndef __VEHICLE_BASE_CPP__
#define __VEHICLE_BASE_CPP__
#include <iostream> 
#include "VehicleBase.h"
using namespace std;
int VehicleBase::vehicleCount = 0;


//intializes
VehicleBase::VehicleBase(VehicleType type, Direction direction, Direction turnDirection)
    : vehicleID(VehicleBase::vehicleCount++), 
      vehicleType(type),
      vehicleDirection(direction),
      vehicleTurnDirection(turnDirection)
{}

//copy constructor
VehicleBase::VehicleBase(const VehicleBase& other)
    : vehicleID(other.vehicleID),
      vehicleType(other.vehicleType),
      vehicleDirection(other.vehicleDirection),
      vehicleTurnDirection(other.vehicleTurnDirection)
{}

//destructor
VehicleBase::~VehicleBase() {}

//copy assignment
VehicleBase& VehicleBase::operator=(const VehicleBase& other){
    if (this == &other){
      return *this;
    }
    vehicleID = other.vehicleID;
    vehicleType = other.vehicleType;
    vehicleDirection = other.vehicleDirection;
    vehicleTurnDirection = other.vehicleTurnDirection;
    return *this;
}

//move constructor
VehicleBase::VehicleBase(VehicleBase&& other)noexcept
    : 
    vehicleID(other.vehicleID),
    vehicleType(other.vehicleType),
    vehicleDirection(other.vehicleDirection),
    vehicleTurnDirection(other.vehicleTurnDirection){
        other.vehicleID = 0;
    }

//move assignment
VehicleBase& VehicleBase::operator=(VehicleBase&& other)noexcept{
    if (this == &other) {
        return *this;
    }
    vehicleID = other.vehicleID;
    vehicleType = other.vehicleType;
    vehicleDirection = other.vehicleDirection;
    vehicleTurnDirection = other.vehicleTurnDirection;
    other.vehicleID = 0;
    return *this;
}
/*
int main (){
	VehicleBase v1(VehicleType::car, Direction::east);
	VehicleBase v2(v1);
	
	std::cout << &v1 << std::endl;
	std::cout << &v2 << std::endl;	
}
*/
#endif
