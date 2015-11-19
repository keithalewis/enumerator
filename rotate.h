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
			std::swap(*b++, *n++);
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
#include "copy.h"
#include "counted_.h"
#include "iota_.h"
#include "null_.h"

inline void test_rotate()
{
	using namespace enumerator;

	char s[6], t[6];
	for (int i = 1; i < 6; ++i) {
		for (int j = 0; j < i; ++j) {
			copy(counted(iota('a'), i), s);
			copy(counted(iota('a'), i), t);

			rotate(counted(s, i), counted(s + j, i - j));
			std::rotate(t, t + j, t + i);

			assert (std::equal(s, s + 5, t));
		}
	}
}

#endif // _DEBUG
