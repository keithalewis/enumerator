// array_.h - counted enumerator from array
#pragma once
#include <iterator>

namespace enumerator {

	template<class T, size_t N>
	class array_ : public std::iterator<std::bidirectional_iterator_tag, T> {
		T* i;
		size_t n;
	public:
		array_()
			: i(nullptr), n(0)
		{ }
		array_(T(&i)[N])
			: i(i), n(N)
		{ }
		operator bool() const
		{
			return n != 0;
		}
	};

} // enumerator
