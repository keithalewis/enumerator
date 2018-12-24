// pointer_.h - unsafe pointer enumerator
#pragma once
#include <iterator>

namespace enumerator {

	// Pointer to T often used in conjunction with null and counted enumerators.
	template<class T>
    class ptr_ : public iterator<T*> {
			T* p;
	public:
		ptr_(T* p)
			: p(p)
		{ }
		bool operator==(const ptr_& p_) const
		{
			return p == p_.p;
		}
		bool operator!=(const ptr_& p_) const
		{
			return !operator==(p_);
		}
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
			auto _ptr(*this);

			operator++();

			return _ptr;
		}
		ptr_& operator--()
		{
			--p;

			return *this;
		}
		ptr_ operator--(int)
		{
			auto _ptr(*this);

			operator--();

			return _ptr;
		}
		ptr_& operator+=(difference_type n)
		{
			p += n;

			return *this;
		}
		ptr_& operator-=(difference_type n)
		{
			return operator+=(-n);
		}
	};
	template<class T>
	inline auto ptr(T* p)
	{
		return ptr_<T>(p);
	}
}
template<class T>
inline auto operator+(const enumerator::ptr_<T>& p, typename enumerator::ptr_<T>::difference_type n)
{
	auto p_(p);

	p_.operator+=(n);

	return p_;
}
template<class T>
inline auto operator+(typename enumerator::ptr_<T>::difference_type n, const enumerator::ptr_<T>& p)
{
	return operator+(p, n);
}
template<class T>
inline auto operator-(const enumerator::ptr_<T>& p, typename enumerator::ptr_<T>::difference_type n)
{
	auto p_(p);

	p_.operator-=(n);

	return p_;
}

#ifdef _DEBUG
#include <cassert>

inline void test_ptr_()
{
	using namespace enumerator;

	int i[3] = {1,2,3};

	// construct, copy, assign
	auto p0 = ptr(i);
	auto p2(p0);
	p0 = p2;

	assert (p0);
	assert (p0 && p2);

	assert (p0 == p2);
	++p2;
	assert (p0 != p2);
	--p2;
	assert (p0 == p2);

	p2++;
	assert (p0 != p2);
	p2--;
	assert (p0 == p2);

	assert (p0);
	assert (*p0 == 1);
	assert (*++p0 == 2);
	p0++;
	assert (*p0 == 3);
	assert (p0);
	++p0;
	assert (p0);
	assert (!!p0);

	p0 = ptr(i);
	p2 = ptr(i);
	assert (p0 == p2);
	p0++;
	p2 += 1;
	assert (p0 == p2);
	p0 -= 1;
	--p2;
	assert (p0 == p2);

	auto p3 = p0 + 2;
	auto p4 = 2 + p0;
	assert (p3 == p4);

	p0 = p3 - 3;
	p2 = p3 + (-3);
	assert (p0 == p2);

	assert (p0 && p2);
}

#endif // _DEBUG
