#pragma once
#include <iterator>

template<class E>
class enumerator_ : public std::iterator<
	typename std::iterator_traits<E>::iterator_category,
	typename std::iterator_traits<E>::value_type,
	typename std::iterator_traits<E>::difference_type,
	typename std::iterator_traits<E>::pointer,
	typename std::iterator_traits<E>::reference>
{
	E e;
public:
	using value_type = typename std::iterator_traits<E>::value_type;
	using reference = typename std::iterator_traits<E>::reference;

	enumerator_(E e)
		: e(e)
	{ }
	operator bool() const
	{
		return true;
	}
	value_type operator*() const
	{
		return *e;
	}
	reference operator*() 
	{
		return *e;
	}
	enumerator_& operator++()
	{
		++e;

		return *this;
	}
	enumerator_ operator++()
	{
		enumerator_ e_(*this);

		operator++();

		return e_;
	}

};
