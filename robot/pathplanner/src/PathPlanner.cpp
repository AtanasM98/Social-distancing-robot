#include "../PathPlanner.h"
#include "../Coordinate.h"
#include "../Map.h"
#include "../Path.h"

#include <iostream>
#include <utility>

PathPlanner::PathPlanner(Coordinate startPoint, Coordinate endPoint, Map m)
{
	this->startPoint = startPoint;
	this->endPoint = endPoint;
	this->map = m;
	this->openPath.addToPath(startPoint);
	this->openPath.setTarget(endPoint);
	this->robot = Vehicle(startPoint, this->map);
	for(unsigned int i = 0; i < this->inputVelocity.size(); i++)
	{
		for(unsigned int k = 0; k < this->inputSteering.size(); k++)
		{
			this->possibleInput.push_back(std::make_pair(this->inputVelocity[i], this->inputSteering[k]));
		}
	}
}

Coordinate PathPlanner::getNextPathNode()
{
	Coordinate nextCandidate;
	if(this->closedPath.getPath().size() > 0)
	{
		if(this->closedPath.back() == this->endPoint)
		{
			return this->closedPath.back();
		}
	}
	std::vector<Path> possiblePaths;
	Path newPath;
	Coordinate robotTarget;
	Coordinate current = this->openPath.back();
	for(long unsigned int i = 0; i < this->possibleInput.size(); i++)
	{
		robotTarget = robot.GetMovement(this->possibleInput[i].first, 
						this->possibleInput[i].second, this->L);
		if(robotTarget.GetRow() != -1)
		{
			newPath = Path(this->openPath);
			newPath.addToPath(robotTarget);
			possiblePaths.push_back(newPath);
		}
	}
	this->closedPath.addToPath(current);
	double min = 10000;
	for(Path c: possiblePaths)
	{
		Coordinate nc = c.back();
		if(c.getCost() < min)
		{
			min = c.getCost();
			nextCandidate = nc;
		}
	}
	std::cout << "Next Coord " << nextCandidate << " cost " << min << std::endl;
	robot.Move(nextCandidate);
	this->openPath.addToPath(nextCandidate);
	this->stepCounter++;
	return nextCandidate;
}

void PathPlanner::updateMap(Map newM)
{
	this->map = newM;
}