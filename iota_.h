// iota_.h - 0, 1, ...
#pragma once
#include <iterator>

namespace enumerator {

	template<class T>
	class iota_ : public std::iterator<std::forward_iterator_tag, T> {
		T t;
	protected:
	public:
//		using value_type = typename std::iterator_traits<E>::value_type;
//		using reference = typename std::iterator_traits<E>::reference;

		iota_(const T& t = 0)
			: t(t)
		{ }

		operator bool() const
		{
			return true;
		}
		// forward iterator
		T operator*() const
		{
			return t;
		}
		T& operator*()
		{
			return t;
		}
		iota_& operator++()
		{
			++t;

			return *this;
		}
		iota_ operator++(int)
		{
			iota_ t_(*this);

			operator++();

			return t_;
		}
	};

	template<class T = int>
	inline auto iota(const T& t = 0)
	{
		return iota_<T>(t);
	}

} // namespace fms

#ifdef _DEBUG
#include <cassert>

inline void test_iota_()
{
	{
		using enumerator::iota;

		auto i = iota();
		size_t n, ni;
		n = sizeof(i);
		ni = sizeof(int);
		assert (n == ni);
		assert (*i == 0);
		assert (*++i == 1);
	}
}

#endif // _DEBUG