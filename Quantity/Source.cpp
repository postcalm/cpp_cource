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

template<int a, int b>
struct Plus
{
	static int const value = a + b;
};

template<int a, int b>
struct Minus
{
	static int const value = a - b;
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

template<int m = 0, int kg = 0, int s = 0, int A = 0, int K = 0, int mol = 0, int cd = 0>
using Dimension = IntList<m, kg, s, A, K, mol, cd>;

template <typename Dimension> struct Quantity;

using NumberQ = Quantity<Dimension<>>;          // число без размерности
using LengthQ = Quantity<Dimension<1>>;          // метры
using MassQ = Quantity<Dimension<0, 1>>;       // килограммы
using TimeQ = Quantity<Dimension<0, 0, 1>>;    // секунды
using VelocityQ = Quantity<Dimension<1, 0, -1>>;   // метры в секунду
using AccelQ = Quantity<Dimension<1, 0, -2>>;   // ускорение, метры в секунду в квадрате
using ForceQ = Quantity<Dimension<1, 1, -2>>;   // сила в ньютонах

template<typename Dimension>
struct Quantity 
{
	double value_;
	using type = Dimension;

	double value() const { return value_; }
	
	Quantity() = default;
	explicit Quantity(double d) : value_(d) {}

	Quantity<Dimension> operator+(const Quantity<Dimension> &input)
	{
		return Quantity<Dimension>(value_ + input.value);
	}

	Quantity<Dimension> operator-(const Quantity<Dimension> &input)
	{
		return Quantity<Dimension>(value_ - input.value);
	}

	template<typename D>
	auto operator*(const Quantity<D>& input) -> decltype(Quantity<typename Zip<type, D, Plus>::type>())
	{
		using type_res = typename Zip<type, D, Plus>::type;
		double result = value_ * input.value();
		return Quantity<type_res>(result);
	};

	template<typename D>
	auto operator/(const Quantity<D>& input) -> decltype(Quantity<typename Zip<type, D, Minus>::type>())
	{
		using type_res = typename Zip<type, D, Minus>::type;
		double result = value_ / input.value();
		return Quantity<type_res>(result);
	};
};



template<typename D>
auto operator*(Quantity<D> f, double l) -> decltype(f * Quantity<Dimension<>>(l))
{
	return f * Quantity<Dimension<>>(l);
}

template<typename D>
auto operator*(double f, Quantity<D> const &l) -> decltype(f * l)
{
	return f * l;
}

template<typename D>
auto operator/(Quantity<D> f, double l) -> decltype(f / Quantity<Dimension<>>(l))
{
	return f / Quantity<Dimension<>>(l);
}

template<typename D>
auto operator/(double f, Quantity<D> const& l) -> decltype(f / l)
{
	return f / l;
}

int main()
{
	LengthQ   l{ 30000 };      // 30 км
	TimeQ     t{ 10 * 60 };    // 10 минут
	// вычисление скорости
	VelocityQ v = l / t;     // результат типа VelocityQ, 50 м/с

	AccelQ    a{ 9.8 };        // ускорение свободного падения
	MassQ     m{ 80 };         // 80 кг
	// сила притяжения, которая действует на тело массой 80 кг
	ForceQ    f = m * a;     // результат типа ForceQ

	return 0;
}