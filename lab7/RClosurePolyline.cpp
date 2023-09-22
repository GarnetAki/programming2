#include <iostream>
#include <stdarg.h>
#include <vector>
#include <string>
#include <cmath>
#include <exception>

#include "RGeometry.h"

RClosurePolyline::RClosurePolyline() : RPolyline() {}

RClosurePolyline::RClosurePolyline(std::vector<RPoint> &rp) : RPolyline(rp) {}

RClosurePolyline::RClosurePolyline(const RClosurePolyline &rpl) : RPolyline(rpl) {}

double RClosurePolyline::perimeter()
{
    double sum = 0;
    for (int i = 0; i < countOfPoints - 1; ++i)
    {
        sum += points[i].dist(points[i + 1]);
    }
    sum += points[countOfPoints - 1].dist(points[0]);
    return sum;
}