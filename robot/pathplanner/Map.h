#ifndef H_MAP_H
#define H_MAP_H

#include "Coordinate.h"

#include <iostream>
#include <vector>

class Map
{
    public:
    Map(int maR, int maC)
    {
        maxR = maR;
        maxC = maC;
    }
    
    Map() { }

    void showMap()
    {
        std::cout << "Map: Rows " << maxR << " Cols " << maxC << std::endl;
        for(int i = 0; i < maxR; i++)
        {
            std::cout << "Row " << i << "\t";
            for(int k = 0; k < maxC; k++)
            {
                std::cout << k << "\t";
            }
            std::cout << std::endl;
        }
    }

    bool checkBounds(Coordinate c)
    {
        if(c.GetRow() > maxR || c.GetCol() > maxC || c.GetRow() < 0 || c.GetCol() < 0)
        {
            return false;
        }
        else
        {
            for(unsigned int i = 0; i < this->obstacle.size(); i++)
            {
                if(this->obstacle[i] == c)
                {
                    std::cout << "Encountered obstacle! " << c << std::endl;
                    return false;
                }
            }
            return true;
        }
    }

    inline bool operator==(Map rhs)
    {
        if(maxR == rhs.maxR && maxC == rhs.maxC && obstacle == rhs.obstacle)
        {
            return true;
        }
        return false;
    }

    void addObstacles(std::vector<Coordinate> obs) { obstacle.insert(obstacle.end(), obs.begin(), obs.end()); }

    private:
    int maxR;
    int maxC;
    std::vector<Coordinate> obstacle;
};
#endif