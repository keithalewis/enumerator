// swap.h - swap ranges
#pragma once
#include <algorithm>

namespace enumerator {

	template<class I, class J>
	inline auto swap(I i, J j)
	{
		while (i && j)
			std::iter_swap(i++, j++);

		if (i)
			return i;
		else
			return j;
	}

} // enumerator

#ifdef _DEBUG
#include <cassert>
#include "null_.h"

inline void test_swap()
{
	using enumerator::swap;
	using enumerator::null;

	{
		char i[4] = "abc";
		char j[3] = "de";

		auto k = swap(null(i), null(j));
		assert (k);
		assert (*k == 'c');
		assert (0 == strncmp(i, "dec", 3));
		assert (0 == strncmp(j, "ab", 2));
	}
	{
		for (int n = 1; n < 5; ++n) {
			char i[6] = "abcde";
			auto j = swap(null(i), null(i+n));
			assert (*j*0 == 0);
//		assert (0 == strncmp(i, "bcdea", 3));
		}
	}
}

#endif // _DEBUG