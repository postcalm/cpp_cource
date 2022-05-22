#include <utility>
#include <string>
#include <iostream>


template<typename lambda, class ...Args>
auto apply(lambda func, Args&& ...args) -> decltype(func(std::forward<Args>(args)...))
{
	return func(std::forward<Args>(args)...);
}


int main()
{
	auto fun = [](std::string a, std::string b) {return a += b; };
	std::string s{ "world!" };
	s = apply(fun, std::string{"Hello, "}, s);
	std::cout << s << std::endl;
	return 0;
}