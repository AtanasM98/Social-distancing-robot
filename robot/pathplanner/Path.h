#ifndef H_PATH_H
#define H_PATH_H
#include "Coordinate.h"

#include <vector>
#include <math.h>
#include <iostream>

class Path
{
    public:
    Path(Coordinate start, Coordinate end, double addCost)
    {
        addToPath(start);
        target = end;
        additionalCost = addCost;
        totalCost = getTotalCost();
    }

    Path(std::vector<Coordinate> newPath, Coordinate end, double addCost)
    {
        addToPath(newPath);
        target = end;
        additionalCost = addCost;
        totalCost = getTotalCost();
    }

    Path() { };

    Path(const Path& copy) 
    {
        target = copy.target;
        additionalCost = copy.additionalCost;
        for(unsigned int i = 0; i < copy.path.size(); i++)
        {
            path.push_back(copy.path[i]);
        }
        totalCost = getTotalCost();
    };

    void addToPath(Coordinate c)
    {
        path.push_back(c);
        totalCost = getTotalCost();
    }

    void addToPath(std::vector<Coordinate> c)
    {
        path.insert(path.end(), c.begin(), c.end());
    }

    void setTarget(Coordinate t)
    {
        target = t;
    }

    void setAddCost(double addC)
    {
        additionalCost = addC;
    }

    Coordinate getTarget()
    {
        return target;
    }

    double getCost()
    {
        return totalCost;
    }

    std::vector<Coordinate> getPath()
    {
        return path;
    }

    Coordinate back()
    {
        return path.back();
    }

    void removeFirst()
    {
        path.erase(path.begin());  
    }

    friend std::ostream& operator<<(std::ostream& os, Path& p)
    {
        for(unsigned int i = 0; i < p.getPath().size(); i++)
        {
            os << p.getPath()[i] << "\t";
        }
        Coordinate tmp = p.getTarget();
        os << tmp << '\t' << p.getCost();
        return os;
    }

    private:
    double getTotalCost()
    {
        double cost;
        double x, xLen;
        double y, yLen;
        int col, col2, row, row2;
        for(long unsigned int i = 0; i < path.size() - 1; i++)
        {
            row = path[i].GetRow();
            row2 = path[i + 1].GetRow();
            col = path[i].GetCol();
            col2 = path[i + 1].GetCol();
            xLen = std::abs(row - row2);
            yLen = std::abs(col - col2);
            x = std::pow(xLen, 2);
            y = std::pow(yLen, 2);
            cost += std::sqrt(x + y);
        }
        x = std::pow(target.GetRow() - path.back().GetRow(), 2);
        y = std::pow(target.GetCol() - path.back().GetCol(), 2);
        cost += std::sqrt(x + y);
        return cost;
    }

    double totalCost, additionalCost;
    Coordinate target;
    std::vector<Coordinate> path;
};
#endif