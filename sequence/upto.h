// upto.h - move enumerator up to a value
#pragma once
#include "until.h"

namespace fms {

	template<class E, class T = std::iterator_traits<E>::value_type>
	inline E upto(const T& t, E e)
	{
		return until([&t](E e) { return *e >= t; }, e);
	}

} // fms

#ifdef _DEBUG
#include <cassert>
#include "enumerator_.h"

inline void test_upto()
{
	int i[] = {0,1,2};
	auto e = fms::enumerator(i);
	e = fms::upto(1, e);
	assert (*e == 1);
}

#endif // _DEBUG

