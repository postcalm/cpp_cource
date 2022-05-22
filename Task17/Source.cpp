#include <algorithm>
#include <vector>
#include <list>
#include <iostream>
#include <queue>

void print_vector(std::vector<int> v)
{
	for (auto const& i : v)
		std::cout << i << " ";
	std::cout << std::endl;
}

// алгоритм должен работать с forward итераторами
// и возвращать итератор, который потом будет передан
// в метод erase соответствующего контейнера
template<class FwdIt>
FwdIt remove_nth(FwdIt p, FwdIt q, size_t n)
{
	if (p == q) return q;
	FwdIt prev_;
	size_t i = -1;
	for (auto it = p; it != q; ++it)
	{
		++i;
		if (i >= n && std::next(it) != q)
			std::iter_swap(it, std::next(it));
		prev_ = it;
	}
	if (i >= n) return prev_;
	return q;
}

int main()
{
	std::vector<int> v = { 0,1,2,3,4,5,6,7,8,9,10 };
	v.erase(remove_nth(v.begin(), v.end(), 5), v.end());
	// теперь в v = {0,1,2,3,4,6,7,8,9,10};
	print_vector(v);
	return 0;
}