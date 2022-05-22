#include <tuple>

template<int one, int two, typename ...T>
auto to_pair(std::tuple<T...> t) -> decltype( std::make_pair( std::get<one>(t), std::get<two>(t) ) )
{
	return std::make_pair(std::get<one>(t), std::get<two>(t));
}

int main()
{
	auto t = std::make_tuple(0, 3.5, "Hello");
	std::pair<double, char const*> p = to_pair<1, 2>(t);
	return 0;
}