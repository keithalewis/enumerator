// constant_.h - constant enumerator
#pragma once
#include <iterator>

namespace enumerator {

	template<class T>
	class constant_ : public std::iterator<std::random_access_iterator_tag, T> {
		T t;
	public:
		constant_(const T& t = 0)
			: t(t)
		{ }
		bool operator==(const constant_& t_) const
		{
			return t == t_.t;
		}
		bool operator!=(const constant_& t_) const
		{
			return !operator==(t_);
		}
		operator bool() const
		{
			return true;
		}
		T operator*() const
		{
			return t;
		}
		T& operator*()
		{
			return t;
		}
		constant_& operator++()
		{
			return *this;
		}
		constant_ operator++(int)
		{
			return constant_(*this);
		}
		constant_& operator+=(difference_type n)
		{
			n = n;
			return *this;
		}
		constant_& operator-=(difference_type n)
		{
			n = n;
			return *this;
		}
	};
	template<class T>
	inline auto constant(const T& t)
	{
		return constant_<T>(t);
	}
	// shorthand
	template<class T>
	inline auto c(const T& t)
	{
		return constant(t);
	}

} // namespace enumerator
template<class T>
inline auto operator+(const enumerator::constant_<T>& e, typename enumerator::constant_<T>::difference_type n)
{
	n = n;
	return enumerator::constant_<T>(e);
}
template<class T>
inline auto operator+(typename enumerator::constant_<T>::difference_type n, const enumerator::constant_<T>& e)
{
	n = n;
	return enumerator::constant_<T>(e);
}
template<class T>
inline auto operator-(const enumerator::constant_<T>& e, typename enumerator::constant_<T>::difference_type n)
{
	n = n;
	return enumerator::constant_<T>(e);
}

#ifdef _DEBUG
#include <cassert>

inline void test_constant_()
{
	using namespace enumerator;

	{
		auto i = c(1);
		auto i2(i);
		i = i2;
		assert (i == i2);
		assert (*i == 1);
		++i;
		assert (*i == 1);
		i++;
		assert (*i == 1);
		*i = 2;
		assert (*i == 2);

		i += 10;
		assert (*i == 2);
		i -= 10;
		assert (*i == 2);
		i = 10 + i;
		assert (*i == 2);
		i = i - 10;
		assert (*i == 2);

		assert (i == i);
		assert (!(i != i));

	}
}

#endif // _DEBUG