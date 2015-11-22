// cmp.h - return <0, =0, >0 if less, equal, or greater lexicographically
#pragma once

namespace enumerator {

	template<class I, class J>
	inline auto cmp(I i, J j)
	{
		while (i && j && *i++ == *j++)
			;

		return !i ? (!j ? 0 : -1) 
			      : (!j ? 1 : *i - *j);
	}

} // enumerator

#ifdef _DEBUG
#include <cassert>
#include "null_.h"

inline void test_cmp()
{
	using enumerator::cmp;
	using enumerator::null;

	assert (cmp(null(""), null("")) == 0);
	assert (cmp(null("a"), null("b")) < 0);
	assert (cmp(null("b"), null("a")) > 0);
	assert (cmp(null(""), null("a")) < 0);
	assert (cmp(null("a"), null("")) > 0);
	assert (cmp(null("ab"), null("a")) > 0);
	assert (cmp(null("ba"), null("a")) > 0);
	assert (cmp(null("abc"), null("abz")) == 'c' - 'z');
}

#endif // _DEBUG