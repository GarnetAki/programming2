#include <iostream>
#include <stdarg.h>
#include <vector>
#include <string>
#include <cmath>
#include <exception>
#include <map>

#include "RGeometry.h"

RPoint::RPoint()
{
    countOfCoordinates = 2;
    coordinates.resize(2);
    coordinates[0] = 0;
    coordinates[1] = 0;
}

RPoint::RPoint(int n, ...)
{
    countOfCoordinates = n;
    coordinates.resize(n);

    if (n < 2)
        throw std::invalid_argument("min count of coordinates is 2.");
    va_list coord;
    va_start(coord, n);
    for (int i = 0; i < n; ++i)
    {
        coordinates[i] = va_arg(coord, double);
    }
    va_end(coord);
}

RPoint::RPoint(const RPoint &rp)
{
    countOfCoordinates = rp.countOfCoordinates;
    coordinates.resize(countOfCoordinates);
    for (int i = 0; i < countOfCoordinates; ++i)
    {
        coordinates[i] = rp.coordinates[i];
    }
}

double CrossProduct(RPoint &a, RPoint &b)
{
    return a.coordinates[0]*b.coordinates[1]-a.coordinates[1]*b.coordinates[0];
}

int RPoint::cntCoord()const
{
    return countOfCoordinates;
}

double RPoint::dist(const RPoint &rp)const
{
    double ans = 0;
    for (int i = 0; i < countOfCoordinates; ++i)
    {
        ans += (coordinates[i] - rp.coordinates[i]) * (coordinates[i] - rp.coordinates[i]);
    }
    return sqrt(ans);
}

void RPoint::addCoordinate(double x)
{
    countOfCoordinates++;
    coordinates.resize(countOfCoordinates);
    coordinates[countOfCoordinates - 1] = x;
}

void RPoint::deleteLastCoordinate()
{
    countOfCoordinates--;
    coordinates.resize(countOfCoordinates);
}

RPoint& RPoint::operator=(const RPoint &rp)
{
    countOfCoordinates = rp.countOfCoordinates;
    coordinates.resize(countOfCoordinates);
    for (int i = 0; i < countOfCoordinates; ++i)
    {
        coordinates[i] = rp.coordinates[i];
    }
    return *this;
}

void RPoint::changeKthCoordinate(int k, double x)
{
    if (k > countOfCoordinates)
        throw std::invalid_argument("this point have less count of coordinates.");
    coordinates[k - 1] = x;
}

bool RPoint::operator==(const RPoint &rp)const
{
    bool key = 1;
    if (countOfCoordinates != rp.countOfCoordinates)
    {
        key = 0;
    }
    else
    {
        for (int i = 0; i < countOfCoordinates; ++i)
        {
            if (coordinates[i] != rp.coordinates[i])
            {
                key = 0;
                break;
            }
        }
    }
    return key;
}