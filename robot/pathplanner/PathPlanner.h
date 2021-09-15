#ifndef H_PATHPLANNER_H
#define H_PATHPLANNER_H
#include "Coordinate.h"
#include "Map.h"
#include "Path.h"
#include "Vehicle.h"

#include <utility>
#include <tuple>

class PathPlanner
{
    public:
    PathPlanner(Coordinate startPoint, Coordinate endPoint, Map m);
    
    // This is the method that returns the chosen path for the next iteration of the algorithm
    Coordinate getNextPathNode();

    bool checkIfPassed(Coordinate c1)
    {
        for(unsigned int i = 0; i < this->closedPath.getPath().size(); i++)
        {
            if(c1.GetRow() == this->closedPath.getPath()[i].GetRow())
                return false;   
        }
        return true;
    }

    int getCounter() { return stepCounter; }

    // Get map 
    Map getMap() { return map; }

    // Updates map with newfound information
    void updateMap(Map newM);


    private:
    Vehicle robot;
    Coordinate startPoint;
    Coordinate endPoint;
    Map map;
    Path openPath;
    Path closedPath;
    int L = 1;
    int stepCounter = 0;
    std::vector<double> additionalCosts = {0.2, 0.1, 0.2, 0.02, 0, 0.02};
    std::vector<double> inputVelocity = {-1, 1};
    std::vector<double> inputSteering = {-30, -15, 0, 15, 30};
    std::vector<std::pair<double, double>> possibleInput;
};
#endif