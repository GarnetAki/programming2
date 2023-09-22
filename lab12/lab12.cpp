#include <bits/stdc++.h>
#include "polynom.h"

int main(){
    point<6, 3, 2, 1> arr;
    std::cout << arr.func << '\n';
    std::cout << point<5, 0, 1, 1>::func << '\n';
    std::cout << point<3, 2, 0, 0, 3, 0, 0>::func << '\n';
    std::cout << arr;
    std::cout << point<5, 1, 3, 0, -7, 0, 0>();
}