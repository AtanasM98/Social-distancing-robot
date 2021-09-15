#include "../Vehicle.h"
#include "../Coordinate.h"

#include <math.h>

Coordinate Vehicle::GetMovement(int inputVelocity, int inputSteering, int L)
{
    double theta;
    double x, y;
    theta = this->location.GetTurnAngle() + (inputVelocity/L) * std::tan(inputSteering);
    x = this->location.GetRow() + inputVelocity*std::cos(theta);
    y = this->location.GetCol() + inputVelocity*std::sin(theta);
    Coordinate movement(x, y, theta);
    if(this->map.checkBounds(movement))
        return movement;
    else
        return Coordinate(-1, -1, -1);
}

void Vehicle::Move(Coordinate c)
{
    this->prevLocation = this->location;
    this->location = c;
}