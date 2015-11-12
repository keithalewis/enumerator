// copy.h - copy one enumerator to another
#pragma once

namespace enumerator {

	template<class E0, class E1>
	inline void copy(E0 e0, E1 e1)
	{
		while (e0 && e1)
			*e1++ = *e0++;
	}

} // enumerator

#ifdef _DEBUG
#include <cassert>
#include "null_.h"

inline void test_copy()
{
	using enumerator::copy;
	using enumerator::null;

	char bar[3];
	copy(null("foo"), bar);
	assert (0 == strncmp("foo", bar, 3));
}

#endif // _DEBUG
