// range_.h - begin/end iterators
#pragma once

namespace enumerator {

	template<class I>
	class range_ : public I {
		I e;
	public:
		using I::I;
		range_()
		{ }
		range_(I i, I e)
			: I(i), e(e)
		{ }
		template<class C>
		range_(C&& c)
			: range_(std::begin(c), std::end(c))
		{ }
		I begin() const
		{
			return *this;
		}
		I end() const
		{
			return e;
		}
		operator bool() const
		{
			return *this != e;
		}
	};
	template<class I>
	inline auto range(I b, I e)
	{
		return range_<I>(b, e);
	}
	template<class C>
	inline auto range(C& c)
	{
		return range_<C::iterator>(c);
	}

} // enumerator

#ifdef _DEBUG
#include <cassert>
#include <vector>

inline void test_range_()
{
	{
		std::vector<int> v{0,1,2};
		auto r = enumerator::range(v.begin(), v.end());
		auto r2(r);
		r = r2;
		assert (*r == 0);
		++r;
		assert (*r == 1);
		r++;
		assert (*r == 2);
		assert (r);
		++r;
		assert (!r);
		--r;
		assert (r);
	}
	{
		std::vector<int> v{0,1,2};
		auto r = enumerator::range(v.begin(), v.end());

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
		auto r = enumerator::range(v);

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