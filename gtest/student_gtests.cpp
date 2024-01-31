#include <gtest/gtest.h>

#include "string.hpp"

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
	EXPECT_EQ(String::strstr("", ""), nullptr);
	EXPECT_EQ(String::strstr("", "foo"), nullptr);
}
