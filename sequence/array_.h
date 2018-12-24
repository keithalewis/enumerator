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
		bool operator==(const array_& a) const
		{
			return i == a.i && n == a.n;
		}
		bool operator!=(const array_& a) const
		{
			return !operator==();
		}
		operator bool() const
		{
			return n != 0;
		}
		array_& operator++()
		{
			if (n != 0) {
				++i;
				--n;
			}

			return *this;
		}
		array_ operator++(int)
		{
			array_ a(*this);

			operator++();

			return *this;
		}
		array_& operator--()
		{
			--i;
			++n;

			return *this;
		}
		array_ operator--(int)
		{
			array_ a(*this);

			operator--();

			return *this;
		}
		array_& operator+=(pointer_difference m)
		{
			i += m;
			n -= m;

			return *this;
		}
		array_& operator-=(pointer_difference m)
		{
			i -= m;
			n += m;

			return *this;
		}
	};

} // enumerator
