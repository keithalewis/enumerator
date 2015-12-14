// copy.h - copy one enumerator to another
#pragma once

namespace enumerator {

	template<class I, class J>
	inline void copy(I i, J j)
	{
		while (i && j)
			*j++ = *i++;
	}

} // enumerator

#ifdef _DEBUG
#include <cassert>
#include <cstring>
#include <vector>
#include "null_.h"
#include "ptr_.h"

inline void test_copy()
{
	using enumerator::copy;
	using enumerator::null;
	using enumerator::ptr;

	char bar[3];
	copy(null(ptr("foo")), bar);
	assert (0 == strncmp("foo", bar, 3));
}

#endif // _DEBUG
