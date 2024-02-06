#include <gtest/gtest.h>
#include <string.h>

#include <algorithm>

#include "string.hpp"
#include "alloc.hpp"

TEST(StringFunction, strlen) {
    EXPECT_EQ(String::strlen(""), 0);
    EXPECT_EQ(String::strlen("foo"), 3);
}

TEST(StringFunction, strcpy) {
    char result[10];
    EXPECT_EQ(String::strcpy(result, "foo"), result);
    EXPECT_STREQ(result, "foo");

    EXPECT_EQ(String::strcpy(result, "a"), result);
    EXPECT_STREQ(result, "a");

    EXPECT_EQ(String::strcpy(result, ""), result);
    EXPECT_STREQ(result, "");
}

TEST(StringFunction, strdup) {
    const char* input1 = "Hello";
    char* result1 = String::strdup(input1);
    EXPECT_STREQ(result1, input1);
    delete[] result1;
    const char* input2 = "";
    char* result2 = String::strdup(input2);
    EXPECT_STREQ(result2, input2);
    delete[] result2;
    const char* input3 = nullptr;
    char* result3 = String::strdup(input3);
    EXPECT_EQ(result3, nullptr);
    const char* input4 = "!@#$*()";
    char* result4 = String::strdup(input4);
    EXPECT_STREQ(result4, input4);
    delete[] result4;
}

TEST(StringFunction, strncpy) {
    char result[10];
	EXPECT_EQ(String::strncpy(result, "foo",3), result);
	EXPECT_STREQ(result, "foo");
	EXPECT_EQ(String::strncpy(result, "bar", 2), result);
	EXPECT_STREQ(result, "ba");
	EXPECT_EQ(String::strncpy(result, "", 3), result);
	EXPECT_STREQ(result, "");
}

TEST(StringFunction, strcat) {
    char result[10];
	String::strcpy(result, "foo");
	EXPECT_EQ(String::strcat(result, "boo"), result);
	EXPECT_STREQ(result, "fooboo");
	String::strcpy(result, "foo");
	EXPECT_EQ(String::strcat(result, ""), result);
	EXPECT_STREQ(result, "foo");
}


TEST(StringFunction, strncat) {
    char result[10];
	String::strcpy(result, "foo");
	EXPECT_EQ(String::strncat(result, "boo", 3), result);
	EXPECT_STREQ(result, "fooboo");
	String::strcpy(result, "foo");
	EXPECT_EQ(String::strncat(result, "bar", 2), result);
	EXPECT_STREQ(result, "fooba");
	String::strcpy(result, "foo");
	EXPECT_EQ(String::strncat(result, "", 3), result);
	EXPECT_STREQ(result, "foo");
}

TEST(StringFunction, strcmp) {
	EXPECT_EQ(String::strcmp("foo", "foo"), 0);
	EXPECT_GT(String::strcmp("foo", "boo"), 0);
	EXPECT_LT(String::strcmp("boo", "foo"), 0);
	EXPECT_EQ(String::strcmp("", ""), 0);
}

TEST(StringFunction, strncmp) {
    EXPECT_EQ(String::strncmp("foo", "foo", 3), 0);
	EXPECT_EQ(String::strncmp("foo", "fooboo", 3), 0);
	EXPECT_GT(String::strncmp("foo", "bar", 3), 0);
	EXPECT_LT(String::strncmp("foo", "foobar", 5), 0);
	EXPECT_EQ(String::strncmp("", "", 2), 0);
}

TEST(StringFunction, reverse_cpy) {
    char result[10];
	String::strcpy(result, "hello");
	String::reverse_cpy(result, "hello");
	EXPECT_STREQ(result, "olleh");
	String::strcpy(result, "");
	String::reverse_cpy(result, "");
	EXPECT_STREQ(result, "");
}

TEST(StringFunction, strchr) {  
    EXPECT_EQ(String::strchr("hello", 'e'), &("hello"[1]));
	EXPECT_EQ(String::strchr("hello", 'h'), &("hello"[0]));
	EXPECT_EQ(String::strchr("hello", 'o'), &("hello"[4]));
	EXPECT_EQ(String::strchr("hello", 'x'), nullptr);
	EXPECT_EQ(String::strchr("", 'x'), nullptr);
}

TEST(StringFunction, strstr) {
    EXPECT_EQ(String::strstr("hello world", "world"), &("hello world"[6]));
	EXPECT_EQ(String::strstr("hello world", "hello"), &("hello world"[0]));
	EXPECT_EQ(String::strstr("hello world", "world"), &("hello world"[6]));
	EXPECT_EQ(String::strstr("hello world", ""), &("hello world"[0]));
	EXPECT_EQ(String::strstr("", "foo"), nullptr);
}
