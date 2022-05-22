#include <iostream>

template<class F>
void for_each_int(int* p, int* q, F f)
{
    for (; p != q; ++p)
    {
        f(*p);
    }
}

int main()
{
    int m[10] = { 1,2,3,4,5,6,7,8,9,10 };
    auto square_fun = [](int& x) { x *= x; };
    for_each_int(m, m + 10, square_fun);
    std::cout << m[2] << std::endl;
    return 0;
}