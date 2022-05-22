#include <algorithm>
#include <vector>
#include <iostream>
#include <iterator>


struct ElementN
{
    explicit ElementN(size_t n)
        : n(n), i(0)
    {}

    template<class T>
    bool operator()(T const& t) { return (i++ == n); }

    size_t n;
    size_t i;
};

int main()
{
    std::vector<int> v = { 0,1,2,3,4,5,6,7,8,9,10,11,12 };

    v.erase(std::remove_if(v.begin(), v.end(), ElementN(3)), v.end());

    for (int i : v)
        std::cout << i << ' ';

    return 0;
}