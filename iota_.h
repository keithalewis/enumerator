// iota_.h - 0, 1, ...
#pragma once
#include "enumerator_.h"

namespace fms {

	template<class T>
	class iota_ : public enumerator_<void,T,std::input_iterator_tag,ptrdiff_t,T*,T&> {
		T t;
	protected:
	public:
		iota_(const T& t = 0)
			: t(t)
		{ }

		operator bool() const
		{
			return true;
		}
		// forward iterator
		const T& operator*() const
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

	template<class T>
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
		auto i = fms::iota<int>();
		size_t n;
		n = sizeof(i);
		n = sizeof(int);
		assert (*i == 0);
		assert (*++i == 1);
	}
}

#endif // _DEBUG