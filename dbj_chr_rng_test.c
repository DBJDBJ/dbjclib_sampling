
// in main.c: #define DBJ_CHAR_RANGE_IMPLEMENTATION 1
#include "dbjclib/dbj_chr_rng/dbj_chr_rng.h"

#include "ubut/utest.h"

// specimen starts from 1
// for "1234567890", sub(5,7) yields '567'
#define SPECIMEN "1234567890"
/* ----------------------------------------------------------------------- */
UTEST(core_tests, dbj_char_range)
{
	dbj_chr_rng dbjs_1 = dbj_chr_rng_assign(SPECIMEN);
	EXPECT_TRUE(dbj_valid_chr_range(&dbjs_1));
	EXPECT_TRUE(10 == dbj_chr_rng_len(&dbjs_1));

	dbj_chr_rng dbjs_2 = dbj_chr_rng_assign(SPECIMEN SPECIMEN);
	EXPECT_TRUE(dbj_valid_chr_range(&dbjs_2));
	EXPECT_TRUE(20 == dbj_chr_rng_len(&dbjs_2));

	EXPECT_FALSE(dbj_chr_rng_compare(&dbjs_1, &dbjs_2));

	// TODO! dbj_chr_rng dbjs_3 = dbj_remove_substring(&dbjs_2, &dbjs_1);

	dbj_chr_rng_free(&dbjs_1);
	dbj_chr_rng_free(&dbjs_2);
	// dbj_chr_rng_free(&dbjs_3);
}
/* ----------------------------------------------------------------------- */
UTEST(core_tests, dbj_char_string_view_range)
{
	dbj_chr_rng r1 = chr_rng_ptr_two_marks(SPECIMEN, 1, 3);
	dbj_chr_rng r2 = chr_rng_ptr_two_marks(SPECIMEN, 4, 6);

	EXPECT_TRUE(dbj_chr_rng_compare(&r1, &r1));

	EXPECT_FALSE(dbj_chr_rng_compare(&r1, &r2));

	// this should crash?
	// as ranges are not zero delimited
	EXPECT_STRNE(r1.front, r2.front);
	EXPECT_STREQ(r1.front, r1.front);

	dbj_chr_rng_free(&r1);
	dbj_chr_rng_free(&r2);
}

#undef SPECIMEN
