// skip.h - functional std::advance
#pragma once
#include <algorithm>
#include <iterator>
#include "enumerator_.h"

namespace fms {

	template<class I, class D = typename std::iterator_traits<I>::difference_type>
	inline I skip(D n, I i)
	{
		std::advance(i, n);

		return i;
	}
	
	template<class I, 
		class C = typename std::iterator_traits<I>::iterator_category,
		class T = typename std::iterator_traits<I>::value_type,
		class D = typename std::iterator_traits<I>::difference_type,
		class P = typename std::iterator_traits<I>::pointer, 
		class R = typename std::iterator_traits<I>::reference> 
	inline enumerator_<I,C,T,D,P,R> skip(D n, enumerator_<I,C,T,D,P,R> e)
	{
		return skip(n, e.iterator());
	}


} // namespace fms

#ifdef _DEBUG
#include <cassert>

inline void test_skip()
{/*
	using fms::enumerator;
	using fms::skip;

	{
		int i[] = {0,1,2};
		auto j = skip(2, i);
		assert (*j == 2);
		j = skip(-1,j);
		assert (*j == 1);
	}
	{
		int i[] = {0,1,2};
		auto e = enumerator(i);
		assert (*e == 0);
		e = skip(2,e);
		assert (*e == 2);
		e = skip(-1,e);
		assert (*e == 1);
	}*/
}

#endif // _DEBUG