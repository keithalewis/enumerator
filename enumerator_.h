// enumerator.h - iteratators with operator bool() const returning false when done
#pragma once
#include <iterator>
#include <type_traits>

namespace fms {

	template<class I, 
		class C = typename std::iterator_traits<I>::iterator_category,
		class T = typename std::iterator_traits<I>::value_type,
		class D = typename std::iterator_traits<I>::difference_type,
		class P = typename std::iterator_traits<I>::pointer, 
		class R = typename std::iterator_traits<I>::reference> 
	class enumerator_ : public std::iterator<C,T,D,P,R> {
	protected:
		I i;
	public:
		typedef typename I iterator_type;
//		typedef typename T value_type;

		enumerator_()
		{ }
		enumerator_(const I& i)
			: i(i)
		{ }

		// underlying iterator
		I& iterator()
		{
			return i;
		}
		// copy of i
		I begin() const
		{
			return i;
		}
		// no end

		bool operator==(const enumerator_& j) const
		{
			return i == j.i;
		}
		bool operator!=(const enumerator_& j) const
		{
			return !operator==(j);
		}

		explicit operator bool() const
		{
			return true;
		}
		T operator*() const
		{
			return *i;
		}
/*		const T& operator*() const
		{
			return *i;
		}
		T& operator*()
		{
			return *i;
		}
	*/	enumerator_& operator++() {
			++i;

			return *this;
		}
		enumerator_ operator++(int) {
			enumerator_ i_(*this);
	
			operator++();

			return i_;
		}
		// enable_if for all iterator types???
	};

	// empty iterator
	template<class T> 
	struct enumerator_<void,T,std::input_iterator_tag,ptrdiff_t,T*,T&> 
		: public std::iterator<std::input_iterator_tag,T,ptrdiff_t,T*,T&> { 
		typedef typename void iterator_type;
		typedef typename T value_type;
	}; 

	// make an enumerator
	template<class I, 
		class C = typename std::iterator_traits<I>::iterator_category,
		class T = typename std::iterator_traits<I>::value_type,
		class D = typename std::iterator_traits<I>::difference_type,
		class P = typename std::iterator_traits<I>::pointer, 
		class R = typename std::iterator_traits<I>::reference> 
	inline enumerator_<I,C,T,D,P,R> enumerator(const I& i)
	{
		return enumerator_<I,C,T,D,P,R>(i);
	}

	// from a pointer
	template<class T>
	inline enumerator_<T*> enumerator(T* i)
	{
		return enumerator_<T*>(i);
	}

} // namespace fms

#ifdef _DEBUG
#include <cassert>
#include <type_traits>
#include <vector>

inline void test_enumerator_()
{
	using std::vector;
	using fms::enumerator;

	{
		vector<int> i{0,1,2};
		auto e = enumerator(i.begin());
		auto e2 = e;
		e = e2;
		assert (e == e2);

		using I = decltype(e);
		static_assert (std::is_constructible<I>::value, "");
		static_assert (std::is_copy_assignable<I>::value, "");
		static_assert (std::is_copy_constructible<I>::value, "");
		static_assert (std::is_destructible<I>::value, "");
		static_assert (std::is_default_constructible<I>::value, "");
		static_assert (std::is_move_assignable<I>::value, "");
		static_assert (std::is_move_constructible<I>::value, "");

		assert (e);
		assert (*e == 0);
		assert (*++e == 1);
		assert (e);
		assert (e != e2);
		assert (*e++ == 1);
		assert (e);
		assert (*e == 2);
		assert (e);

		auto& ie = e.iterator();
		--ie;
		assert (*e == 1);
	}
	{
		int i[] = {0,1,2};
		auto e = enumerator(i);
		auto e2(e);
		e = e2;

		assert (e);
		assert (*e == 0);
		assert (*++e == 1);
		assert (e);
		assert (e != e2);
		assert (*e++ == 1);
		assert (e);
		assert (*e == 2);
		assert (e);
		++e++;
		assert (e); // out of range
	}
}

#endif