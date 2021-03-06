// tuple_.h - join iterators into a tuple
#pragma once
#include <iterator>
#include <tuple>
#include <type_traits>

namespace enumerator {

	template<class... I>
	class tuple_ 
	{
		std::tuple<I...> i;
	public:
		tuple_(I... i)
			: i(std::make_tuple(i...))
		{ }
		operator bool() const
		{
			return true;
		}
		tuple_& operator++()
		{
			return *this;
		}
	};
	/*
	template<class I...>
	inline auto tuple(I... i)
	{
		return tuple_<I...>(i);
	}
	*/

} // enumerator
#ifdef _DEBUG
#include <cassert>

inline void test_tuple_()
{
	using namespace enumerator;

	int i[3] = {0,1,2};
	char c[5] = "abcd";
///	auto t = tuple(
}

#endif // _DEBUG