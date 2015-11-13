// enumerator.cpp
#include <cassert>
#include "enumerator.h"

using namespace enumerator;

void test_copy_until()
{
	char s[2];
	copy(until([](auto pc) { return *pc == 'c'; }, "abcd"), s);
	assert (0 == strncmp(s, "ab", 2));
}

int main()
{
	test_null_();
	test_apply_();
	test_until_();

//	test_cmp();
	test_copy();
	test_swap();

	test_copy_until();
	/*
	test_counted_enumerator();
	test_iota_();
	test_pair_();

	test_past();
	test_upto();

	test_range_();

	test_skip();
*/
	return 0;
}