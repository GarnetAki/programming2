#include <iostream>
#include <stdarg.h>
#include <vector>
#include <string>
#include <cmath>
#include <exception>
#include <map>

#include "RGeometry.h"
#include "RPolynom.h"

// virtual area (area of regular polygon)
// * of polynom
// selfkillings of polygon
// sum of polynoms nlog(m) (sad)

double func(RPolyline *a)
{
    return a->perimeter();
}

int main()
{
    try{
        RPoint a = RPoint(2, (double)0, (double)0);
        RPoint b = RPoint(2, (double)1, (double)0);
        RPoint c = RPoint(2, (double)1, (double)1);
        RPoint d = RPoint(2, (double)0, (double)1);
        RPoint e = RPoint(3, (double)2, (double)5, (double)4);
        RPoint f = RPoint(3, (double)2, (double)4, (double)5);
        RPoint g = RPoint(3, (double)1, (double)4, (double)5);
        std::vector<RPoint> ab;
        std::vector<RPoint> ba;
        std::cout << a.dist(b) << '\n';
        ab.push_back(a);
        ab.push_back(b);
        ab.push_back(c);
        ab.push_back(d);
        RRegularPolygon t3 = RRegularPolygon(ab);
        std::cout << t3.area() << '\n';
        ba.push_back(e);
        ba.push_back(f);
        ba.push_back(g);
        /*RClosurePolyline t3 = RClosurePolyline(ab);
        RPolyline t6 = RPolyline(ab);
        RPolygon t1 = RPolygon(ab);
        RPolygon t2 = t1;
        RPolyline* t5 = &t6;
        RClosurePolyline* t4 = &t3;
        std::cout << func(t4) << " " << func(t5) << '\n';
        std::cout << t3.perimeter() << '\n';*/
        RPolynom p1;
        p1.changeKthCoefficient(1, 2);
        p1.changeKthCoefficient(2, 3);
        std::cout << p1<< '\n';
        RPolynom p2 = p1;
        p2/=2;
        std::cout << p2 << '\n';
        std::cout << p1*p2 << '\n';
    }
    catch (const std::exception& err)
    {
        std::cerr << err.what() << std::endl;
    }
    
    return 0;
}