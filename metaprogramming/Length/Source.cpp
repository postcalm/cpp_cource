#include <iostream>

template<int ... Types>
struct IntList;

template<int H, int ...T>
struct IntList<H, T...>
{
	static int const Head = H;
	using Tail = IntList<T...>;
};

template<>
struct IntList<> {};

template<typename TL>
struct Length
{
	static int const value = 1 + Length<typename TL::Tail>::value;
};

template<>
struct Length<IntList<>>
{
	static int const value = 0;
};

int main()
{
	using primes = IntList<2,3,5,7,11,13>;

	constexpr int head = primes::Head;
	constexpr size_t len = Length<primes>::value; // 6
	std::cout << len << std::endl;

	using odd_primes = primes::Tail;
	return 0;
}