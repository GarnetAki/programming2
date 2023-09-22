#ifndef R_NOM
#define R_NOM

class RPolynom
{
protected:
    std::map <int, double> coefficients;

public:
    RPolynom();
    RPolynom(std::map <int, double> &rp) : coefficients{rp} {};
    RPolynom(const std::vector <std::pair<int, double>> &rp);
    RPolynom(int n, ...);
    RPolynom(const RPolynom &rp);
    ~RPolynom() = default;
    RPolynom clearNullsAndZeros();
    void changeKthCoefficient(int k, double x);
    RPolynom &operator=(const RPolynom &rp);
    bool operator==(const RPolynom &rp)const;
    bool operator!=(const RPolynom &rp)const;
    RPolynom &operator+=(const RPolynom &rp);
    RPolynom &operator-=(const RPolynom &rp);
    friend RPolynom operator+(const RPolynom &rp1, const RPolynom &rp2);
    friend RPolynom operator-(const RPolynom &rp1, const RPolynom &rp2);
    friend RPolynom operator-(const RPolynom &rp);
    RPolynom &operator*=(const RPolynom &rp);
    RPolynom &operator*=(const double &rp);
    RPolynom &operator/=(const double &rp);
    friend RPolynom operator*(const RPolynom &rp1, const RPolynom &rp2);
    friend RPolynom operator*(const double &rp2, const RPolynom &rp1);
    friend RPolynom operator*(const RPolynom &rp1, const double &rp2);
    friend RPolynom operator/(const RPolynom &rp1, const double &rp2);
    friend std::ostream &operator<<(std::ostream &out, const RPolynom &rp);
    friend RPolynom &operator>>(std::istream &in, RPolynom &rp);
    double operator[](int i);
};

#include "RPolynom.cpp"

#endif