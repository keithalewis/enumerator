// apply_.h - apply a function to an enumerator
#pragma once
#include <type_traits>

namespace fms {

	template<class F, class E,
		class I = typename E::iterator_type,
		class C = typename E::iterator_category,
		class U = typename std::result_of<F(typename E::value_type)>::type
	>
	class apply_ : public enumerator_<I,C,U> {
	protected:
		F f;
	public:
		apply_(F f, E e)
			: enumerator_<I,C,U>(e), f(f)
		{ }

		U operator*() const
		{
			return f(enumerator_<I,C,U>::operator*());
		}
	};

	template<class F, class E>
	inline auto apply(const F& f, E e)
	{
		return apply_<F,E>(f,e);
	}

} // fms

#ifdef _DEBUG
#include <cassert>
#include "enumerator_.h"

inline void test_apply_()
{
	int i[] = {0,1,2};
	auto e = fms::enumerator(i);
	auto f = apply([](int i) { return i*i; }, e);
	assert (*f == 0);
	++f;
	assert (*f++ == 1);
	assert (*f == 4);
}

#endif // _DEBUG