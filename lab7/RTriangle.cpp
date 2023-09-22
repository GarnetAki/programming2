#include <iostream>
#include <stdarg.h>
#include <vector>
#include <string>
#include <cmath>
#include <exception>

#include "RGeometry.h"

RTriangle::RTriangle() : RPolygon() {}

RTriangle::RTriangle(const RTriangle &rpl) : RPolygon(rpl) {}

RTriangle::RTriangle(std::vector<RPoint> &rp) : RPolygon(rp)
{
    if (rp.size() != 3)
        throw std::invalid_argument("it's not a triangle.");
}