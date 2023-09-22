#include <iostream>
#include <stdarg.h>
#include <vector>
#include <string>
#include <cmath>
#include <exception>

#include "RGeometry.h"

RTrapezoid::RTrapezoid() : RPolygon() {}

RTrapezoid::RTrapezoid(const RTrapezoid &rpl) : RPolygon(rpl) {}

RTrapezoid::RTrapezoid(std::vector<RPoint> &rp) : RPolygon(rp)
{
    if (rp.size() != 4 || points[0].dist(points[1]) != points[2].dist(points[3]) || points[1].dist(points[2]) != points[3].dist(points[0]))
        throw std::invalid_argument("it's not a trapezoid.");
}