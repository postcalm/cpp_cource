#include <list>
#include <future>
#include <thread>
#include <functional>
#include <iostream>
#include <algorithm>
#include <vector>

template <class It, class F1, class F2>
auto do_async(It prev, It next, F1 f1, F2 f2) -> decltype(f2(f1(*prev), f1(*prev))) 
{
	It iter = prev;
	auto res = f1(*iter);
	while (++iter != next) {
		res = f2(res, f1(*iter));
	}
	return res;
}

template <class It, class F1, class F2>
auto map_reduce(It p, It q, F1 f1, F2 f2, size_t threads) -> decltype(f2(f1(*p), f1(*p)))
{
	auto dist = std::distance(p, q) / threads;
	std::vector<std::future<decltype(f2(f1(*p), f1(*p)))>> futures;
	It next = p, prev;
	for (int i = 0; i < threads - 1; ++i)
	{
		prev = next;
		std::advance(next, dist);
		futures.push_back(std::async(std::launch::async, do_async<It, F1, F2>, prev, next, f1, f2));
	}
	futures.push_back(std::async(std::launch::async, do_async<It, F1, F2>, next, q, f1, f2));
	decltype(f2(f1(*p), f1(*p))) result = (*futures.begin()).get();
	for (auto i = std::next(futures.begin()); i != futures.end(); ++i)
	{
		result = f2(result, (*i).get());
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