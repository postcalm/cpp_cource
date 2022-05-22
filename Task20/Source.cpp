#include <vector>
#include <string>
#include <sstream>
#include <iostream>
#include <type_traits>
#include <cassert>
#include <exception>

class bad_from_string : public std::exception
{
	std::string info;

public:
	bad_from_string(std::string e = "from string expt") :
		info(e){}
	const char* what() const noexcept 
	{
		return info.c_str();
	}
};

template<class T>
T from_string(std::string const& s)
{
	std::istringstream is(s);
	T type;
	std::string temp;
	is >> std::noskipws >> type;
	std::cout << type << std::endl;
	if(is.fail() || is.peek() != EOF)
		throw bad_from_string("conversion is failed");
	if (!temp.empty())
		throw bad_from_string("conversion is failed");
	return type;
}

int main()
{
	std::string s1("123");
	int    a1 = from_string<int>(s1); // a1 = 123
	double b1 = from_string<double>(s1); // b1 = 123.0
	std::string c1 = from_string<std::string>(s1); // c1 = "123"

	std::string s2("12.3");
	int    a2 = from_string<int>(s2); // исключение
	double b2 = from_string<double>(s2); // b2 = 12.3
	std::string c2 = from_string<std::string>(s2); // c2 = "12.3"

	std::string s3("abc");
	int    a3 = from_string<int>(s3); // исключение
	double b3 = from_string<double>(s3); // исключение
	std::string c3 = from_string<std::string>(s3); // c3 = "abc"
	return 0;
}