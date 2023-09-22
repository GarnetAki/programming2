#include <iostream>
#include <stdarg.h>
#include <vector>
#include <string>
#include <cmath>
#include <exception>
#include <map>

#include "RPolynom.h"

RPolynom::RPolynom()
{
}

RPolynom::RPolynom(int n, ...)
{
    va_list coef;
    va_start(coef, n);
    for (int i = 0; i < n; ++i)
    {
        coefficients[i] = va_arg(coef, double);
    }
    va_end(coef);
}

RPolynom::RPolynom(const std::vector <std::pair<int, double>> &rp)
{
    int n = rp.size();
    for (int i = 0; i < n; ++i)
    {
        coefficients[rp[i].first] = rp[i].second;
    }
}

RPolynom::RPolynom(const RPolynom &rp)
{
    coefficients = rp.coefficients;
}

void RPolynom::changeKthCoefficient(int k, double x)
{
    coefficients[k] = x;
}

RPolynom RPolynom::clearNullsAndZeros(){
    RPolynom tmp;
    for(auto it: coefficients){
        if(it.second != 0)
            coefficients[it.first] = it.second;
    }
    return tmp;
}

RPolynom &RPolynom::operator=(const RPolynom &rp)
{
    coefficients = rp.coefficients;
    return *this;
}

bool RPolynom::operator==(const RPolynom &rp)const
{
    return coefficients == rp.coefficients;
}

bool RPolynom::operator!=(const RPolynom &rp)const
{
    return coefficients != rp.coefficients;
}

RPolynom &RPolynom::operator+=(const RPolynom &rp)
{
    for (auto it : rp.coefficients)
    {
        coefficients[it.first] += it.second;
    }
    clearNullsAndZeros();
    return *this;
}

RPolynom &RPolynom::operator-=(const RPolynom &rp)
{
    for (auto it : rp.coefficients)
    {
        coefficients[it.first] -= it.second;
    }
    clearNullsAndZeros();
    return *this;
}

RPolynom operator+(const RPolynom &rp1, const RPolynom &rp2)
{
    RPolynom rp = rp1;
    rp += rp2;
    rp.clearNullsAndZeros();
    return rp;
}

RPolynom operator-(const RPolynom &rp1, const RPolynom &rp2)
{
    RPolynom rp = rp1;
    rp -= rp2;
    rp.clearNullsAndZeros();
    return rp;
}

RPolynom operator-(const RPolynom &rp)
{
    RPolynom rp0 = rp;
    for (auto it : rp0.coefficients)
    {
        rp0.coefficients[it.first] = -1 * it.second;
    }
    rp0.clearNullsAndZeros();
    return rp0;
}

RPolynom &RPolynom::operator*=(const double &rp)
{
    for (auto it : coefficients)
    {
        coefficients[it.first] = rp * it.second;
    }
    return *this;
}

RPolynom &RPolynom::operator/=(const double &rp)
{
    for (auto it : coefficients)
    {
        coefficients[it.first] = it.second / rp;
    }
    return *this;
}

RPolynom operator*(const RPolynom &rp1, const double &rp2)
{
    RPolynom rp;
    rp.coefficients = rp1.coefficients;
    rp *= rp2;
    return rp;
}

RPolynom operator*(const double &rp2, const RPolynom &rp1)
{
    RPolynom rp;
    rp.coefficients = rp1.coefficients;
    rp *= rp2;
    return rp;
}

RPolynom operator/(const RPolynom &rp1, const double &rp2)
{
    RPolynom rp;
    rp.coefficients = rp1.coefficients;
    rp /= rp2;
    return rp;
}

RPolynom &RPolynom::operator*=(const RPolynom &rp)
{
    RPolynom tmp;
    for (auto it : coefficients)
    {
        for (auto iter : rp.coefficients)
        {
            tmp.coefficients[it.first + iter.first] += it.second * iter.second;
        }
    }
    *this = tmp;
    return *this;
}

RPolynom operator*(const RPolynom &rp1, const RPolynom &rp2)
{
    RPolynom tmp;
    for (auto it : rp1.coefficients)
    {
        for (auto iter : rp2.coefficients)
        {
            tmp.coefficients[it.first + iter.first] += it.second * iter.second;
        }
    }
    return tmp;
}

std::ostream &operator<<(std::ostream &out, const RPolynom &rp)
{
    if(rp.coefficients.size()==0){
        out << 0;
    }else{
        int key = 0;
        for(auto it: rp.coefficients){
            if(key)
                out << " + ";
            if(it.first == 0)out << it.second;
            else out << it.second << " * (x^" << it.first << ")";
            key = 1;
        }
    }
    return out;
}

RPolynom &operator>>(std::istream &in, RPolynom &rp)
{
    int h1;
    double h2;
    rp.coefficients.clear();
    while(in >> h1 >> h2){
        rp.coefficients[h1] += h2;
    }
    return rp;
}

double RPolynom::operator[](int i){
    return coefficients[i];
}