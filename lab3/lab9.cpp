#include <bits/stdc++.h>
#include "Circular_buffer.h"
#include "algo.h"

int main(){
    Circular_buffer <int> a(10);
    a.push_end(2);
    std::cout << a.length() << " " << a.front() << std::endl;
    a.push_end(1);
    a.push_end(6);
    std::cout << a.front() << std::endl << *(a.begin() + 1) << std::endl << *(a.begin() + 2) << std::endl;
    bool b = a.begin()==(a.end()-3);
    std::cout << b;
}