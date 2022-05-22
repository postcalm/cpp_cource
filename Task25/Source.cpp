#include <iostream>

template<int N>
struct F
{
	static int const value = F<N - 1>::value + F<N - 2>::value;
};

template<>
struct F<1>
{
	static int const value = 1;
};

template<>
struct F<0>
{
	static int const value = 0;
};

int main()
{
	std::cout << F<10>::value << std::endl;
	return 0;
}