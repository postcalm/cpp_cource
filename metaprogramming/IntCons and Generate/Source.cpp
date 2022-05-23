#include <iostream>

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

template<int H, typename TL>
struct IntCons;

template<int H, int ...TL>
struct IntCons<H, IntList<TL...>>
{
	using type = IntList<H, TL...>;
};

template <int N, int ... Next>
struct Generate : public Generate<N - 1, N - 1, Next...> {};

template <int ... Next>
struct Generate<0, Next ... >
{
	using type = IntList<Next ... >;
};

int main()
{
	using L1 = IntList<2, 3, 4>;

	using L2 = IntCons<1, L1>::type;   // IntList<1,2,3,4>

	using L3 = Generate<5>::type;      // IntList<0,1,2,3,4>
	
	return 0;
}