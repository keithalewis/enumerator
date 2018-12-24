// past.h - move enumerator past a value
#pragma once
#include "until.h"

namespace fms {

	template<class E, class T = std::iterator_traits<E>::value_type>
	inline E past(const T& t, E e)
	{
		return until([&t](auto e) { return *e > t; }, e);
	}

} // fms

#ifdef _DEBUG
#include <cassert>
#include "enumerator_.h"

inline void test_past()
{
	int i[] = {0,1,2};
	auto e = fms::enumerator(i);
	e = fms::past(1, e);
	assert (*e == 2);
}

#endif // _DEBUG
