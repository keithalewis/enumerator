// end_.h - [begin, end) to enumerator
#pragma once

namespace enumerator {

	template<class I, class E>
	class end_ : public std::iterator<
		typename std::iterator_traits<E>::iterator_category,
		typename std::iterator_traits<E>::value_type,
		typename std::iterator_traits<E>::difference_type,
		typename std::iterator_traits<E>::pointer,
		typename std::iterator_traits<E>::reference>
	{
		I i;
		E e;
	public:
		using value_type = typename std::iterator_traits<E>::value_type;
		using reference = typename std::iterator_traits<E>::reference;

		end_(I i, E e)
			: i(i), e(e)
		{ }

		bool operator==(const end_& ie) const
		{
			return i == ie.i && e == ie.e;
		}
		bool operator!=(const end_& e) const
		{
			return !operator==(e);
		}

		operator bool() const
		{
			return i != e;
		}
		value_type operator*() const
		{
			return *i;
		}
		reference operator*()
		{
			return *i;
		}
		end_& operator++()
		{
			++i;

			return *this;
		}
		end_ operator++(int)
		{
			end_ _end(*this);

			operator++();

			return _end;
		}
	};
	template<class I, class E>
	inline auto end(I i, E e)
	{
		return end_<I,E>(i, e);
	}
	template<class C>
	inline auto end(C& c)
	{
		using I = typename C::iterator;

		return end_<I,I>(std::begin(c), std::end(c));
	}

} // enumerator

#ifdef _DEBUG
#include <cassert>
#include <vector>

inline void test_end_()
{
	std::vector<int> v = {1,2,3};
	{
		auto i = enumerator::end(v.begin(), v.end());
		auto i2(i);
		i = i2;
		assert (i == i2);
		assert (!(i != i2));
		assert (i);
		assert (*i == 1);
		assert (*++i == 2);
		assert (i);
		i++;
		assert (*i == 3);
		assert (i);
		assert (!++i);
	}
	{
		auto i = enumerator::end(v);
		auto i2(i);
		i = i2;
		assert (i == i2);
		assert (!(i != i2));
		assert (i);
		assert (*i == 1);
		assert (*++i == 2);
		assert (i);
		i++;
		assert (*i == 3);
		assert (i);
		assert (!++i);
	}
	{
		int s = 0;
		for (const auto& i : v) {
			s += i;
		}
		assert (s == 6);
	}
	{
		int s = 0;
		auto ev = enumerator::end(v);
		while (ev)
			s += *ev++;
		assert (s == 6);
	}
}
#endif // _DEBUG