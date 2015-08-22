// concatenate_.h - concatenate enumerators
#pragma once
#include "enumerator_.h"

namespace fms {

	template<class E...>
	class concatenate_ : enumerator_<std::common_type<E...::iterator_type>, std::common_type<E...::value_type>> {
	};

} // fms
