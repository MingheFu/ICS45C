#include "word_count.hpp"
#include <map>
#include <set>
#include <cctype>
#include <iterator>
#include <sstream>

void to_lowercase(std::string& str) {
	std::transform(str.begin(), str.end(), str.begin(), ::tolower);
}

std::set<std::string> load_stopwords(std::istream& stopwords) {
	std::set<std::string> stopWord;
	std::string stop_word;

	while (stopwords >> stop_word) {
		to_lowercase(stop_word);
		stopWord.insert(stop_word);
	}

	return stopWord;
}

std::map<std::string, int> count_words(std::istream& document, const std::set<std::string>& stopwords) {
	std::map <std::string, int> wordCounts;
	std::string word;
	while (document >> word) {
		to_lowercase(word);
		if (stopwords.find(word) == stopwords.end()) {
			wordCounts[word]++;
		}
	
	}
	return wordCounts;
}

void output_word_counts(const std::map <std::string, int>& word_counts, std::ostream& out) {
	for (const auto& entry: word_counts) {
		out << entry.first << " " << entry.second << "\n";
	}
}

