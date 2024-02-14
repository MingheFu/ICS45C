#include <gtest/gtest.h>

#include "list.hpp"

using namespace std;
using list::Node;

TEST(ListTests, FromStringBasic) {
    Node* const foo_list_head = list::from_string("foo");
    Node* foo_list = foo_list_head;

    EXPECT_EQ(foo_list->data, 'f');
    // ASSERT instead of EXPECT means: end the test here if this fails, do not try to continue
    // running. This is useful to prevent early crashes.
    ASSERT_NE(foo_list->next, nullptr);

    foo_list = foo_list->next;
    EXPECT_EQ(foo_list->data, 'o');
    ASSERT_NE(foo_list->next, nullptr);

    foo_list = foo_list->next;
    EXPECT_EQ(foo_list->data, 'o');
    ASSERT_EQ(foo_list->next, nullptr);

    list::free(foo_list_head);
}

TEST(ListTests, Length) {
    Node* const head = list::from_string("foo");
    EXPECT_EQ(list::length(head), 3);
    list::free(head);
}
	
TEST(ListTests, CopyList) {
    Node* const original_head = list::from_string("test");
	Node* copied_head = list::copy(original_head);
	Node* original_current = original_head;
	Node* copied_current = copied_head;
	while (original_current != nullptr) {
		ASSERT_NE(copied_current, nullptr);
		EXPECT_EQ(original_current->data, copied_current->data);
		original_current = original_current->next;
		copied_current = copied_current->next;
	}
	EXPECT_EQ(copied_current, nullptr);
	list::free(original_head);
	list::free(copied_head);
	copied_head = list::copy(nullptr);
	EXPECT_EQ(copied_head, nullptr);
}

TEST(ListTests, Reverselist) {
	Node* head = list::from_string("test");
    head = list::reverse(head);
    const char expected_order[] = {'t', 's', 'e', 't'};
    const size_t expected_length = 4;
    
    Node* current = head;
    for (size_t i = 0; i < expected_length; ++i) {
        ASSERT_NE(current, nullptr);
        EXPECT_EQ(current->data, expected_order[i]);
        current = current->next;
    }
    EXPECT_EQ(current, nullptr);
    list::free(head);
}

TEST(ListTests, CompareLists) {
	Node* const list_one = list::from_string("abc");
	Node* const list_two = list::from_string("abc");
    Node* const list_three = list::from_string("abd");
    EXPECT_EQ(list::compare(list_one, list_two), 0);
    EXPECT_LT(list::compare(list_one, list_three), 0);
    EXPECT_GT(list::compare(list_three, list_two), 0);
    EXPECT_GT(list::compare(list_one, nullptr), 0);
    EXPECT_LT(list::compare(nullptr, list_one), 0);
    EXPECT_EQ(list::compare(nullptr, nullptr), 0);
    list::free(list_one);
    list::free(list_two);
    list::free(list_three);
}

TEST(ListTests, FindChar) {
	Node* const head = list::from_string("hello");
    Node* result = list::find_char(head, 'e');
    ASSERT_NE(result, nullptr);
    EXPECT_EQ(result->data, 'e');
    result = list::find_char(head, 'n');
    EXPECT_EQ(result, nullptr);
    list::free(head);
    result = list::find_char(nullptr, 'a');
    EXPECT_EQ(result, nullptr);
}

TEST(ListTests, FindList) {
	Node* const haystack = list::from_string("example");
    Node* const needle = list::from_string("amp");
    Node* const notFoundNeedle = list::from_string("nnn");
    Node* result = list::find_list(haystack, needle);
    ASSERT_NE(result, nullptr);
    EXPECT_EQ(result->data, 'a');
    result = list::find_list(haystack, notFoundNeedle);
    EXPECT_EQ(result, nullptr);
    EXPECT_EQ(list::find_list(nullptr, needle), nullptr);
    EXPECT_EQ(list::find_list(haystack, nullptr), haystack);
    list::free(haystack);
    list::free(needle);
    list::free(notFoundNeedle);
}

TEST(ListTests, GetLast) {
    Node* const head = list::from_string("test");
    Node* lastNode = list::last(head);
    ASSERT_NE(lastNode, nullptr);
    EXPECT_EQ(lastNode->data, 't');
    list::free(head);
}

TEST(ListTests, GetNth) {
	Node* const head = list::from_string("test");
    int n = 3;
    Node* nthNode = list::nth(head, n);
    ASSERT_NE(nthNode, nullptr);
    EXPECT_EQ(nthNode->data, 't');
    list::free(head);
}


TEST(ListTests, CompareNLists) {
	Node* list1 = list::from_string("testing");
    Node* list2 = list::from_string("testif");
    Node* list3 = list::from_string("test");
    int result = list::compare(list1, list2, 4);
    EXPECT_EQ(result, 0); 
    result = list::compare(list1, list3, 4);
    EXPECT_EQ(result, 0);
    result = list::compare(list1, list3, 6);
    EXPECT_GT(result, 0);
    list::free(list1);
    list::free(list2);
    list::free(list3);
}


TEST(ListTests, ListsIndex) {
	Node* const list = list::from_string("hello");
    Node* searchNode = list;
    for (int i = 0; i < 3; ++i) {
        searchNode = searchNode->next;
    }
    int index = list::index(list, searchNode);
    EXPECT_EQ(index, 3);
    list::free(list);
}

TEST(ListTests, Appendlists) {
	Node* const list_one = list::from_string("hello");
    Node* const list_two = list::from_string("world");
    Node* appendedList = list::append(list_one, list_two);
    EXPECT_EQ(list::length(appendedList), 10);
    Node* appendNull = list::append(list_one, nullptr);
    EXPECT_EQ(list::length(appendNull), 5);
    Node* appendToNull = list::append(nullptr, list_two);
    EXPECT_EQ(list::length(appendToNull), 5);
    list::free(list_one);
    list::free(list_two);
    list::free(appendedList);
    list::free(appendNull);
    list::free(appendToNull);
}

TEST(ListTests, PrintLists) {
	Node* const head = list::from_string("test");
	std::stringstream out;
	list::print(out, head);
	EXPECT_EQ(out.str(), "test");
	list::free(head);
}



