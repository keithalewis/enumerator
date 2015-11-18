// pointer_.h - unsafe pointer enumerator
#pragma once
#include <iterator>

namespace enumerator {

	template<class T>
	struct ptr_ : public std::iterator<std::random_access_iterator_tag, T> {
		T* p;
	public:
		/*
		using iterator_category = typename std::iterator_traits<E>::iterator_category;
		using value_type = typename std::iterator_traits<E>::value_type;
		using difference_type = typename std::iterator_traits<E>::difference_type;
		using pointer = typename std::iterator_traits<E>::pointer;
		using reference = typename std::iterator_traits<E>::reference;
		*/
		ptr_(T* p)
			: p(p)
		{ }
		operator bool() const
		{
			return true;
		}
		T operator*() const
		{
			return *p;
		}
		T& operator*()
		{
			return *p;
		}
		ptr_& operator++()
		{
			++p;

			return *this;
		}
		ptr_ operator++(int)
		{
			ptr_ _ptr(*this);

			operator++();

			return _ptr;
		}
		// op--, etc
	};
	template<class T>
	inline auto ptr(T* t)
	{
		return ptr_<T>(t);
	}
};

#ifdef _DEBUG
#include <cassert>
#include "copy.h"
#include "counted_.h"
#include "iota_.h"

inline void test_ptr_()
{
	using namespace enumerator;

	int i[3];
	auto pi = ptr(i);
	auto pi2(pi);
	pi = pi2;
	copy(counted(iota(), 3), i);
	assert (pi);
	assert (*pi == 0);
	assert (*++pi == 1);
	pi++;
	assert (*pi == 2);

	pi = ptr(i);
	copy(counted(iota(), 3), pi);
	assert (pi);
	assert (*pi == 0);
	assert (*++pi == 1);
	pi++;
	assert (*pi == 2);
}

#endif // _DEBUG
