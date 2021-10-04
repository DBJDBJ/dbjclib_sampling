#include <assert.h>
#include <string.h>

#include "ubut/utest.h"
#include "dbjclib/dbjclib_core.h"
#include "dbjclib/valstat_interop.h"

/* https://rosettacode.org/wiki/Levenshtein_distance#C.2B.2B */
/* s, t: two strings; ls, lt: their respective length */
int levenshtein(const char* s, int ls, const char* t, int lt)
{
	int a, b, c;

	/* if either string is empty, difference is inserting all chars
	 * from the other
	 */
	if (!ls) return lt;
	if (!lt) return ls;

	/* if last letters are the same, the difference is whatever is
	 * required to edit the rest of the strings
	 */
	if (s[ls - 1] == t[lt - 1])
		return levenshtein(s, ls - 1, t, lt - 1);

	/* else try:
	 *      changing last letter of s to that of t; or
	 *      remove last letter of s; or
	 *      remove last letter of t,
	 * any of which is 1 edit plus editing the rest of the strings
	 */
	a = levenshtein(s, ls - 1, t, lt - 1);
	b = levenshtein(s, ls, t, lt - 1);
	c = levenshtein(s, ls - 1, t, lt);

	if (a > b) a = b;
	if (a > c) a = c;

	return a + 1;
}

UTEST(core_tests, playground)
{

#define call_lvstn(a,b) (levenshtein(a, strlen(a), b, strlen(b)) )

	ASSERT_TRUE(call_lvstn("ISLANDER", "SLANDER") == 1);
	ASSERT_TRUE(call_lvstn("MART", "KARMA") == 3);
	ASSERT_TRUE(call_lvstn("KITTEN", "SITTING") == 3);
	ASSERT_TRUE(call_lvstn("INTENTION", "EXECUTION") == 5);

#undef call_lvstn
}

UTEST(core_tests, matrix_whatever)
{
	/*
	height: 3
		  0 1 2  --> width: 3
		0 A B C
		1 D E F
		2 G H J
	*/

	/* rows, cols */
#define HEIGHT 3
#define WIDTH 2

	int m[HEIGHT][WIDTH];

	int k;

	k = 0;	m[k][0] = 1;	m[k][1] = 2;	//m[k][2] = 'C';

	k = 1;	m[k][0] = 3;	m[k][1] = 4;	//m[k][2] = 'F';

	k = 2;	m[k][0] = 5;	m[k][1] = 6;	//m[k][2] = 'J';


}

#ifdef __clang__
#pragma clang diagnostic push
#endif
/* EOF */
