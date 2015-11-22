// e.h - enumerators
#pragma once
#include <iterator>

namespace e {

#define ITERATOR(I) std::iterator< \
	typename std::iterator_traits<I>::iterator_category, \
	typename std::iterator_traits<I>::value_type>

	template<class T>
	class ptr_ : public std::iterator<std::random_access_iterator_tag, T> {
		T* p;
	public:
		ptr_(T* p)
			: p(p)
		{ }
		bool operator==(const ptr_& p) const
		{
			return this->p == p.p;
		}
		bool operator!=(const ptr_& p) const
		{
			return !operator==(p);
		}
		operator bool() const
		{
			return true;
		}
		T operator*() const
		{
			return *p;
		}
		T& operator*()
		{
			return *p;
		}
		ptr_& operator++()
		{
			++p;

			return *this;
		}
		ptr_ operator++(int)
		{
			auto _ptr(*this);

			operator++();

			return _ptr;
		}
		// etc...
	};
	template<class T>
	inline auto ptr(T* p)
	{
		return ptr_<T>(p);
	}

	// enumerator from STL range
	template<class I>
	class range_ : public ITERATOR(I) {
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

	template<class T>
	class constant_ : public std::iterator<std::random_access_iterator_tag, T> {
		T t;
	public:
		constant_(const T& t = 0)
			: t(t)
		{ }
		bool operator==(const constant_& t) const
		{
			return this->t == t.t;
		}
		bool operator!=(const constant_& t) const
		{
			return !operator==(t);
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

	template<class I>
	struct e_ : public I {
		e_(const I& i)
			: I(i)
		{ }
		operator bool() const
		{
			return true;
		}
	};
	template<class I>
	inline auto e(const I& i)
	{
		return e_<I>(i);
	}

	template<class I>
	class counted_ : public I {
		size_t n;
	public:
		counted_(const I& i, size_t n)
			: I(i), n(n)
		{ }
		bool operator==(const counted_& i) const
		{
			return n == i.n && I::operator==(i);
		}
		bool operator!=(const counted_& i) const
		{
			return !operator==(i);
		}
		operator bool() const
		{
			return n != 0;
		}
		counted_& operator++()
		{
			return --n, static_cast<counted_&>(I::operator++());
		}
		counted_ operator++(int)
		{
			return counted_(I::operator++(0), n--);
		}
	};
	template<class I>
	inline auto counted(const I& i, size_t n)
	{
		return counted_<I>(i, n);
	}

	template<class T, size_t N>
	inline auto array(T(&a)[N])
	{
		return counted(ptr_<T>(a), N);
	}

	template<class I>
	struct null_ : public I {
		null_(const I& i)
			: I(i)
		{ }
		operator bool() const
		{
			return I::operator*() != 0;
		}
		null_& operator++()
		{
			return static_cast<null_&>(I::operator++());
		}
		null_ operator++(int)
		{
			return null_(I::operator++(0));
		}
	};
	template<class I>
	inline auto null(const I& i)
	{
		return null_<I>(i);
	}
	template<class I>
	inline auto n(const I& i)
	{
		return null(i);
	}

	template<class I, class J>
	class concat2_ : std::iterator<
		std::common_type_t<typename I::iterator_category, typename J::iterator_category>,
		std::common_type_t<typename I::value_type, typename J::value_type>>
	{
		I i;
		J j;
	public:
		using value_type = std::common_type_t<typename I::value_type, typename J::value_type>;
		concat2_(const I& i, const J& j)
			: i(i), j(j)
		{ }
		operator bool() const
		{
			return i ? i.operator bool() : j.operator bool();
//			return i ? i : j;
		}
		value_type operator*() const
		{
		    return i ? *i : *j;
		}
		concat2_& operator++()
		{
			if (i)
				++i;
			else
				++j;

			return *this;
		}
		concat2_ operator++(int)
		{
			concat2_ _concat2(*this);

			operator++();

			return _concat2;
		}
	};
	template<class I, class J>
	inline auto concat2(const I& i, const J& j)
	{
		return concat2_<I,J>(i, j);
	}

	template<class F>
	class generate_ : public constant_<std::result_of_t<F()>> {
		using T = std::result_of_t<F()>;
		F f;
	public:
		generate_(const F& f)
			: f(std::move(f))
		{
			constant_<T>::operator*() = this->f();
		}
		generate_& operator++()
		{
			constant_<T>::operator*() = f();

			return *this;
		}
		generate_ operator++(int)
		{
			generate_ _generate(*this);

			operator++();

			return _generate;
		}
	};
	template<class F>
	inline auto generate(const F& f)
	{
		return generate_<F>(f);
	}

	template<class I, class J>
	inline bool equal(I i, J j)
	{
		while (i && j)
			if (*i++ != *j++)
				return false;

		return !i && !j;
	}

} // namespace e
#ifdef _DEBUG
#include <cassert>
#include <vector>

inline void test_e()
{
	using namespace e;

	{
		int i[] = {0,1,2};
		auto p = ptr(i);
		auto p2(p);
		p = p2;

		assert (p2 == p);
		assert (p);
		assert (*p == 0);
		p++;
		assert (*p == 1);
		*p = 3;
		assert (*p == 3);

		auto e = e::e(p);
		assert (*e == 3);
		assert (*++e == 2);
	}
	{
		auto c = e::c(2);
		auto c2(c);
		c = c2;
		assert (c == c2);
		assert (*c == 2);
		assert (*++c == 2);
		assert (*c++ == 2);
		assert (c);
		*c = 3;
		assert (*c == 3);
		assert (*++c++ == 3);
	}
	{
		int i[] = {0,1,2};
		auto i2 = counted(ptr(i), 2);
		auto i3 = counted(ptr(i), 3);
		assert (i2 != i3);
	}
	{
		char c[4] = "abc";
		auto n = null(ptr(c));
		auto n2(n);
		n = n2;
		assert (n == n2);

		assert (n);
		assert (*n == 'a');
		n++;
		assert (n);
		assert (*n == 'b');
		assert (*++n == 'c');
		assert (!++n);

		auto m = counted(ptr(c), 2);
		auto m2(m);
		m = m2;
		assert (m);
		assert (*m == 'a');

		auto m_ = m++;
		assert (*m_ == 'a');
		assert (++m_);
		assert (*m_ == 'b');
		assert (!++m_);

		assert (m);
		assert (*m == 'b');
		assert (!++m);
	}
	{
		auto iota = []() { static int i = 0; return ++i; };
		auto e = generate(iota);
		assert (e);
		assert (*e == 1);
		e++;
		assert (*e == 2);
		assert (*++e == 3);
	}
	{
		int i[] = {0,1,2};
		auto a = array(i);
		auto a2(a);
		a = a2;
		assert (a == a2);

		assert (a);
		assert (*a == 0);
		a++;
		assert (*a == 1);
		assert (*++a == 2);
		assert (!++a);

		char c[] = "abc";
		auto d = array(c);
		auto n = null(ptr(c));

		assert (!equal(d, n));

	}
	{
		std::vector<int> i = {0,1,2};
		auto e = range(i.begin(), i.end());
		auto e2(e);
		e = e2;
		assert (e == e2);
		assert (e);
		assert (*e == 0);
		e++;
/*		auto e3 = range(i.begin(), e);
		assert (e != e3);
		assert (*e == 1);
		assert (*++e == 2);
		assert (!++e);
*/	}
	{
		std::vector<int> i = {0,1,2};
		int j[] = {0,1,2};
		auto e = e::range(i);
		assert (e);
		assert (*e == 0);
		e++;
		assert (*e == 1);
		assert (equal(e::range(i), array(j)));
	}
	{
		std::vector<int> i = {0,1,2};
		std::vector<double> d = {.3,.4};
		auto c = concat2(e::range(i), e::range(d));
		auto c2(c);
		c = c2;
		assert (*c++ == 0);
		assert (*c++ == 1);
		assert (*c++ == 2);
		assert (*c++ == .3);
		assert (*c++ == .4);
		assert (!c);
	}
}

#endif // _DEBUG
