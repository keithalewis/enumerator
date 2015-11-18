// counted_.h - counted enumerator
#pragma once

namespace enumerator {

	template<class E>
	class counted_ : public std::iterator<
		typename std::iterator_traits<E>::iterator_category,
		typename std::iterator_traits<E>::value_type,
		typename std::iterator_traits<E>::difference_type,
		typename std::iterator_traits<E>::pointer,
		typename std::iterator_traits<E>::reference>
	{
		E e;
		size_t n;
	public:
		using value_type = typename std::iterator_traits<E>::value_type;
		using reference = typename std::iterator_traits<E>::reference;

		counted_(E e, size_t n = 0)
			: e(e), n(n)
		{ }

		bool operator==(const counted_& c) const
		{
			return n == c.n && e == c.e;
		}
		bool operator!=(const counted_& c) const
		{
			return !operator==(c);
		}

		operator bool() const
		{
			return n != 0;
		}
		value_type operator*() const
		{
			return *e;
		}
		reference operator*()
		{
			return *e;
		}
		counted_& operator++()
		{
			++e;
			--n;

			return *this;
		}
		counted_ operator++(int)
		{
			counted_ _counted(*this);

			operator++();

			return _counted;
		}
		// enable_if op--, op+=, ...

	};
	template<class E>
	inline auto counted(E e, size_t n)
	{
		return counted_<E>(e, n);
	}
}

#ifdef _DEBUG
#include <cassert>

inline void test_counted_()
{
	using enumerator::counted;

	auto i = counted("abc", 2);
	auto i2(i);
	i = i2;
	assert (i == i2);
	assert (!(i != i2));
	assert (i);
	assert (*i == 'a');
	assert (*++i == 'b');
	i++;
	assert (!i);
}

#endif // _DEBUG