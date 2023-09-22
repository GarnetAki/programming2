#include <iostream>
#include <stdarg.h>
#include <vector>
#include <string>
#include <cmath>
#include <exception>

#include "RGeometry.h"

bool positive(int value)
{
    return value>=0;
}
bool negative(int value)
{
    return value<=0;
}

RPolygon::RPolygon() : RClosurePolyline() {}

RPolygon::RPolygon(const RPolygon &rpl) : RClosurePolyline(rpl) {}

RPolygon::RPolygon(std::vector<RPoint> &rp) : RClosurePolyline(rp)
{
    if (countOfCoord != 2)
        throw std::invalid_argument("idk how to work with polygon not in 2D.");
    else if (rp.size() < 3)
    {
        throw std::invalid_argument("cnt of points less than 3.");
    }
    else
    {
        RPoint prev, next;
        int n = rp.size();
        prev.coordinates[0] = points[n - 1].coordinates[0] - points[n - 2].coordinates[0];
        prev.coordinates[1] = points[n - 1].coordinates[1] - points[n - 2].coordinates[1];

        next.coordinates[0] = points[0].coordinates[0] - points[n - 1].coordinates[0];
        next.coordinates[1] = points[0].coordinates[1] - points[n - 1].coordinates[1];

        bool (*sign)(int);
        sign = (CrossProduct(prev, next) >= 0) ? positive : negative;

        bool result = true;
        for (int i = 1; i < n && result; ++i)
        {
            prev = next;
            next.coordinates[0] = points[i].coordinates[0] - points[i - 1].coordinates[0];
            next.coordinates[1] = points[i].coordinates[1] - points[i - 1].coordinates[1];
            result = sign(CrossProduct(prev, next));
        }
        if (result == 0)
            throw std::invalid_argument("polygon is not convex.");
    }
}

double RPolygon::area()
{
    double sum = 0;
    for (int i = 0; i < countOfPoints - 1; ++i)
    {
        sum += points[i].coordinates[0] * points[i + 1].coordinates[1];
        sum -= points[i].coordinates[1] * points[i + 1].coordinates[0];
    }
    sum += points[countOfPoints - 1].coordinates[0] * points[0].coordinates[1];
    sum -= points[countOfPoints - 1].coordinates[1] * points[0].coordinates[0];
    sum = abs(sum);
    sum /= 2;
    return sum;
}