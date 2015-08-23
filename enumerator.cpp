// enumerator.cpp
#include "enumerator.h"

int main()
{
	test_enumerator_();
	test_counted_enumerator();

	test_apply_();
	test_iota_();
	test_pair_();

	test_past();
	test_until();
	test_upto();

	test_range_();

	test_skip();

	return 0;
}