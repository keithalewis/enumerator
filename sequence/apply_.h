// apply_.h - apply a function to an enumerator
#pragma once
#include <type_traits>
#include <iterator>

namespace enumerator {

	template<class F, class E>
	class apply_ : public std::iterator<
		typename std::input_iterator_tag,
		typename std::result_of_t<F(typename std::iterator_traits<E>::value_type)>,
		typename std::iterator_traits<E>::difference_type,
		typename std::iterator_traits<E>::pointer,
		typename std::iterator_traits<E>::reference>
	{
	protected:
		F f;
		E e;
	public:
		using iterator_category = typename std::iterator_traits<E>::iterator_category;
		using value_type = std::result_of_t<F(typename std::iterator_traits<E>::value_type)>;
		using difference_type = typename std::iterator_traits<E>::difference_type;
		using pointer = typename std::iterator_traits<E>::pointer;
		using reference = typename std::iterator_traits<E>::reference;

		apply_(F f, E e)
			: f(f), e(e)
		{ }

		bool operator==(const apply_&) const
		{
			return false;
		}
		bool operator!=(const apply_&) const
		{
			return true;
		}

		operator bool() const
		{
			return e;//.operator bool();
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
			apply_ _apply(*this);

			++e;

			return _apply;
		}
	};

	template<class F, class E>
	inline auto apply(F f, E e)
	{
		return apply_<F,E>(f,e);
	}

} // enumerator

#ifdef _DEBUG
#include <cassert>
#include <cmath>
#include "ptr_.h"

inline void test_apply_()
{
	using namespace enumerator;

	int i[] = {0,1,2};
	auto f = [](int i) { return sqrt(i); };
	auto fi = apply(f, ptr(i));
//	auto fi2(fi);
//	fi = fi2;
	assert (fi);
	assert (*fi == 0);
	++fi;
	assert (*fi++ == 1);
	assert (*fi == sqrt(2));
}

#endif // _DEBUG