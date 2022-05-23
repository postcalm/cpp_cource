#include <list>
#include <future>
#include <thread>
#include <functional>
#include <iostream>
#include <algorithm>
#include <vector>


template <class It, class F1, class F2>
auto map_reduce(It p, It q, F1 f1, F2 f2, size_t threads) -> decltype(f2(f1(*p), f1(*p)))
{
	using type = decltype(f2(f1(*p), f1(*p)));
	auto dist = std::distance(p, q) / threads;
	std::vector<type> values;
	std::vector<std::thread> thds;
	type result;
	It next = p;
	It prev;
	for (auto i = 0; i < threads; ++i)
	{
		prev = next;
		if (i == threads - 1) next = q;
		else std::advance(next, dist);
		thds.push_back(std::thread([&result, f1, f2, &prev, next]() {
			result = f1(*prev);
			while (++prev != next)
			{
				result = f2(result, f1(*prev));
			}
			}));
		values.push_back(result);
	}

	for (auto& th : thds) th.join();

	auto it = values.begin();
	result = *it;
	while (++it != values.end())
	{
		result = f2(result, (*it));
	}
	return result;
}

int main()
{
	std::list<int> l = { 1,2,3,4,5,6,7,8,9,10 };
	// параллельное суммирование в 3 потока
	auto sum = map_reduce(
		l.begin(),
		l.end(),
		[](int i) {return i; },
		std::plus<int>(),
		3
	);
	std::cout << sum << std::endl;
	// проверка наличия чётных чисел в четыре потока
	auto has_even = map_reduce(
		l.begin(),
		l.end(),
		[](int i) {return i % 2 == 0; },
		std::logical_or<bool>(),
		4
	);
	std::cout << has_even << std::endl;
	return 0;
}