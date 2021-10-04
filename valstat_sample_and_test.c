/* µnit is MIT-licensed */
#include "dbjclib/valstat_interop.h"
#include "ubut/utest.h"

// VALSTAT used is: valstat_uint64_t
// here we declare and define it
VALSTAT(uint64_t);

// VALSTAT is a struct of two pointers
// & divider_rezult_ is used as 
// VALSTAT instance aggregate initializer
static uint64_t divider_rezult_ = 0;

// we could use this: valstat_type(uint64_t)
// or valstat_uint64_t as we did here
static valstat_uint64_t
divider(uint64_t dividend, uint64_t divisor)
{
	if (0 == divisor)
		return valstat_error(valstat_uint64_t, "invalid_argument: zero divisor");

	if ((dividend) >= UINT16_MAX)
		return valstat_error(valstat_uint64_t, "dividend too large");

	if ((divisor) >= UINT16_MAX)
		return valstat_error(valstat_uint64_t, "divisor too large");

	divider_rezult_ = (dividend / divisor);

	return valstat_ok(valstat_uint64_t, divider_rezult_);
}

UTEST(dbjclib, dbj_valstat_test)
{
	valstat_uint64_t rez1 = divider(4, 2);

	ASSERT_TRUE(is_valstat_ok(rez1));
	EXPECT_EQ(2, *rez1.val);

	valstat_uint64_t rez2 = divider(4, 0);

	ASSERT_TRUE(is_valstat_error(rez2));
	EXPECT_FALSE(rez2.stat);
	UBUT_TRACE("%s", rez2.stat);
}