// counted_.h - counted enumerator
#pragma once

namespace enumerator {

	template<class I>
	class counted_ : public I {
		size_t n;
	public:
		counted_(const I& i, size_t n)
			: I(i), n(n)
		{ }
		bool operator==(const counted_& i) const
		{
			return n == i.n && I::operator==(i);
		}
		bool operator!=(const counted_& i) const
		{
			return !operator==(i);
		}
		operator bool() const
		{
			return n != 0;
		}
		counted_& operator++()
		{
			return --n, static_cast<counted_&>(I::operator++());
		}
		counted_ operator++(int)
		{
			return counted_(I::operator++(0), n--);
		}
	};
	template<class I>
	inline auto counted(const I& i, size_t n)
	{
		return counted_<I>(i, n);
	}

	template<class T, size_t N>
	inline auto array(T(&a)[N])
	{
		return counted(ptr_<T>(a), N);
	}
}

#ifdef _DEBUG
#include <cassert>

inline void test_counted_()
{
	using enumerator::counted;
	using enumerator::array;

	int i[] = {1,2,3};
	auto e = array(i);
	auto e2(e);
	e = e2;
	assert (e == e2);
	assert (!(e != e2));
	assert (e);
	assert (*e == 1);
	assert (*++e == 2);
	assert (e != e2);
	e++;
	assert (*e++ == 3);
	assert (!e);
}

#endif // _DEBUG