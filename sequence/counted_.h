// counted_.h - counted enumerator
#pragma once

namespace enumerator {

	template<class I>
	class counted_ : public I {
		typename I::difference_type n;
	public:
		counted_(typename I::difference_type n, const I& i)
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
			if (n) {
				--n;
				I::operator++();
			}

			return static_cast<counted_&>(*this);
		}
		counted_ operator++(int)
		{
			counted_ _counted(*this);

			operator++();

			return _counted;
		}
		counted_& operator+=(typename I::difference_type n_)
		{
			if (n) { // once done, always done
				if (n - n_ >= 0) {
					n -= n_;
					I::operator+=(n_);
				}
				else {
					n = 0;
					I::operator+=(-n);
				}
			}

			return *this;
		}
		counted_& operator-=(typename I::difference_type n_)
		{
			return operator+=(-n_);
		}
	};
	template<class I>
	inline auto counted(size_t n, const I& i)
	{
		return counted_<I>(n, i);
	}
	template<class T, size_t N>
	inline auto counted(T(&a)[N])
	{
		return counted(N, ptr_<T>(a));
	}
	// alternate name
	template<class T, size_t N>
	inline auto array(T(&a)[N])
	{
		return counted(a);
	}
}
template<class T>
inline auto operator+(const enumerator::counted_<T>& p, typename enumerator::counted_<T>::difference_type n)
{
	return enumerator::counted_<T>(p).operator+=(n);
}
template<class T>
inline auto operator+(typename enumerator::counted_<T>::difference_type n, const enumerator::counted_<T>& p)
{
	return operator+(p, n);
}
template<class T>
inline auto operator-(const enumerator::counted_<T>& p, typename enumerator::counted_<T>::difference_type n)
{
	return enumerator::counted_<T>(p).operator-=(n);
}

#ifdef _DEBUG
#include <cassert>
#include "ptr_.h"

inline void test_counted_()
{
	using enumerator::ptr;
	using enumerator::counted;
	using enumerator::array;

	{
		char foo[] = "foo";
		auto e = array(foo);
		auto e2(e);
		e = e2;
		assert (e == e2);
		assert (!(e != e2));

		assert (*e == foo[0]);
		e++;
		assert (*e == foo[1]);
		assert (*++e == foo[2]);
		assert (*++e == 0);
		assert (e);
		assert (!++e);
	}
	{
		char foo[] = "foo";
		auto e = counted(4, ptr(foo));
		auto e2(e);
		e = e2;
		assert (e == e2);
		assert (!(e != e2));

		assert (*e == foo[0]);
		e++;
		assert (*e == foo[1]);
		assert (*++e == foo[2]);
		assert (*++e == 0);
		assert (e);
		assert (!++e);
	}
	{
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
	{
		int i[] = {1,2,3};
		auto e = array(i);
		e += 1;
		assert (*e == 2);
		e -= 1;
		assert (*e == 1);
		e = e + 2;
		assert (*e == 3);
		e = e - 1;
		assert (*e == 2);
		e += 10;
		assert (!e);
		e += -100;
		assert (!e);
		e -= 1000;
		assert (!e);
	}
}

#endif // _DEBUG