// until.h - move enumerator forward until condition is true
#pragma once

namespace fms {

template<class P, class E>
inline E until(const P& p, E e)
{
	while (e && !p(e))
		++e;

	return e;
}

} // namespace fms

#ifdef _DEBUG
#include <cassert>
#include "enumerator_.h"

inline void test_until()
{
	int i[] = {0,1,2};
	auto e = fms::enumerator(i);
	e = until([](auto e) { return *e == 1; }, e);
	assert (*e == 1);
}

#endif // _DEBUG