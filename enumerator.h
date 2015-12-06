// enumerator.h - iterators having operator bool() const
#pragma once
#include <iterator>

namespace enumerator {

	// Enumerator classes usually publicly inherit from this and
	// implement `operator bool() const` along with other methods.
	template<class I>
	using iterator = std::iterator< 
		typename std::iterator_traits<I>::iterator_category,
		typename std::iterator_traits<I>::value_type,
		typename std::iterator_traits<I>::difference_type,
		typename std::iterator_traits<I>::pointer,
		typename std::iterator_traits<I>::reference
	>;

} // namespace enumerator

#include "ptr_.h"
#include "null_.h"
#include "counted_.h"
#include "constant_.h"
#include "range_.h"
  /*
#include "apply_.h"
#include "counted_.h"
#include "end_.h"
#include "iota_.h"
x#include "rotate.h"
#include "until_.h"

#include "cmp.h"
#include "copy.h"
#include "swap.h"

#include "counted_enumerator_.h"
#include "pair_.h"

#include "past.h"
#include "skip.h"
#include "until.h"
#include "upto.h"

*/