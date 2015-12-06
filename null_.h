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
			if (operator bool())
				I::operator++();

			return *this;
		}
		null_ operator++(int)
		{
			null_ _null(*this);

			operator++();

			return _null;
		}
	};
	template<class I>
	inline auto null(const I& i)
	{
		return null_<I>(i);
	}
	// shorthand
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
		assert (sizeof(i) == 4);
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
		assert (!e++);
		++e;
		e++;
		assert (!e);
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
		++e;
		e++;
		assert (!e);
	}
}

#endif // _DEBUG