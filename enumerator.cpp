// enumerator.cpp
#include <cassert>
#include "enumerator.h"

void test_counted()
{
	using enumerator::equal;
	using enumerator::counted;
	int e[] = {1,2,3};
	auto ce = counted(e,3);
	auto ce2{ ce };
	assert(equal(ce, ce2));
	ce = ce2;
	assert(equal(ce, ce2));
	assert (ce);
	assert(*ce == 1);
	assert(*++ce == 2);
	++ce;
	assert(*ce == 3);
	++ce;
	assert(!ce);

	ce = counted(e, 3);
	assert(equal(counted(e, 2), take(2, ce)));

//	using enumerator::predicate;
//	auto three = [](int*) { static std::size_t n = 3; 0 != n--; };
//	auto pe = predicate(e, three);
//	assert(equal(ce, pe));
}

void test_equal()
{
	using enumerator::equal;
	using enumerator::counted;

	int e[] = {1,2,3};
	assert (enumerator::equal(counted(e,3), counted(e,3)));
	assert(!enumerator::equal(counted(e, 2), counted(e, 3)));
}

void test_null()
{
	using enumerator::null;

	auto abc = null("abc");
	assert(abc);
	++abc; ++abc;
	assert(*abc == 'c');
	assert(!++abc);
}

void test_pow()
{
	using enumerator::pow;
	using enumerator::epsilon;

	double t = 0.5;
	pow<double> tn(t);
	assert(tn && *tn == 1);
	assert(++tn && *tn == t);
	assert(++tn && *tn == t*t);
	assert(++tn && *tn == t * t * t);

	auto et = epsilon(tn);
	size_t n = 3;
	while (++et)
		++n;
	assert (n == 52);
}

int main()
{
	test_counted();
	test_equal();
	test_null();
	test_pow();

	return 0;
}
