#include <iostream>
#include <stdarg.h>
#include <vector>
#include <string>
#include <cmath>
#include <exception>

#include "RGeometry.h"

RPolyline::RPolyline()
{
    countOfPoints = 0;
    points.resize(0);
}

RPolyline::RPolyline(std::vector<RPoint> &rpl)
{
    countOfPoints = rpl.size();
    points.resize(countOfPoints);
    if(rpl.size()==0){
        countOfCoord = 2;
    }
    else{
        countOfCoord = rpl[0].cntCoord();
        for (int i = 0; i < countOfPoints; ++i)
        {
            points[i] = rpl[i];
            if (rpl[i].cntCoord() != countOfCoord)
            {
                throw std::invalid_argument("point has got other count of coordinates.");
            }
        }
    }
}

RPolyline::RPolyline(const RPolyline &rpl)
{
    countOfCoord = rpl.countOfCoord;
    countOfPoints = rpl.countOfPoints;
    points.resize(countOfPoints);
    for (int i = 0; i < countOfPoints; ++i)
    {
        points[i] = rpl.points[i];
    }
}

RPolyline& RPolyline::operator=(const RPolyline &rpl)
{
    countOfCoord = rpl.countOfCoord;
    countOfPoints = rpl.countOfPoints;
    points.resize(countOfPoints);
    for (int i = 0; i < countOfPoints; ++i)
    {
        points[i] = rpl.points[i];
    }
    return *this;
}

double RPolyline::perimeter()
{
    double sum = 0;
    for (int i = 0; i < countOfPoints - 1; ++i)
    {
        sum += points[i].dist(points[i + 1]);
    }
    return sum;
}