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
		// etc...
	};
	template<class T>
	inline auto constant(const T& t)
	{
		return constant_<T>(t);
	}
	template<class T>
	inline auto c(const T& t)
	{
		return constant(t);
	}

} // namespace enumerator

#ifdef _DEBUG
#include <cassert>

inline void test_constant_()
{
	using namespace enumerator;

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
}

#endif // _DEBUG