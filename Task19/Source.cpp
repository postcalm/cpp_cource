#include <algorithm>
#include <array>
#include <vector>
#include <iostream>

template<class Iterator>
size_t count_permutations(Iterator p, Iterator q)
{
	using value_type = typename std::iterator_traits<Iterator>::value_type;

	if (p == q) return 1;
	auto count = 0;
	std::vector<value_type> dup(p, q);
	std::sort(dup.begin(), dup.end());
	do
	{
		if (std::adjacent_find(dup.begin(), dup.end()) == dup.end())
			++count;
	} while (std::next_permutation(dup.begin(), dup.end()));
	return count;
}

int main()
{
	std::array<int, 3> a1 = { 1,2,3 };
	size_t c1 = count_permutations(a1.begin(), a1.end()); // 6
	std::cout << c1 << std::endl;

	std::array<int, 5> a2 = { 1,2,3,4,4 };
	size_t c2 = count_permutations(a2.begin(), a2.end()); // 36
	std::cout << c2 << std::endl;
	return 0;
}