#include <iostream>

#include <utility>

using namespace std;

#include "string.hpp"

String::String(const char *s) {
	buf = new char[strlen(s) + 1];
	strcpy(buf, s);
}

String::String(const String &s) {
	 buf = new char[strlen(s.buf) + 1];
	 strcpy(buf, s.buf);
}

String::String(int length) {
	buf = new char[length + 1];
	buf[0] = '\0';
}

void String::swap(String &s) {
	std::swap(buf, s.buf);
}


String &String::operator=(String s) {
	swap(s);
	return *this;
}


char &String::operator[](int index) {
	if (in_bounds(index)) {
		return buf[index];
		} else {
			std::cout << "ERROR: Index Out Of Bounds" << std::endl;
			return buf[0];
		}
}
 

const char &String::operator[](int index) const {
	if (in_bounds(index)) {
		 return buf[index];
	} else {
		 std::cout << "ERROR: Index Out Of Bounds" << std::endl;
		 return buf[0];
	}
}

int String::size() const {
	return static_cast<int>(strlen(buf));
}

String String:: reverse() const {
	String reversed(size());
	reverse_cpy(reversed.buf, buf);
	return reversed;
}

int String::indexOf(char c) const {
	const char* result = strchr(buf, c);
	 if (result) {
	 	return static_cast<int>(result - buf);
	} else {
		return -1;
	}
}

int String::indexOf(String &s) const {
	const char* result = strstr(buf, s.buf);
	if (result) {
		return static_cast<int>(result - buf);
	} else {
		return -1;
	}
}

bool String::operator==(String s) const {
	return strcmp(buf, s.buf) == 0;
}

bool String::operator!=(String s) const {
	return strcmp(buf, s.buf) != 0;
}

bool String::operator>(String s) const {
	return strcmp(buf, s.buf) > 0;
}

bool String::operator<(String s) const {
	return strcmp(buf, s.buf) < 0;
}

bool String::operator<=(String s) const {
	return strcmp(buf, s.buf) <= 0;
}

bool String::operator>=(String s) const {
	return strcmp(buf, s.buf) >= 0;
}

String String::operator+(String &s) const {
	String result(size() + s.size());
	strcpy(result.buf, buf);
	strcat(result.buf, s.buf);
	return result;
}


String &String::operator+=(String &s) {
	int newSize = size() + s.size();
	char* tempBuf = new char[newSize + 1];
	strcpy(tempBuf, buf);
	strcat(tempBuf, s.buf);
	delete[] buf;
	buf = tempBuf;
	return *this;
}


void String::print(std::ostream &out) const {
	out << buf;
}


void String::read(std::istream &in) {
	delete[] buf;
	String temp;
	in >> temp;
	buf = strdup(temp.buf);
}

int String::strlen(const char *s) {
	int i = 0;
	while(s[i] != '\0') {
		++i;
	}
	return i;
}

String::~String() {
	delete[] buf;
}


char *String::strcpy(char *dest, const char *src) {
	int i = 0;
	while (src[i] != '\0'){
	dest[i] = src[i];
	++i;
	}
	dest[i] = '\0';
	return dest;
}

char *String::strdup(const char *src) {
	if (src ==nullptr) {
		return nullptr;
	}
	int src_len = strlen(src);
	char *duplicate = new char[src_len + 1];
	strcpy(duplicate, src);
	return duplicate;
}


char *String::strncpy(char *dest, const char *src, int n) {
	int i = 0;
	for (;i < n && src[i] != '\0'; ++i) {
		dest[i] = src[i];
	}
	dest[i] = '\0';
	return dest;
}

char *String::strcat(char *dest, const char *src) {
	int dest_len = strlen(dest);
	int i = 0;
	while (src[i] != '\0') {
		dest[dest_len + i] = src[i];
		++i;
	}
	dest[dest_len + i] = '\0';
	return dest;
}

char *String::strncat(char *dest, const char *src, int n) {
	int dest_len = strlen(dest);
	int i = 0;
	while(i < n && src[i] != '\0') {
		dest[dest_len + i] = src[i];
		++i;
	}
	dest[dest_len + i] = '\0';
	return dest;
}

int String::strcmp(const char *left, const char *right) {
	int i = 0;
	while (left[i] != '\0' && right[i] != '\0' && left[i] == right[i]) {
		++i;
	}
	return left[i] - right[i];
}

int String::strncmp(const char *left, const char *right, int n) {
	int i = 0;
	while (i < n && left[i] != '\0' && right[i] != '\0' && left[i] == right[i]) {
		++i;
	}
	return i == n ? 0 : left[i] - right[i];
}

void String::reverse_cpy(char *dest, const char *src) {
	int src_len = strlen(src);
	for (int i = 0; i < src_len; ++i) {
		dest[i] = src[src_len - i - 1];
	}
	dest[src_len] = '\0';
}

const char *String::strchr(const char *str, char c) {
	while (*str != '\0' && *str != c) {
		++str;
	}
	return (*str == c) ? str: nullptr;
}

const char *String::strstr(const char *haystack, const char *needle) {
	while (*haystack != '\0') {
		const char *haystack_ptr = haystack;
		const char *needle_ptr = needle;
		while (*haystack_ptr != '\0' && *needle_ptr != '\0' && *haystack_ptr == *needle_ptr) {
			++haystack_ptr;
			++needle_ptr;
		}
		if (*needle_ptr == '\0') {
			return haystack;
		}
		++haystack;
	}
	return nullptr;
}
std::ostream &operator<<(std::ostream &out, String s) {
	s.print(out);
	return out;
}

std::istream &operator>>(std::istream &in, String &s) {
	s.read(in);
	return in;
}

	
