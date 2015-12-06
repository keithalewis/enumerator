// cmp.h - return <0, =0, >0 if less, equal, or greater lexicographically
#pragma once

namespace enumerator {

	template<class I, class J>
	inline auto cmp(I i, J j)
	{
		while (i && j && *i == *j) {
			++i;
			++j;
		}

		return i ? (j ? *i - *j : 1 ) : j ? -1 : 0; 
	}

} // enumerator

#ifdef _DEBUG
#include <cassert>
#include "null_.h"
#include "ptr_.h"

inline void test_cmp()
{
	using enumerator::cmp;
	using enumerator::null;
	using enumerator::ptr;

	auto np = [](auto i) { return null(ptr(i)); };

	assert (cmp(np(""), np("")) == 0);
	assert (cmp(np("a"), np("b")) < 0);
	assert (cmp(np("b"), np("a")) > 0);
	assert (cmp(np(""), np("a")) < 0);
	assert (cmp(np("a"), np("")) > 0);
	assert (cmp(np("ab"), np("a")) > 0);
	assert (cmp(np("a"), np("ab")) < 0);
	assert (cmp(np("ba"), np("a")) > 0);
	assert (cmp(np("b"), np("ab")) > 0);
	assert (cmp(np("abc"), np("abz")) == 'c' - 'z');
	assert (cmp(np("abz"), np("abc")) == 'z' - 'c');
}

#endif // _DEBUG