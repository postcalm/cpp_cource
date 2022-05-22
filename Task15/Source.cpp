#include <iostream>
#include <list>


void print_list(std::list<int> list)
{
	for (auto const& elem : list)
		std::cout << elem << " ";
	std::cout << std::endl;
}


int main()
{
	std::list<int> l = { 1,2,3 };
	l.insert(l.begin(), 4);
	l.insert(l.end(), 5);

	print_list(l);

	auto it = l.begin();
	++it;
	++it;

	l.insert(it, 6);

	print_list(l);

	auto rit1 = l.rbegin();
	++rit1;
	++rit1;
	l.insert(rit1.base(), 7);

	print_list(l);

	auto rit2 = l.rbegin();
	++rit2;
	++rit2;
	l.insert(rit2.base(), 8);

	print_list(l);

	return 0;
}