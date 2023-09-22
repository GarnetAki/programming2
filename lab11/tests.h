#ifndef TEST
#define TEST
#include <vector>
#include <list>
#include <map>
#include <fstream>
#include <chrono>
#include <cstdlib>

using namespace std::chrono;

template <typename Allocator>
class Tests {
private:
    template<typename Container, typename Function>
    double test (Allocator& alloc, size_t cnt, Function add) {
        auto start = high_resolution_clock::now();
        Container c(alloc);
        for (size_t i = 0; i < cnt; ++i) {
            add(c);
        }
        auto diff = high_resolution_clock::now();
        return ((double)(diff.time_since_epoch().count() - start.time_since_epoch().count()))/1000000;
    }

public:
    Tests() = default;

    double test_vector(Allocator& alloc, size_t cnt) {
        return test<std::vector<char, Allocator>>(alloc, cnt, [](std::vector<char, Allocator>& c) {
            c.push_back('a');
        });
    }

    double test_list(Allocator& alloc, size_t cnt) {
        return test<std::list<char, Allocator>>(alloc, cnt, [](std::list<char, Allocator>& c) {
            c.push_back('a');
        });
    }

    double test_map(Allocator& alloc, size_t cnt) {
        return test<std::map<int, char, std::less<int>, Allocator>>(alloc, cnt, [](std::map<int, char, std::less<int>, Allocator>& c) {
            c[std::rand() % (INT32_MAX)] = 'a';
        });
    }
};

#endif