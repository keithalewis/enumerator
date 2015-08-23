// apply_.h - apply a function to an enumerator
#pragma once
#include <type_traits>
#include <iterator>

namespace enumerator {

	template<class F, class E>
	class apply_ : public std::iterator<
		typename std::iterator_traits<E>::iterator_category,
		typename std::result_of_t<F(typename std::iterator_traits<E>::value_type)>,
		typename std::iterator_traits<E>::difference_type,
		typename std::iterator_traits<E>::pointer,
		typename std::iterator_traits<E>::reference>
	{
	protected:
		F f;
		E e;
	public:
		apply_(F f, E e)
			: e(e), f(f)
		{ }
		operator bool() const
		{
			return E::operator bool();
		}
		value_type operator*() const
		{
			return f(*e);
		}
		apply_& operator++()
		{
			++e;

			return *this;
		}
		apply_ operator++(int)
		{
			apply_ a(*this);

			++e;

			return a;
		}
	};

	template<class F, class E>
	inline auto apply(const F& f, E e)
	{
		return apply_<F,E>(f,e);
	}

} // enumerator

#ifdef _DEBUG
#include <cassert>
#include <vector>
#include "range_.h"

inline void test_apply_()
{
	std::vector<int> i {0,1,2};
	auto f = enumerator::apply([](int i) { return i*i; }, enumerator::range(i.begin(),i.end()));
	auto f2(f);
//	f = f2;
	assert (*f == 0);
	++f;
	assert (*f++ == 1);
	assert (*f == 4);
}

#endif // _DEBUG