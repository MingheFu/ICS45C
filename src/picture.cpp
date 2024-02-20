#include "picture.hpp"
#include <iostream>
#include <utility>

Picture::Picture() : head(nullptr), tail(nullptr) {}

Picture::Picture(const Picture& other) : head(nullptr), tail(nullptr) {
	ListNode* current = other.head;
	while(current != nullptr) {
		this->add(*current->shape);
		current = current->next;
	}
}

Picture::Picture(Picture&& other) noexcept: head(other.head), tail(other.tail) {
	other.head = nullptr;
	other.tail = nullptr;
}

void Picture::swap(Picture& other) {
	std::swap(head, other.head);
	std::swap(tail, other.tail);
}
Picture& Picture::operator=(const Picture& other) {
	if (this != &other) {
		Picture temp(other);
		this->swap(temp);
	}
	return *this;
}

Picture& Picture::operator=(Picture&& other) noexcept {
	if (this != &other) {
        ListNode* current = head;
        while (current != nullptr) {
            ListNode* nextnode = current->next;
            delete current->shape;
            delete current;
            current = nextnode;
        }
        head = other.head;
        tail = other.tail;
        other.head = nullptr;
        other.tail = nullptr;
    }
    return *this;
}

void Picture::add(const Shape& shape) {
	Shape* newShape = shape.clone();
	ListNode* newNode = new ListNode{newShape, nullptr};
	if (head == nullptr) {
		head = newNode;
		tail = newNode;
	} else {
		tail->next = newNode;
		tail = newNode;
	}
}

void Picture::print_all(std::ostream& out) const {
	ListNode* current = head;
	while (current != nullptr) {
		current->shape->print(out);
		if (current->next != nullptr) {
            out << "***\n***\n***\n";
        }
		current = current->next;
	}

}

void Picture::draw_all(std::ostream& out) const {
	ListNode* current = head;
	while (current != nullptr) {
		current->shape->draw(out);
		current = current->next;
	}
}

double Picture::total_area() const {
	double area = 0.0;
	ListNode* current = head;
	while (current != nullptr) {
		area += current->shape->area();;
		current = current->next;
	}
	return area;
}

Picture::~Picture() {
	ListNode* current = head;
	while (current != nullptr) {
		ListNode* nextone = current->next;
		delete current->shape;
		delete current;
		current = nextone;
	}
}

