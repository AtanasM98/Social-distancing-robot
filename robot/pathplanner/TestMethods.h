#ifndef H_TESTS_H
#define H_TESTS_H
#include "PathPlanner.h"
#include "Coordinate.h"
#include "Map.h"
#include "Path.h"

class TestAll
{
    public:
    void TestPathPlanner();
    private:
    void TestCoordinate();
    void TestGetNextPathNode();
    void TestMap();
    void TestPath();
    void TestPathMap();
    void TestVehicle();
};
#endif