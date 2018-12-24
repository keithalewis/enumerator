// concatenate_.h - concatenate enumerators
#pragma once
#include <iterator>

namespace fms {

	template<class E0, class E1>
	class concatenate_ : public std::iterator<
		std::common_type<E0::iterator_type,E1::iterator_type>, 
		std::common_type<E0::value_type,E1::value_type>> 
	{
		E0 e0;
		E1 e1;
	public:
		typedef std::common_type<E0::iterator_type,E1::iterator_type> iterator_type;
		typedef std::common_type<E0::value_type,E1::value_type> value_type;
		concatenate_(E0 e0, E1 e1)
			: e0(e0), e1(e1)
		{ }
		operator bool() const
		{
			return e0 ? true : e1;
		}
		value_type operator*() const
		{
			return e0 ? value_type(*e0) : value_type(*e1);
		}
		concatenate_& operator++()
		{
			e0 ? ++e0 : ++e1;

			return *this;
		}
	};

} // fms
