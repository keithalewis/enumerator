// range_.h - begin/end iterators
#pragma once

namespace enumerator {

	// enumerator from STL range
	template<class I>
	class range_ : public I {
		I e;
	public:
		range_(const I& b, const I& e)
			: I(b), e(e)
		{ }

		I& begin()
		{
			using namespace std;

			return *this;
		}
		I& end()
		{
			return e;
		}
		const I& begin() const
		{
			return *this;
		}
		const I& end() const
		{
			return e;
		}
		operator bool() const
		{
			return I::operator!=(e);
		}
		bool operator==(const range_<I>& r) const
		{
			return I::operator==(r) && e == r.e;
		}
		bool operator!=(const range_<I>& r) const
		{
			return !operator==(r);
		}
		range_& operator++()
		{
			if (operator bool())
				I::operator++();

			return *this;
		}
		range_ operator++(int)
		{
			range_ _range(*this);

			I::operator++();

			return _range;
		}
		range_& operator+=(typename I::difference_type n)
		{
			I::operator+=(n);

			return *this;
		}
		range_& operator-=(typename I::difference_type n)
		{
			I::operator-=(n);

			return *this;
		}
	};
	template<class I>
	inline auto range(const I& b, const I& e)
	{
		return range_<I>(b, e);
	}
	template<class C>
	inline auto range(/*const*/ C& c)
	{
		return range(std::begin(c), std::end(c));
	}

} // enumerator

template<class I>
inline auto operator+(const enumerator::range_<I>& e, typename enumerator::range_<I>::difference_type n)
{
	return enumerator::range_<I>(e) += n;
}
template<class I>
inline auto operator+(typename enumerator::range_<I>::difference_type n, const enumerator::range_<I>& e)
{
	return e + n;
}
template<class I>
inline auto operator-(const enumerator::range_<I>& e, typename enumerator::range_<I>::difference_type n)
{
	return enumerator::range_<I>(e) -= n;
}
#ifdef _DEBUG
#include <cassert>
#include <vector>

inline void test_range_()
{
	using namespace enumerator;
	{
		std::vector<int> v{0,1,2};
		auto r = range(v.begin(), v.end());
		auto r2(r);
		r = r2;

		assert (r == r2);

		assert (*r == 0);
		++r;
		assert (r != r2);
		assert (*r == 1);
		r++;
		assert (*r == 2);
		assert (r);
		++r;
		assert (!r);
//		--r;
//		assert (r);
	}
	{
		std::vector<int> v{0,1,2};
		auto r = range(v.begin(), v.end());

		int s{0};
		for (auto t : r) {
			s += t;
		}
		assert (s == 3);
		s = 0;
		for (const auto& t : r) {
			s += t;
		}
		assert (s == 3);
	}
	{
		std::vector<int> v{0,1,2};
		auto r = range(v);

		int s{0};
		for (auto t : r) {
			s += t;
		}
		assert (s == 3);
		s = 0;
		for (const auto& t : r) {
			s += t;
		}
		assert (s == 3);
	}
	{
		std::vector<int> v{0,1,2};
		auto r = range(v);
		assert (r.begin() == v.begin());
		assert (r.end() == v.end());
		r += 2;
		assert (r.begin() == v.begin() + 2);
		assert (r.end() == v.end());
		r = r + 1;
		assert (r.begin() == v.end());
	}
}

#endif // _DEBUG