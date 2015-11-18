// swap.h - swap ranges
#pragma once
#include <algorithm>
#include <type_traits>

namespace enumerator {

	template<class I, class J>
	inline auto swap(I i, J j)
	{
		while (i && j)
			std::iter_swap(i++, j++);

		return j;
	}

} // enumerator

#ifdef _DEBUG
#include <cassert>
#include "copy.h"
#include "counted_.h"
#include "iota_.h"
#include "null_.h"
#include <string>

inline void test_swap()
{
	using namespace enumerator;

	{
		char i[4] = "abc";
		char j[3] = "de";

		swap(null(i), null(j));
		assert (0 == strncmp(i, "dec", 3));
		assert (0 == strncmp(j, "ab", 2));
	}
}

#endif // _DEBUG