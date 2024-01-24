#include <gtest/gtest.h>


#include <sstream>
#include "word_count.hpp"

using namespace std;

TEST(WordCount, ToLowercase) {
	string uppercase = "Café";
	to_lowercase(uppercase);
	EXPECT_STREQ("café", uppercase.c_str());

}

TEST(WordCount, LoadStopwords) {
	stringstream test("Word word WorD WORd");
	const auto stop_words = load_stopwords(test);
	EXPECT_TRUE(stop_words.contains("word"));
	//EXPECT_TRUE(stop_words.contains("test"));
	//EXPECT_TRUE(stop_words.contains("without"));
	//EXPECT_TRUE(stop_words.contains("mistakes"));
	//EXPECT_FALSE(stop_words.contains("false"));
	//EXPECT_FALSE(stop_words.contains("unexpected_word"));

}


TEST(WordCount, CountWords) {
	stringstream test("Word word Word WoRd");
	const auto counts = count_words(test, {});
	EXPECT_EQ(counts.at("word"),4);
}

TEST(WordCount, OutputWordCount) {
	map<string, int> word_counts;
	word_counts[string(100003, 'a')] = 1;
	//word_counts["test"] = 1;
	//word_counts["case"] = 1;
	//word_counts["aa"] = 3;
	stringstream output;
	output_word_counts(word_counts, output);
	//EXPECT_STREQ(output.str().c_str(), "aa 3\ncase 1\ntest 1\n");
	EXPECT_LE(output.str().length(), 100006);

}

TEST(WordCount, ToLowercaseMixedCase) {
	string test = "HeLLO WorlD";
	to_lowercase(test);
	EXPECT_EQ("hello world", test);
}

TEST(WordCont, ToLowerCaseAllUpper) {
	string test = "TEST";
	to_lowercase(test);
	EXPECT_EQ("test", test);
}

TEST(WordCount, LoadStopWordsEmptyStream) {
	stringstream test("");
	const auto stop_words = load_stopwords(test);
	EXPECT_TRUE(stop_words.empty());
}

TEST(WordCount, CountWordsEmpty) {
	stringstream test("");
	const auto counts = count_words(test, {});
	EXPECT_TRUE(counts.empty());
}

TEST(WordCount, CountWordsWithStopWords) {
	stringstream test("count with stop words");
	stringstream stopwords("count with");
	const auto stop_words = load_stopwords(stopwords);
	const auto counts = count_words(test, stop_words);
	EXPECT_EQ(counts.at("stop"), 1);
	EXPECT_EQ(counts.at("words"), 1);
	EXPECT_FALSE(counts.count("count"));
	EXPECT_FALSE(counts.count("with"));
}

TEST (WordCount, OutputWordCountsEmpty) {
	map<string, int> word_counts;
	stringstream output;
	output_word_counts(word_counts,output);
	EXPECT_TRUE(output.str().empty());
}

TEST (WordCount, LoadStopWordsRepetive) {
	stringstream test("hi hi hello");
	const auto stop_words = load_stopwords(test);
	EXPECT_EQ(stop_words.size(), 2);
	EXPECT_TRUE(stop_words.contains("hi"));
	EXPECT_TRUE(stop_words.contains("hello"));
}

TEST(WordCount, CountWordsWithSpecialChars) {
	stringstream test("123 456 hello");
	const auto counts = count_words(test, {});
	EXPECT_EQ(counts.at("123"), 1);
	EXPECT_EQ(counts.at("456"), 1);
	EXPECT_EQ(counts.at("hello"), 1);
}

TEST(WordCount, CountWordsNoWordsValid) {
	stringstream test("stop word");
	stringstream stopwords("stop word");
	const auto stop_words = load_stopwords(stopwords);
	const auto counts = count_words(test, stop_words);
	EXPECT_TRUE(counts.empty());
}

TEST(WorldCount, outputWordCountsWithIdenticalAppear) {
	map<string, int> word_counts;
	word_counts["same"] = 2;
	word_counts["time"] = 2;
	stringstream output;
	output_word_counts(word_counts, output);
	EXPECT_EQ(output.str(), "same 2\ntime 2\n");
}

