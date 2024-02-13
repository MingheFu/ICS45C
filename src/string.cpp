#include <iostream>

#include <utility>

#include <compare>


#include "string.hpp"
#include "list.hpp"

using namespace list;

String::String(const char *s) {
	head = from_string(s);
}

String::String(const String &s) {
	head = copy(s.head);
}

String::String(list::Node* first): head(first){
}
	

String::String(String &&s) noexcept : head(s.head) {
	s.head = nullptr;
}

void String::swap(String &s) {
	std::swap(head, s.head);
}

String &String::operator=(const String &s) {
	if (this != &s) {
		String temp(s);
		swap(temp);
	}
	return *this;
}

String &String::operator=(String &&s) noexcept {
	swap(s);
	return *this;
}
	
bool String::in_bounds(int index) const {
	return index >= 0 && index < size();
}

char String::operator[](int index) const {
	if (in_bounds(index)) {
    	Node* current = head;
    	for (int i = 0; i < index && current != nullptr; i++) {
        		current = current->next;
    	}
    	if (current) {
        	return current->data;
    	}
    }
    return '\0';
}

int String::size() const {
	return length(head);
}

String String::reverse() const {
	Node* reversed = list::reverse(head);
    String reversedString(reversed);
    free(reversed);
    return reversedString;
}

int String::indexOf(char c) const {
	Node* found = find_char(head, c);
    if (!found) return -1;
    int index = 0;
    for (Node* current = head; current != found; current = current->next, ++index);
    return index;
}

int String::indexOf(const String &s) const {
	Node* found = find_list(head, s.head);
    if (!found) return -1;
    int index = 0;
    for (Node* current = head; current != found; current = current->next, ++index);
    return index;
}

bool String::operator==(const String &s) const {
    return compare(head, s.head) == 0;
}

std::strong_ordering String::operator<=>(const String &s) const {
	return compare(head, s.head) <=> 0;
}

String String::operator+(const String &s) const {
	Node* concatenate = append(head, s.head);
    String concatenatedString(concatenate);
    free(concatenate);
    return concatenatedString;
}

String &String::operator+=(const String &s) {
	Node* concatenate = append(head, s.head);
    free(head);
    head = concatenate;
    return *this;
}

void String::print(std::ostream &out) const {
	for (Node* current = head; current != nullptr; current = current->next) {
        out << current->data;
    }
}
	

void String::read(std::istream &in) {
	std::string temp;
    if (in >> temp) {
        list::free(head);
        head = list::from_string(temp.c_str());
    }
}

String::~String() {
	free(head);
}

std::ostream &operator<<(std::ostream &out, const String &s) {
	s.print(out);
    return out;
}


std::istream &operator>>(std::istream &in, String &s) {
	s.read(in);
	return in;
}

