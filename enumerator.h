// enumerator.h - iterators with operator bool() const
#pragma once
#include <cstddef>
#include <functional>

namespace enumerator {

	// is_enumerator : has op_bool_const && has op_star_const && has op_incr

	template<class E, class F>
	inline bool equal(E e, F f)
	{
		for (; e && f; ++e, ++f)
			if (*e != *f)
				return false;

		if (!e && !f)
			return true;

		return false;
	}

	template<class E>
	class predicate {
		E e;
		std::function<bool(E)> p;
	public:
		predicate(E e, const std::function<bool(E)>& p)
			: e(e), p(p)
		{ }
		operator bool() const
		{
			return p(e);
		}
		auto operator*() const
		{
			return *e;
		}
		predicate& operator++()
		{
			++e;

			return *this;
		}
	};

	// Specify the number of elements
	template<class E>
	class counted {
		E e;
		std::size_t n;
	public:
		counted(E e, std::size_t n)
			: e(e), n(n)
		{ }
		operator bool() const
		{
			return n != 0;
		}
		auto operator*() const
		{
			return *e;
		}
		counted& operator++()
		{
			++e;
			--n;

			return *this;
		}
	};

	template<class E>
	inline auto take(std::size_t n, E e)
	{
		return counted(e, n);
	}

	// null terminated iterator
	template<class E>
	class null {
		E e;
	public:
		null(E e)
			: e(e)
		{ }
		operator bool() const
		{
			return *e != 0;
		}
		auto operator*() const
		{
			return *e;
		}
		null& operator++()
		{
			++e;

			return *this;
		}
	};

	template<class E> // is_floating_point<decltype(*E)>
	class epsilon {
		E e;
	public:
		epsilon(E e)
			: e(e)
		{ }
		operator bool() const
		{
			return *e + 1 != 1;
		}
		auto operator*() const
		{
			return *e;
		}
		epsilon& operator++()
		{
			++e;

			return *this;
		}
	};

	// Drop (up to) n elements.
	template<class E>
	inline auto drop(std::size_t n, E e)
	{
		for (; e && n; ++e, --n)
			;

		return e;
	}

	// 1, t, t^2, ...
	template<class T>
	class pow {
		T t, v;
	public:
		pow(T t)
			: t(t), v(T(1))
		{ }
		operator bool() const
		{
			return true;
		}
		T operator*() const
		{
			return v;
		}
		pow& operator++()
		{
			v *= t;

			return *this;
		}
	};

} // enumerator
