#include <iostream>
#include <tuple>
#include <utility>
#include <functional>

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

template<class F, typename ...Args, int ...I>
auto apply_impl(F &&f, std::tuple<Args...> t, IntList<I...>) -> decltype(f(std::get<I>(t)...))
{
	return f(std::get<I>(t)...);
}

template<class F, typename ...Args>
auto apply(F&& f, std::tuple<Args...> t) -> decltype(apply_impl(f, t, typename Generate<(sizeof ...(Args))>::type()))
{
	return apply_impl(f, t, typename Generate<(sizeof ...(Args))>::type());
}

int main()
{
	auto f = [](int x, double y, double z) { return x + y + z; };
	auto t = std::make_tuple(30, 5.0, 1.6);  // std::tuple<int, double, double>
	auto res = apply(f, t);                // res = 36.6
	std::cout << res << std::endl;
	return 0;
}