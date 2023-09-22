#include <bits/stdc++.h>
#include <exception>
#include "aloc.h"
#include "tests.h"

std::vector <std::size_t> blocks = {4, 12, 8, 4, 4};
ralloc <int> a(blocks);

void tmp(){
    ralloc <block> b = a;
}


int main(){
    try{
        tmp();
        std::vector <std::size_t> blockss(1000, 10000000);
        ralloc <char> c(blockss);
        //std::cout << (a==b) << '\n';
        std::cout << (a==c) << '\n';
        //std::cout << sizeof(int);
        auto t0 = a.allocate(1);
        auto t1 = a.allocate(1);
        auto t2 = a.allocate(1);
        std::cout << t2 - a.start() << '\n';
        a.deallocate(t2, 0);
        auto t3 = a.allocate(1);
        std::cout << t3 - a.start() << '\n';
        
        std::vector<char, ralloc<char>> v(c);
        v.push_back('s');
        v.push_back('a');
        v.push_back('d');
        std::cout << v.front() << v[1] << v.back() << '\n';

        std::vector <char> v_simple(8);
        v_simple.push_back('i');
        std::cout << v_simple.back();

        v.push_back('n');
        std::cout << v.back();

        std::list<char, ralloc<char>> l(c);
        l.push_back('i');
        l.push_back('s');
        std::cout << l.back() << l.front();

        std::vector <std::size_t> blocksss(100, 10000000);
        ralloc <std::pair <const int, char>> cc(blocksss);

        std::map <int, char, std::less<int>, ralloc <std::pair <const int, char>>> mm(cc);
        mm[1] = 's';
        mm[2] = 'e';
        mm[6] = 'd';
        std::cout << mm[6] << mm[2] << '\n';
        
        Tests <ralloc<char>> t;
        double test_on_vector = t.test_vector(c, 5000000);
        std::cout << test_on_vector << '\n';
        
        Tests <std::allocator<char>> tt;
        std::allocator<char> al;
        double test_on_vector2 = tt.test_vector(al, 5000000);
        std::cout << test_on_vector2 << '\n';
    }
    catch (const std::exception& err)
    {
        std::cerr << err.what() << std::endl;
    }
}