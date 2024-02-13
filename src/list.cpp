#include <iostream>

#include <iosfwd>

using namespace std;

#include "list.hpp"

namespace list {

Node* from_string(const char* s) {
	if (!s || *s == '\0') return nullptr;
    Node* head = new Node{ *s, nullptr };
    Node* current = head;
    while (*++s) {
        current->next = new Node{ *s, nullptr };
        current = current->next;
    }
    return head;
}


void free(Node* head) {
	while (head != nullptr) {
		Node* temp = head;
		head = head -> next;
		delete temp;
	}
}


void print(std::ostream& out, Node* head) {
	for (Node* current = head; current != nullptr; current = current -> next) {
		out << current->data;
	}
}


Node* copy(Node* head) {
	if (!head) return nullptr;
	Node* newhead = new Node{head->data, nullptr};
	Node* newheadone = newhead;
	for (Node* current = head->next; current != nullptr; current = current-> next) {
		newheadone->next = new Node{ current-> data, nullptr};
		newheadone = newheadone->next;
	}
	return newhead;
}


int compare(Node* lhs, Node* rhs) {
	while (lhs != nullptr && rhs != nullptr) {
		if (lhs->data < rhs->data) return -1;
		if (lhs->data > rhs->data) return 1;
		lhs = lhs->next;
		rhs = rhs->next;
	}
	if (lhs == nullptr && rhs == nullptr) return 0;
	return (lhs == nullptr) ? -1 : 1;
}

int compare(Node* lhs, Node* rhs, int n) {
	if (lhs == nullptr && rhs == nullptr) return 0;
    if (lhs == nullptr) return -1;
    if (rhs == nullptr) return 1;
    for (int i = 0; i < n; ++i) {
        if (lhs == nullptr || rhs == nullptr) {
            return lhs == nullptr ? -1 : 1;
        }
        if (lhs->data < rhs->data) return -1;
        if (lhs->data > rhs->data) return 1;
        lhs = lhs->next;
        rhs = rhs->next;
    }
    return 0;
}


int length(Node* head) {
	int i = 0;
	for (Node* current = head; current != nullptr; current = current->next) {
		++i;
	}
	return i;
}

Node* reverse(Node* head) {
	Node* reverse = nullptr;
	Node* current = head;
	while (current != nullptr) {
		Node* next = current->next;
		current->next = reverse;
		reverse = current;
		current = next;
	}
	return reverse;
}

Node* append(Node* lhs, Node* rhs) {
	if (!lhs) return copy(rhs);
	Node* result = copy(lhs);
	Node* last = list::last(result);
	last->next = copy(rhs);
	return result;
}
	

int index(Node* head, Node* node) {
	int i = 0;
	for (Node* current = head; current != nullptr; current = current->next, ++i) {
		if (current == node) return i;
	}
	return -1;
}

Node* find_char(Node* head, char c) {
	for (Node* current = head; current != nullptr; current = current->next) {
		if (current->data == c) return current;
	}
	return nullptr;
}

Node* find_list(Node* haystack, Node* needle) {
	if (!needle) return haystack;
	for (Node* h = haystack; h != nullptr; h = h-> next) {
		Node* n = needle;
		Node* temp = h;
		while (temp && n && temp->data == n->data) {
			temp = temp->next;
			n = n->next;
		}
		if (!n) return h;
	}
	return nullptr;
}

Node* nth(Node* head, int n) {
	Node* current = head;
	for (int i = 0; i < n && current != nullptr; ++i) {
		current = current->next;
	}
	return current;
}

Node* last(Node* head) {
	if (!head) return nullptr;
	Node* current = head;
	while (current->next != nullptr) {
		current = current->next;
		}
	return current;
}

}

