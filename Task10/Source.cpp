#include <iostream>
#include <algorithm>

template<class F>
int* find_if(int* p, int* q, F f)
{
    for (; p != q; ++p)
        if (f(*p))
            return p;
    return q;
}

int main()
{
    int primes[5] = { 2,3,5,7,11 };

    int m[10] = { 0,0,1,1,4,6,7,8,9,10 };

    auto gen_finder = [](int* a, int* b) 
    {

        return [a, b](int val)->bool 
        {
            bool R = false;

            for (int* mMm = a; mMm != b; ++mMm) 
            {
                if (*mMm == val) {
                    R = true;
                }
            }
            return R;
        };
    };
    // first_prime будет указывать на число 7
    int* first_prime = find_if(m, m + 10, gen_finder(primes, primes + 5));
    std::cout << "first_prime = " << *first_prime << std::endl;
    return 0;
}