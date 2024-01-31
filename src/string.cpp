#include <iostream>


using namespace std;

#include "string.hpp"

String::String(const char *s) {
	if (strlen(s) >= MAXLEN) {
		std::cout << "ERROR: String Capacity Exceeded" << std::endl;
		s = "";
	}
	strcpy(buf, s);
}

String::String(const String &s) {
	strcpy(buf, s.buf);
}

String &String::operator=(const String &s) {
	if (this != &s) {
		strcpy(buf, s.buf);
	}
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


int String:: size() const {
	return static_cast<int>(strlen(buf));
}

String String::reverse() const{
	String reversed;
	reverse_cpy(reversed.buf, buf);
	return reversed;
}

int String::indexOf(char c) const{
	const char *result = strchr(buf, c);
	if (result) {
		return static_cast<int>(result - buf);
	} else {
		return -1;
	}
}

int String::indexOf(const String &s) const{
	const char *result = strstr(buf, s.buf);
	if (result) {
		return static_cast<int>(result - buf);
	} else {
		return -1;
	}
}

bool String::operator==(const String &s) const{
	return strcmp(buf, s.buf) == 0;
}

bool String::operator!=(const String &s) const {
	return strcmp(buf, s.buf) != 0;
}

bool String::operator>(const String &s) const {
	return strcmp(buf, s.buf) > 0;
}

bool String::operator<(const String &s) const {
	return strcmp(buf, s.buf) < 0;
}

bool String::operator<=(const String &s) const {
	return strcmp(buf, s.buf) <= 0;
}

bool String::operator>=(const String &s) const {
	return strcmp(buf, s.buf) >= 0;
}

String String::operator+(const String &s) const {
	if (size() + s.size() >= MAXLEN) {
		std::cout << "ERROR: String Capacity Exceeded" << std::endl;
		return String();
	} 
	String result;
	strcpy(result.buf, buf);
	strcat(result.buf, s.buf);
	return result;
}

String &String::operator+=(const String &s) {
	size_t newSize = strlen(buf) + strlen(s.buf);
	if (newSize >= MAXLEN) {
		std::cout << "ERROR: String Capacity Exceeded" << std::endl;
		return *this;
	} 
	strncat(buf, s.buf, MAXLEN - strlen(buf)-1);
	return *this;
}

String::~String() {
	std::cout << "String " << buf << " is destructing" << std::endl;
}

void String::print(std::ostream &out) const {
	out << buf;
}

void String::read(std::istream &in) {
	in >> buf;
	if (size() >= MAXLEN){
		std::cout << "ERROR: String Capacity Exceeded" << std::endl;
		buf[0] = '\0';
	} 
}

int String::strlen(const char *s) {
	int len = 0;
	while (s[len] != '\0') {
		++len;
	}
	return len;
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
	 while (i < n && src[i] != '\0') {
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
    return (*str == c) ? str : nullptr;
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

std::ostream &operator<<(std::ostream &out, const String &s) {
	s.print(out);
	return out;
}

std::istream &operator>>(std::istream &in, String &s) {
	s.read(in);
	return in;
}

