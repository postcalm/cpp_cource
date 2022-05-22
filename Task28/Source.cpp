#include <iostream>
#include <tuple>

template<int ...Types>
struct IntList;

template<int H, int ...T>
struct IntList<H, T...>
{
	static int const Head = H;
	using Tail = IntList<T...>;
};

template<>
struct IntList<> {};

template <int N, int ... Next>
struct Generate : public Generate<N - 1, N - 1, Next...> {};

template <int ... Next>
struct Generate<0, Next ... >
{
	using type = IntList<Next ... >;
};

auto apply()
{

}

int main()
{
	auto f = [](int x, double y, double z) { return x + y + z; };
	auto t = std::make_tuple(30, 5.0, 1.6);  // std::tuple<int, double, double>
	auto res = apply(f, t);                // res = 36.6
	return 0;
}