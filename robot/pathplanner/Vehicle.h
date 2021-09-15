#ifndef H_VEHICLE_H
#define H_VEHICLE_H
#include "Coordinate.h"
#include "Map.h"

class Vehicle
{
    public:
    Vehicle(Coordinate st, Map m)
    {
        location = st;
        prevLocation = location;
        map = m;
    }
    Vehicle () { }

    Coordinate GetMovement(int inputVelocity, int inputSteering, int L);
    void Move(Coordinate target);
    Coordinate GetLoc()
    {
        return location;
    }

    private:
    Coordinate location;
    Coordinate prevLocation;
    Map map;
};
#endif