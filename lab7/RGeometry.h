#ifndef R_GEOM
#define R_GEOM

class RPoint
{
protected:
    int countOfCoordinates;
    
public:
    std::vector<double> coordinates;

    RPoint();
    RPoint(int n, ...);
    RPoint(const RPoint &rp);
    int cntCoord()const;
    double CrossProduct(RPoint &a, RPoint &b)const;
    double dist(const RPoint &rp)const;
    void addCoordinate(double x);
    void deleteLastCoordinate();
    RPoint& operator=(const RPoint &rp);
    void changeKthCoordinate(int k, double x);
    bool operator==(const RPoint &rp)const;
};

class RPolyline
{
protected:
    int countOfPoints;
    int countOfCoord;
    std::vector<RPoint> points;
public:
    RPolyline();
    RPolyline(std::vector<RPoint> &rpl);
    RPolyline(const RPolyline &rpl);
    RPolyline& operator=(const RPolyline &rpl);
    virtual double perimeter();
};

class RClosurePolyline : public RPolyline
{
public:
    RClosurePolyline();
    RClosurePolyline(std::vector<RPoint> &rp);
    RClosurePolyline(const RClosurePolyline &rpl);
    virtual double perimeter();
};

class RPolygon : public RClosurePolyline
{
public:
    RPolygon();
    RPolygon(const RPolygon &rpl);
    RPolygon(std::vector<RPoint> &rp);
    virtual double area();
};

class RTriangle : public RPolygon
{
public:
    RTriangle();
    RTriangle(const RTriangle &rpl);
    RTriangle(std::vector<RPoint> &rp);
};

class RTrapezoid : public RPolygon
{
public:
    RTrapezoid();
    RTrapezoid(const RTrapezoid &rpl);
    RTrapezoid(std::vector<RPoint> &rp);
};

class RRegularPolygon : public RPolygon
{
public:
    RRegularPolygon();
    RRegularPolygon(const RRegularPolygon &rpl);
    RRegularPolygon(std::vector<RPoint> &rp);
    virtual double area();
};

#include "RPoint.cpp"
#include "RPolyline.cpp"
#include "RClosurePolyline.cpp"
#include "RPolygon.cpp"
#include "RTriangle.cpp"
#include "RTrapezoid.cpp"
#include "RRegularPolygon.cpp"

#endif