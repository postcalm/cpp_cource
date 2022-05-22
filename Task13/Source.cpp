#include <list>
#include <string>
#include <iostream>
#include <algorithm>
#include <assert.h>

template<class It>
size_t max_increasing_len(It p, It q)
{
    int size = 1;
    size_t max_size = 1;
    if (p != q)
    {
        auto pre = p;
        ++p;
        for (; p != q; p++)
        {
            if (*pre < *p) size++;
            else size = 1;
            pre = p;
            max_size = size;
        }
        return max_size;
    }
    else return 0;
}


int main()
{
    std::list<int> const l = { 1 };
    size_t len1 = max_increasing_len(l.begin(), l.end());
    assert(len1 == 1);
    
    std::list<int> const l2 = { 7,8,9,4,5,6,1,2,3,4 };
    size_t len2 = max_increasing_len(l2.begin(), l2.end());
    assert(len2 == 4);
    
    std::list<int> const l3 = { -3,-2,-1,0,0,1,2,3,4,5, };
    size_t len3 = max_increasing_len(l3.begin(), l3.end());
    assert(len3 == 6);
    
    std::list<std::string> const l4 = { "1","2","3" };
    size_t len4 = max_increasing_len(l4.begin(), l4.end());
    assert(len4 == 3);
    
    std::list<int> const l5 = {};
    size_t len5 = max_increasing_len(l5.begin(), l5.end());
    assert(len5 == 0);
    
    std::list<int> const l6 = { 1, 2 };
    size_t len6 = max_increasing_len(l6.begin(), l6.end());
    assert(len6 == 2);

    std::list<int> const l7 = { 7,8,9,4,5,6,1,2,3,4,5 };
    size_t len7 = max_increasing_len(l7.begin(), l7.end());
    assert(len7 == 5);

    return 0;
}
