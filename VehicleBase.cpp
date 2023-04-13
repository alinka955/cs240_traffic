#ifndef __VEHICLE_BASE_CPP__
#define __VEHICLE_BASE_CPP__

#include "VehicleBase.h"

int VehicleBase::vehicleCount = 0;


//intializes
VehicleBase::VehicleBase(VehicleType type, Direction direction)
    : vehicleID(VehicleBase::vehicleCount++), 
      vehicleType(type),
      vehicleDirection(direction)
{}

//copy constructor
VehicleBase::VehicleBase(const VehicleBase& other)
    : vehicleID(other.vehicleID),
      vehicleType(other.vehicleType),
      vehicleDirection(other.vehicleDirection)
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
    return *this;
}

//move constructor
VehicleBase::VehicleBase(VehicleBase&& other)noexcept
    : 
    vehicleID(other.vehicleID),
    vehicleType(other.vehicleType),
    vehicleDirection(other.vehicleDirection){
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
    other.vehicleID = 0;
    return *this;
}


#endif
