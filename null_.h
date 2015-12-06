// null_.h - null terminated enumerator
#pragma once
#include <iterator>

namespace enumerator {

	template<class I>
	struct null_ : public I {
		null_(const I& i)
			: I(i)
		{ }
		// operator==() ???
		operator bool() const
		{
			return I::operator*() != 0;
		}
		null_& operator++()
		{
			return static_cast<null_&>(I::operator++());
		}
		null_ operator++(int)
		{
			return null_(I::operator++(0));
		}
	};
	template<class I>
	inline auto null(const I& i)
	{
		return null_<I>(i);
	}
	template<class I>
	inline auto n(const I& i)
	{
		return null(i);
	}

} // enumerator

#ifdef _DEBUG
#include <cassert>
#include "ptr_.h"

inline void test_null_()
{
	using namespace enumerator;

	{
		char i[] = "foo";
		auto e = null(ptr(i));
		auto e2(e);
		e = e2;
		assert (e);
		assert (*e == i[0]);
		e++;
		assert (e);
		assert (*e == i[1]);
		assert (*++e == i[2]);
		assert (!++e);
	}
	{
		auto e = null(ptr("foo"));
		auto e2(e);
		e = e2;
		assert (e);
		assert (*e == 'f');
		e++;
		assert (e);
		assert (*e == 'o');
		assert (*++e == 'o');
		assert (!++e);
	}
}

#endif // _DEBUG