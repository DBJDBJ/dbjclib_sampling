
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

	dbj_chr_rng dbjs_3 = dbj_remove_substring(&dbjs_2, &dbjs_1);

	dbj_chr_rng_free(&dbjs_1);
	dbj_chr_rng_free(&dbjs_2);
	dbj_chr_rng_free(&dbjs_3);
}
/* ----------------------------------------------------------------------- */
UTEST(core_tests, dbj_char_string_view_range)
{

	// remember: no memory is allocated for the strings viewed
	// thus be carefull to keep them arround

	EXPECT_TRUE(3 == dbj_sv_len(dbj_sv_make(SPECIMEN, 1, 3)));

	EXPECT_TRUE(
		dbj_sv_compare(
			dbj_sv_make(SPECIMEN, 1, 3), dbj_sv_make(SPECIMEN, 1, 3)));

	EXPECT_FALSE(
		dbj_sv_compare(
			dbj_sv_make(SPECIMEN, 1, 3), dbj_sv_make(SPECIMEN, 4, 6)));

	EXPECT_STRNE(
		dbj_sv_make(SPECIMEN, 1, 3)->front,
		dbj_sv_make(SPECIMEN, 4, 6)->front);

	EXPECT_STREQ(
		dbj_sv_make(SPECIMEN, 1, 3)->front,
		dbj_sv_make(SPECIMEN, 1, 3)->front);


}

#undef SPECIMEN
