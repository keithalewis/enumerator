// skip.h - functional std::advance
#pragma once
#include <algorithm>
#include <iterator>

namespace enumerator {

	template<class E, class D = typename std::iterator_traits<E>::difference_type>
	inline E skip(D n, E e)
	{
		std::advance(e, n);

		return e;
	}
	
} // namespace enumerator

#ifdef _DEBUG
#include <cassert>
#include <vector>

inline void test_skip()
{
	using enumerator::skip;

	std::vector<int> v{0,1,2};
	auto e1 = skip(1, v.begin());
	assert (*e1 == 1);
	e1 = skip(-1, e1);
	assert (*e1 == 0);
}

#endif // _DEBUG