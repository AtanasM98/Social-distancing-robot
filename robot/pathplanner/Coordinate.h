#ifndef H_COORDINATE_H
#define H_COORDINATE_H

#include <string>
#include <iostream>
#include <cmath>

class Coordinate
{
    public:
    Coordinate(double rowN, double colN, double robotTurnAngle)
    {
        row = rowN;
        col = colN;
        turnAngle = robotTurnAngle;
        SetDiscRow();
        SetDiscCol();
    }

    Coordinate(double rowN, double colN)
    {
        row = rowN;
        col = colN;
        SetDiscRow();
        SetDiscCol();
    }
    Coordinate() { }

    double GetRow() { return row; }

    double GetCol() { return col; }

    void SetDiscRow()
    {
        if(row > 0)
            discRow = std::ceil(row);
        else
            discRow = std::floor(row);
    }

    void SetDiscCol()
    {
        if(col > 0)
            discCol = std::ceil(col);
        else
            discCol = std::floor(col);
    }

    double GetTurnAngle() { return turnAngle; }

    void SetRow(double r) 
    {
        row = r;
        SetDiscRow();
    }

    void SetCol(double c) 
    {
        col = c;
        SetDiscCol();
    }

    void SetTurnAngle(double t) { turnAngle = t; }

    bool operator==(const Coordinate& rhs) const
    {
        return discRow == rhs.discRow && discCol == rhs.discCol;
    }

    friend std::ostream& operator<<(std::ostream& os, Coordinate& c)
    {
        os << c.GetRow() << '/' << c.GetCol() << '/' << c.GetTurnAngle();
        return os;
    }

    private:
    double row, col, turnAngle, discRow, discCol;
};
#endif