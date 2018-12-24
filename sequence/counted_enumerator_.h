// counted_enumerator_.h - enumerators with a size_t count
#pragma once
#include "enumerator_.h"

namespace fms {

	template<class I, 
		class C = typename std::iterator_traits<I>::iterator_category,
		class T = typename std::iterator_traits<I>::value_type,
		class D = typename std::iterator_traits<I>::difference_type,
		class P = typename std::iterator_traits<I>::pointer, 
		class R = typename std::iterator_traits<I>::reference> 
	class counted_enumerator_ : public fms::enumerator_<I,C,T,D,P,R> {
		size_t n;
	protected:
		using fms::enumerator_<I,C,T,D,P,R>::enumerator_::i;
	public:
		counted_enumerator_(const I& i, size_t n)
			: enumerator_<I,C,T,D,P,R>(i), n(n)
		{ }

		size_t size() const
		{
			return n;
		}
		I end() const
		{
			I e(i);

			std::advance(e, n);

			return e;
		}

		operator bool() const
		{
			return n != 0;
		}
		counted_enumerator_& operator++()
		{
			if (n) {
				++i;
				--n;
			}

			return *this;
		}
		counted_enumerator_ operator++(int)
		{
			counted_enumerator_ i_(*this);

			operator++();

			return i_;
		}
	};

	template<class I, 
		class C = typename std::iterator_traits<I>::iterator_category,
		class T = typename std::iterator_traits<I>::value_type,
		class D = typename std::iterator_traits<I>::difference_type,
		class P = typename std::iterator_traits<I>::pointer, 
		class R = typename std::iterator_traits<I>::reference> 
	inline counted_enumerator_<I,C,T,D,P,R> counted_enumerator(const I& i, size_t n)
	{
		return counted_enumerator_<I,C,T,D,P,R>(i, n);
	}

	// construct from array
	template<class T, size_t N>
	inline counted_enumerator_<T*> counted_enumerator(T(&a)[N])
	{
		return counted_enumerator_<T*>(a, N);
	}

} // namespace fms

#ifdef _DEBUG

#include <cassert>

inline void test_counted_enumerator()
{
	{
		int i[] = {0,1,2};
		auto e = fms::counted_enumerator(i);
		auto e2(e);
		e = e2;

		assert (e.size() == 3);
		assert (e);
		assert (*e == 0);
		assert (*++e == 1);
		assert (e.size() == 2);
		assert (*e++ == 1);
		assert (e.size() == 1);
		assert (*e == 2);
		assert (e);
		assert (e++);
		assert (!e);
		assert (!++e);
		assert (e.size() == 0);
	}
	{
		int i[] = {0,1,2};
		auto e = fms::counted_enumerator(i);
		int s{0};
		for (const auto& ei: e)
			s += ei;
		assert (s == 3);
	}
}

#endif