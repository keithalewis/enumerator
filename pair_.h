// pair_.h - pair of enumerators
#pragma once
#include "enumerator_.h"

namespace fms {

	template<class I0, class I1,
	class C = typename std::common_type<I0::iterator_category,I1::iterator_category>::type,
	class T0 = typename I0::value_type,
	class T1 = typename I1::value_type,
	class D = typename ptrdiff_t,
	class P = typename std::pair<I0,I1>*, 
	class R = typename std::pair<I0,I1>&
	>
	struct pair_ : public enumerator_<std::pair<I0,I1>,C,std::pair<T0,T1>,D,P,R> {
		using enumerator_<std::pair<I0,I1>,C,std::pair<T0,T1>,D,P,R>::i;
		pair_()
		{ }
		pair_(I0 i0, I1 i1)
			: enumerator_<std::pair<I0,I1>,C,std::pair<T0,T1>,D,P,R>(std::make_pair(i0,i1))
		{ }
		operator bool() const
		{
			return i.first || i.second;
		}
		std::pair<T0,T1> operator*() const
		{
			return std::make_pair(*i.first, *i.second);
		}
		pair_& operator++()
		{
			++i.first;
			++i.second;

			return *this;
		}
		pair_ operator++(int)
		{
			pair_ p(*this);

			operator++();

			return p;
		}
	};

	template<class I0, class I1,
	class C = typename std::common_type<I0::iterator_category,I1::iterator_category>::type,
	class T0 = typename I0::value_type,
	class T1 = typename I1::value_type,
	class D = typename ptrdiff_t,
	class P = typename std::pair<I0,I1>*, 
	class R = typename std::pair<I0,I1>&
	>
		inline auto pair(I0 i0, I1 i1)
	{
		return pair_<I0,I1,C,T0,T1,D,P,R>(i0, i1);
	}
} // fms

#ifdef _DEBUG
#include <cassert>

inline void test_pair_()
{
	int i0[] = {0,1,2};
	int i1[] = {3,4,5};
	auto p = fms::pair(fms::enumerator(i0),fms::enumerator(i1));
}

#endif // _DEBUG
