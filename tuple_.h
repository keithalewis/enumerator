// tuple_.h - join iterators into a tuple
#pragma once
#include <iterator>
#include <tuple>
#include <type_traits>

namespace enumerator {

	template<class... I>
	class tuple_ : public std::iterator<
		std::common_type_t<std::iterator_traits<I>::category_type...>,
		std::tuple<I...>>
	{
		std::tuple<I...> i;
	public:
		tuple_(I... i)
			: i(i)
		{ }
	};

} // enumerator