// until.h - move enumerator forward until condition is true
#pragma once

namespace enumerator {

	template<class P, class E>
	class until_ : public std::iterator<
		typename std::iterator_traits<E>::iterator_category,
		typename std::iterator_traits<E>::value_type,
		typename std::iterator_traits<E>::difference_type,
		typename std::iterator_traits<E>::pointer,
		typename std::iterator_traits<E>::reference>
	{
		P p;
		E e;
	public:
		until_(P p, E e)
			: p(p), e(e)
		{ }
		operator bool() const
		{
			return !p(e);
		}
		value_type operator*() const
		{
			return *e;
		}
		reference operator*()
		{
			return *e;
		}
		until_& operator++()
		{
			++e;

			return *this;
		}
		until_ operator++(int)
		{
			auto _(*this);

			operator++();

			return _;
		}
	};
	template<class P, class E>
	inline auto until(P p, E e)
	{
		return until_<P,E>(p, e);
	}

} // namespace fms

#ifdef _DEBUG
#include <cassert>

inline void test_until_()
{
	using enumerator::until;

	int i[] = {0,1,2};
	auto f = [](auto e) { return *e > 1; };
	auto fi = until(f, i);
	auto fi2(fi);
	// auto fi = f2;
	assert (fi);
	assert (*fi == 0);
	fi++;
	assert (*fi == 1);
	assert (!++fi);
}

#endif // _DEBUG