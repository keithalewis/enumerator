// null_.h - null terminated enumerator
#pragma once
#include <iterator>

namespace enumerator {

	template<class E>
	class null_ : public std::iterator<
		typename std::iterator_traits<E>::iterator_category,
		typename std::iterator_traits<E>::value_type,
		typename std::iterator_traits<E>::difference_type,
		typename std::iterator_traits<E>::pointer,
		typename std::iterator_traits<E>::reference>
	{
		E e;
	public:
		using value_type = typename std::iterator_traits<E>::value_type;
		using reference = typename std::iterator_traits<E>::reference;

		null_(E e)
			: e(e)
		{ }

		bool operator==(const null_& n) const
		{
			return e == n.e;
		}
		bool operator!=(const null_& n) const
		{
			return !operator==(n);
		}

		operator bool() const
		{
			return *e != 0;
		}
		value_type operator*() const
		{
			return *e;
		}
		reference operator*()
		{	
			return *e;
		}
		null_& operator++()
		{
			++e;

			return *this;
		}
		null_ operator++(int)
		{
			auto _(*this);

			operator++();

			return _;
		}
	};
	template<class E>
	inline auto null(E e)
	{
		return null_<E>(e);
	}

} // enumerator

#ifdef _DEBUG
#include <cassert>

inline void test_null_()
{
	using enumerator::null;

	{
		char i[] = "foo";
		auto e = null(i);
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
		auto e = null("foo");
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