#include <iostream>
#include <stdarg.h>
#include <vector>
#include <string>
#include <cmath>
#include <exception>

#include "RGeometry.h"

RRegularPolygon::RRegularPolygon() : RPolygon() {}

RRegularPolygon::RRegularPolygon(const RRegularPolygon &rpl) : RPolygon(rpl) {}

RRegularPolygon::RRegularPolygon(std::vector<RPoint> &rp) : RPolygon(rp)
{
    int siz = points[0].dist(points[1]);
    for (int i = 0; i < countOfPoints - 1; ++i)
    {  
        if (points[i].dist(points[i + 1]) != siz)
        {
            throw std::invalid_argument("it's not a regular polygon.");
        }
    }
}

double RRegularPolygon::area(){
    double a = points[0].dist(points[1]);
    double n = points.size();
    return n*a*a/(4*tan(3.14159265 / n));
}