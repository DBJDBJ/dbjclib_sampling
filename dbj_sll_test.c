/* µnit is MIT-licensed */
#include "ubut/utest.h"

#include "dbjclib/dbjclib_core.h"
#include "dbjclib/dbj_hsl/dbj_hsl.h"


static struct test_dbj_hsl {
	int input_size_;
	const char* input[3];
} test_data = { 3, { "BIMBILI", "BAMBILI", "BUMBILI" } };

UTEST(dbjclib, dbj_hsl)
{
	dbj_hsl_node* head_ = dbj_hsl_make_head();

	int walker_ = 0;
	while (walker_ != test_data.input_size_)
		dbj_hsl_append(head_, test_data.input[walker_++]);

	/*
	Debugging messages, are hidden by default (see the --log-visible option).
	https://nemequ.github.io/munit/#--log-visible

	dbj_hsl_node_dump_visitor default stream is stderr
	*/
	UBUT_TRACE("DBJ SLL dump");
	dbj_hsl_foreach(head_, dbj_hsl_node_dump_visitor);

	// remove tail returns pointer to the new tail
	// dbj_hsl_node* new_tail_ = dbj_hsl_remove_tail(head_);

	// head stays
	dbj_hsl_erase(head_);
	UBUT_TRACE("Head after SLL erasure");
	dbj_hsl_node_dump_visitor(head_);

	// start from the head of the empty list
	ASSERT_TRUE(true == is_dbj_hsl_empty(head_));

	unsigned long k1 = dbj_hsl_append(head_, "Abra")->key;
	unsigned long k2 = dbj_hsl_append(head_, "Ka")->key;
	unsigned long k3 = dbj_hsl_append(head_, "Dabra")->key;

	dbj_hsl_node* node_1 = dbj_hsl_find(head_, k1);
	ASSERT_TRUE(0 == strcmp(node_1->data, "Abra"));

	dbj_hsl_node* node_2 = dbj_hsl_find(head_, k2);
	ASSERT_TRUE(0 == strcmp(node_2->data, "Ka"));

	dbj_hsl_node* node_3 = dbj_hsl_find(head_, k3);
	ASSERT_TRUE(0 == strcmp(node_3->data, "Dabra"));

	ASSERT_TRUE(false == is_dbj_hsl_empty(head_));

	dbj_hsl_erase_with_head(&head_);
	EXPECT_FALSE(head_);
}

