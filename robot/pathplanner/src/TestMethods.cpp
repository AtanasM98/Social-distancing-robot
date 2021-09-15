#include "../TestMethods.h"
#include "../Path.h"
#include "../Map.h"
#include "../Vehicle.h"
#include "../PathPlanner.h"
#include "../Coordinate.h"

#include <iostream>
#include <cassert>
#include <vector>
#include <iomanip>

void TestAll::TestPathPlanner()
{
	this->TestPathMap();
	this->TestGetNextPathNode();
	this->TestMap();
	this->TestPath();
	this->TestVehicle();
}

void TestAll::TestPathMap()
{
	Coordinate c(0,0);
	Map previousM(10, 10);
	PathPlanner p(c, c, previousM);
	Map map(20, 20);
	p.updateMap(map);
	Map testM = p.getMap();
	assert(testM == map);
	assert(!(testM == previousM));
}

void TestAll::TestGetNextPathNode()
{
	Coordinate start(0,0);
	Coordinate end(10,0);
	Map map(10, 10);
	PathPlanner p(start, end, map);
	Coordinate result = p.getNextPathNode();
	Coordinate target(0.992549461023988,0.121842387620196,6.40533119664628);
	assert(target == result);
}

void TestAll::TestMap()
{
	Map map(10, 10);
	map.addObstacles({Coordinate(2, 2), Coordinate(5, 5)});
	Coordinate testC(2, 2);
	Coordinate testC1(-2, 2);
	Coordinate testC2(2, -2);
	Coordinate testC3(4, 4);
	assert(false == map.checkBounds(testC));
	assert(false == map.checkBounds(testC1));
	assert(false == map.checkBounds(testC2));
	assert(true == map.checkBounds(testC3));
}

void TestAll::TestPath()
{
	Coordinate start(0,0);
	Coordinate end(5,0);
	Path p(start, end, 0);
	double distance = 5;
	double result = p.getCost();
	assert(distance == result);
}

void TestAll::TestVehicle()
{
	Coordinate start(5,5);
	Map m(10,10);
	Vehicle robot(start, m);
	Coordinate move = robot.GetMovement(1, 0, 1);
	Coordinate move1 = robot.GetMovement(-10, 0, 1);
	robot.Move(move);
	Coordinate target(6,5);
	Coordinate invalid(-1,-1,-1);
	Coordinate robotMove = robot.GetLoc();
	assert(!(robotMove == start));
	assert(robotMove == target);
	assert(move1 == invalid);
}