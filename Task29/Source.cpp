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

// бинарна€ метафункци€
template<int a, int b>
struct Plus
{
	static int const value = a + b;
};

template<class Input1, class Input2, template<int...> class Operator>
struct Zip
{
	using type = typename IntCons< Operator<Input1::Head, Input2::Head>::value, 
		typename Zip<typename Input1::Tail, 
		typename Input2::Tail, Operator>::type >::type;
};

template<template<int, int> class Operator>
struct Zip<IntList<>, IntList<>, Operator>
{
	using type = IntList<>;
};

int main()
{
	// два списка одной длины
	using L1 = IntList<1, 2, 3, 4, 5>;
	using L2 = IntList<1, 3, 7, 7, 2>;

	// результат применени€ Ч список с поэлементными суммами
	using L3 = Zip<L1, L2, Plus>::type;  // IntList<2, 5, 10, 11, 7>
	return 0;
}