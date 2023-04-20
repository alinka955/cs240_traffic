#ifndef __VEHICLE_BASE_CPP__
#define __VEHICLE_BASE_CPP__
#include <iostream> 
#include "VehicleBase.h"
using namespace std;
int VehicleBase::vehicleCount = 0;

/**
* This program is a modified VehicleBase class that has been updated to include 
* copy and move constructors, copy and move assignments, deconstructors, and turn directions 
* for the vehicle. 
*/
//intializes
VehicleBase::VehicleBase(VehicleType type, Direction direction, turnDirection turndirection)
    : vehicleID(VehicleBase::vehicleCount++), 
      vehicleType(type),
      vehicleDirection(direction),
      vehicleTurnDirection(turndirection)
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


#endif
