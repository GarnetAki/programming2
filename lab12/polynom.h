#ifndef ALOC
#define ALOC
#include <bits/stdc++.h>

template <int x, int p>
class pow_precomp{
public:
    static const int po = x * pow_precomp<x, p-1>::po;
};

template <int x>
class pow_precomp<x, 0>{
public:
    static const int po = 1;
};

template <int p, int coef, int ...other_coefs>
class point
{
public:
    static const int power = 1 + point<p, other_coefs...>::power;
    static const int func = coef * pow_precomp<p, power>::po + point<p, other_coefs...>::func;
    friend std::ostream &operator<<(std::ostream &out, const point){
        point<p, other_coefs...> k;
        if(coef == 0){
            out << k;
        }else{
            if(coef < 0){
                out << "(" << coef << ") * (x ^ " << power << ") + "<< k;
            }else if(coef == 1){
                out << "(x ^ " << power << ") + "<< k;
            }else{
                out << coef << " * (x ^ " << power << ") + "<< k;
            }
        }
        return out;
    }
};

template <int p, int last_coef>
class point<p, last_coef>
{
public:
    static const int power = 0;
    static const int func = last_coef;
    friend std::ostream &operator<<(std::ostream &out, const point){
        if(last_coef < 0){
            out << "(" << last_coef << ")" << '\n';
        }else{
            out << last_coef << '\n';
        };
        return out;
    }
};

#endif