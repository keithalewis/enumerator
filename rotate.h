// rotate.h - left rotate a range
#pragma once
#include <algorithm>

namespace enumerator {

	template<class E>
	inline void rotate(E b, E m)
	{
		if (!b || !m || b == m)
			return;

		E n = m;
		while (b != n) {
			auto t = *b;
			*n = *b;
			*b = t;
			++b;
			++n;
			if (!n)
				n = m;
			else if (b == m)
				m = n;
		}
	}
	template<class E>
	inline void rotate_iter_swap(E b, E m)
	{
		if (!b || !m || b == m)
			return;

		E n = m;
		while (b != n) {
//			iter_swap(b++, n++);
			iter_swap(b, n);
			++b;
			++n;
			if (!n)
				n = m;
			else if (b == m)
				m = n;
		}
	}
	template<class E>
	inline void rotate_swap(E b, E m)
	{
		if (!b || !m || b == m)
			return;

		E n = m;
		while (b != n) {
//			std::swap(*b++, *n++);
			std::swap(*b, *n);
			++b;
			++n;
			if (!n)
				n = m;
			else if (b == m)
				m = n;
		}
	}

} // enumerator

#ifdef _DEBUG
#include <cassert>
#include <cstring>
#include <algorithm>
#include <iostream>
#include "timer.h"
#include "range_.h"

// http://en.cppreference.com/w/cpp/algorithm/rotatetemplate 
template<class ForwardIt>
inline void rotate(ForwardIt first, ForwardIt n_first, ForwardIt last)
{
	ForwardIt next = n_first;
	while (first != next) {
		std::iter_swap(first++, next++);
		if (next == last) {
			next = n_first;
		} else if (first == n_first) {
			n_first = next;
		}
	}
}

inline void test_rotate()
{
	using namespace enumerator;

	timer::clock<> c;

	std::vector<int> i(1'000);

	c.start();
	for (size_t m = 0; m < i.size(); ++m)
		::rotate(i.begin(), i.begin() + m, i.end());
	c.stop();
	auto milli = c.count();

	std::cout << milli << '\n';

	auto e = range(i);
	c.start();
	for (ptrdiff_t m = 0; static_cast<size_t>(m) < i.size(); ++m)
		enumerator::rotate(e, e + m);
	c.stop();
	milli = c.count();
	std::cout << milli << '\n';

	c.start();
	for (ptrdiff_t m = 0; static_cast<size_t>(m) < i.size(); ++m)
		enumerator::rotate_iter_swap(e, e + m);
	c.stop();
	milli = c.count();
	std::cout << milli << '\n';
	c.start();
	for (ptrdiff_t m = 0; static_cast<size_t>(m) < i.size(); ++m)
		enumerator::rotate_swap(e, e + m);
	c.stop();
	milli = c.count();
	std::cout << milli << '\n';
}

#endif // _DEBUG
