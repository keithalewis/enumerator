// range_.h - begin/end iterators
#pragma once

namespace enumerator {

	// enumerator from STL range
	template<class I>
	class range_ : public iterator<I> {
		I b;
		I e;
	public:
		range_(const I& b, const I& e)
			: b(b), e(e)
		{ }
		operator bool() const
		{
			return b != e;
		}
		bool operator==(const range_<I>& r) const
		{
			return b == r.b && e == r.e;
		}
		bool operator!=(const range_<I>& r) const
		{
			return !operator==(r);
		}
		value_type operator*() const
		{
			return *b;
		}
		range_& operator++()
		{
			++b;

			return *this;
		}
		range_ operator++(int)
		{
			auto _range = range_(*this);

			operator++();

			return _range;
		}
		I begin() const
		{
			return b;
		}
		I end() const
		{
			return e;
		}
	};
	template<class I>
	inline auto range(const I& b, const I& e)
	{
		return range_<I>(b, e);
	}
	template<class C>
	inline auto range(const C& c)
	{
		return range(std::begin(c), std::end(c));
	}

} // enumerator

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
}

#endif // _DEBUG