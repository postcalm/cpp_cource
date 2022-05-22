
#include <iostream>
#include <string>

struct Base 
{
    Base() { std::cout << "Base : created \n"; }
};

struct D1 : Base 
{
    D1() { std::cout << "D1 : created \n"; }
    int a{ 1 };
};

struct D2 : Base 
{
    D2() { std::cout << "D2 : created \n"; }
    int a{ 2 };
};

struct D3 : D1, D2 
{
    D3() { std::cout << "D3 : created \n"; }
};

Base const *D1BaseToD2Base(Base const *base)
{
    std::cout << "base " << base << std::endl;
    auto *a = static_cast<Base const*>(base);
    std::cout << "a " << a << std::endl;
    auto *b = static_cast<D1 const*>(a);
    std::cout << "b " << b << std::endl;
    auto *c = static_cast<D3 const*>(b);
    std::cout << "c " << c << std::endl;
    auto *d = static_cast<D2 const*>(c);
    std::cout << "d " << d << std::endl;
    /*return static_cast<Base const*>(
        static_cast<D2 const*>(
            static_cast<D3 const*>(
                static_cast<D1 const*>(
                    static_cast<Base const*>(base)))));*/
    return d;
}

int main(int argc, char const *argv[])
{
    D3 d3Obj;
    const Base *ptr = static_cast<D1 *>(&d3Obj);
    std::cout << static_cast<D1 const*>(ptr)->a << ptr << std::endl;
    const Base *ptra = nullptr;
    std::cout << ptra << std::endl;

    ptra = D1BaseToD2Base(ptr);
    std::cout << static_cast<D2 const*>(ptra)->a << std::endl;
    return 0;
}
