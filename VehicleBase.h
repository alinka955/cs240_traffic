#ifndef __VEHICLE_BASE_H__
#define __VEHICLE_BASE_H__
using namespace std;
// enum: see http://isocpp.github.io/CppCoreGuidelines/CppCoreGuidelines#S-enum
enum class Direction   {north, south, east, west};
enum class turnDirection {right, straight},
enum class VehicleType {car, suv, truck};
enum class LightColor  {green, yellow, red};

class VehicleBase
{
   public:
      static int vehicleCount;

   private:
      int         vehicleID;
      VehicleType vehicleType;
      Direction   vehicleDirection;
      turnDirection   vehicleTurnDirection;

   public:
      VehicleBase(VehicleType type, Direction originalDirection, turnDirection vehicleTurnDirection);
      VehicleBase(const VehicleBase& other);
      ~VehicleBase();
      VehicleBase(VehicleBase&& other)noexcept;
      VehicleBase& operator=(const VehicleBase& other);
      VehicleBase& operator=(VehicleBase&& other)noexcept;

      inline int getVehicleID() const { return this->vehicleID; }

      inline VehicleType getVehicleType() const { return this->vehicleType; }
      inline Direction   getVehicleOriginalDirection() const { return this->vehicleDirection; }
      inline turnDirection   getVehicleTurnDirection() const { return this->vehicleTurnDirection; }

};

#endif
