// sequence.h - iterator having operator bool() const
// Add end class so the sequence(i, end) has a begin and end.
#pragma once

#include <iterator>
#include <tuple>
#include <type_traits>

template<class I>
class sequence : public std::iterator<
	typename std::iterator_traits<I>::iterator_category,
	typename std::iterator_traits<I>::value_type,
	typename std::iterator_traits<I>::difference_type,
	typename std::iterator_traits<I>::pointer,
	typename std::iterator_traits<I>::reference>
{
protected:
	I i;
public:
	sequence()
	{ }
	sequence(I i)
		: i(i)
	{ }
	operator bool() const
	{
		return true;
	}
	bool operator==(const sequence& i_) const
	{
		return i == i_.i;
	}
	bool operator!=(const sequence& i_) const
	{
		return i != i_.i;
	}
	typename std::iterator_traits<I>::value_type operator*()
	{
		return *i;
	}
	sequence& operator++()
	{
		++i;

		return *this;
	}
	sequence operator++(int)
	{
		return sequence(i++);
	}
	// enable_if the rest
};
template<class I>
struct null_sequence : public sequence<I> {
	null_sequence()
	{ }
	null_sequence(I i)
		: sequence<I>(i)
	{ }
	operator bool() const
	{
		return *i != 0;
	}
};
template<class I>
class counted_sequence : public sequence<I> {
	size_t n;
public:
	counted_sequence()
	{ }
	counted_sequence(I i, size_t n)
		: sequence<I>(i), n(n)
	{ }
	bool operator==(const counted_sequence& i_) const
	{
		return i == i_.i && n == i_.n;
	}
	bool operator!=(const counted_sequence& i) const
	{
		return !operator==(i);
	}
	operator bool() const
	{
		return n != 0;
	}
	counted_sequence& operator++()
	{
		++i;
		--n;

		return *this;
	}
	counted_sequence operator++(int)
	{
		return counted_sequence(i++, n--);
	}
};
template<class T>
class counter : public std::iterator<
	std::forward_iterator_tag, T>
{
	T i;
public:
	counter(T i = 0)
		: i(i)
	{ }
	bool operator==(const counter c) const
	{
		return i == c.i;
	}
	bool operator!=(const counter c) const
	{
		return i != c.i;
	}
	T operator*()
	{
		return i;
	}
	counter& operator++()
	{
		++i;
		
		return *this;
	}
	counter operator++(int)
	{
		return counter(i++);
	}
};
template<class ...Is>
class tupler : public std::iterator<
	std::input_iterator_tag, typename std::common_type<Is...>::type>
{
	size_t n;
	std::tuple<Is...> is;
public:
	tupler()
	{ }
	tupler(Is... is)
		: n(0), is(is...)
	{ }
	typename std::common_type<Is...>::type operator*()
	{
		return std::get<n>(is);
	}
	tupler& operator++()
	{
		++n;

		return *this;
	}
};

template<class C>
class container_sequence : public sequence<typename C::iterator> {
	C& c;
public:
	container_sequence(C& c)
		: sequence<typename C::iterator>(c.begin()), c(c)
	{ }
	operator bool() const
	{
		return i != c.end();
	}
};


#ifdef _DEBUG
#include <cassert>
#include <vector>

void test_sequence()
{
	{
		null_sequence<char*> s("foo");
		null_sequence<char*> s_(s);
		assert (s == s_);
		null_sequence<char*> _s;
		_s = s;
		assert (s == _s);

		assert (s);
		assert (*s == 'f');
		++s;
		assert (s);
		assert (*s == 'o');
		++s;
		assert (s);
		assert (*s == 'o');
		s++;
		assert (!s);
	}
	{
		counted_sequence<char*> s("foo", 2);
		counted_sequence<char*> s_(s);
		assert (s == s_);
		counted_sequence<char*> _s;
		_s = s;
		assert (s == _s);

		assert (s);
		assert (*s == 'f');
		++s;
		assert (s);
		assert (*s == 'o');
		++s;
		assert (!s);
	}
	{
		std::vector<int> v{1,2,3};
		counted_sequence<std::vector<int>::iterator> s(v.begin(), 3);
		assert (s);
		assert (s);
		assert (*s == 1);
		++s;
		assert (s);
		assert (*s == 2);
		++s;
		assert (s);
		assert (*s == 3);
		s++;
		assert (!s);
	}
	{
		std::vector<int> v{1,2,3};
		container_sequence<std::vector<int>> s(v);
		assert (s);
		assert (s);
		assert (*s == 1);
		++s;
		assert (s);
		assert (*s == 2);
		++s;
		assert (s);
		assert (*s == 3);
		s++;
		assert (!s);
	}
	{
		counter<int> c(1);
		counter<int> c_(c);
		assert (c == c_);
		counter<int> _c;
		_c = c;
		assert (c == _c);

		assert (*c == 1);
		assert (*++c == 2);
		assert (*c++ == 2);
		assert (*c == 3);

		sequence<counter<int>> sc(counter<int>(1));
		sequence<counter<int>> sc_(sc);
		assert (sc == sc_);
		sequence<counter<int>> _sc;
		_sc = sc;
		assert (sc == _sc);

		assert (sc);
		assert (*sc == 1);
		assert (*++sc == 2);
		assert (*sc++ == 2);
		assert (*sc == 3);

		counted_sequence<counter<int>> cs(counter<int>(1), 3);
		assert (*cs == 1);
		assert (*++cs == 2);
		assert (*cs++ == 2);
		assert (*cs == 3);
		assert (!++cs);
	}
	{
	}
}

#endif // _DEBUG