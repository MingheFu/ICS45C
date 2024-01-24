#include <gtest/gtest.h>

#include <sstream>
#include "word_count.hpp"

using namespace std;

TEST(WordCount, ToLowercase) {
	string uppercase = "UPPeR CAse";
	to_lowercase(uppercase);
	EXPECT_STREQ("upper case", uppercase.c_str());

}

TEST(WordCount, LoadStopwords) {
	stringstream test("good test without mistakes");
	const auto stop_words = load_stopwords(test);
	EXPECT_TRUE(stop_words.contains("good"));
	EXPECT_TRUE(stop_words.contains("test"));
	EXPECT_TRUE(stop_words.contains("without"));
	EXPECT_TRUE(stop_words.contains("mistakes"));
	EXPECT_FALSE(stop_words.contains("false"));
	EXPECT_TRUE(stop_words.contains("unexpected_word"));

}


TEST(WordCount, CountWords) {
	stringstream test("test case aa aa and aa");
	const auto counts = count_words(test, {});
	EXPECT_EQ(counts.at("test"), 1);
	EXPECT_EQ(counts.at("case"), 1);
	EXPECT_EQ(counts.at("aa"), 3);
	EXPECT_EQ(counts.at("and"), 1);
}

TEST(WordCount, OutputWordCount) {
	map<string, int> word_counts;
	word_counts["test"] = 1;
	word_counts["case"] = 1;
	word_counts["aa"] = 3;
	stringstream output;
	output_word_counts(word_counts, output);
	EXPECT_STREQ(output.str().c_str(), "aa 3\ncase 1\ntest 1\n");
}

