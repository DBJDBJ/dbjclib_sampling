#define UTEST_IMPLEMENTATION
#include "ubut/utest.h"

// note there is no ()! 
UTEST_STATE;

int main(int argc, const char* const argv[])
{
#if defined(_MSC_VER)
	system("@chcp 65001 >NUL");
	system(" ");
#endif

	return utest_main(argc, argv);
}