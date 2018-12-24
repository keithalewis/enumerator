// zip_.h - interleave two enumerators
#pragma once
#include <type_traits>
#include <utility>
#include "enumerator_.h"

namespace fms {

	template<class E0, class E1,
		class I = typename std::common_type<E0::iterator_type,E1::iterator_type>::type,
		class C = typename std::common_type<E0::iterator_category,E1::iterator_category>::type,
		class T = typename std::common_type<E0::iterator_value,E1::iterator_value>::type>
	>
	class zip_ : public iterator<I,C,T> {
		std::pair<E0,E1> e;
	public:
		zip_()
		{ }
		// piecewise_construct???
		zip_(E0 e0, E1 e1)
			: e0 ? e(std::make_pair(e0,1)) : e(std::make_pair(e1,e0))
		{ }
		operator bool() const
		{
			return e.first;
		}
		T operator*() const
		{
			return *e.first;
		}
		zip_& operator++()
		{
			if (e.first)
				++e.first;
			if (e.second)
				e.swap();

			return *this;
		}
		zip_ operator++(int)
		{
			zip_ z(*this);

			operator++();

			return z;
		}
	};

} // fms

#ifdef _DEBUG
#include <cassert>

inline void test_zip_()
{
}

#endif // _DEBUG