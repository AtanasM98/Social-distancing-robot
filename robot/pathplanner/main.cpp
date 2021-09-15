#include "PathPlanner.h"
#include "Map.h"
#include "Coordinate.h"
#include "Path.h"

#include <iostream>

int main()
{
    std::cout << "Hello, World! One day I am going to control a big robot!" << std::endl;
    std::cout << "My name is Path Planner!" << std::endl;
    Coordinate start(0,0,0);
    Coordinate end(20,20,0);
    Map map(40, 40);
    map.addObstacles({Coordinate(1, 1), Coordinate(19,19)});
    PathPlanner planner(start, end, map);
    Coordinate current = planner.getNextPathNode();
    while(!(current == end))
    {
        current = planner.getNextPathNode();
        //std::cin.get();
    }
    std::cout << "Pathplanner passed with " << planner.getCounter() << " steps." << std::endl;
    return 0;
}