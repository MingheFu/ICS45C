
#ifndef SET_LIST_HPP
#define SET_LIST_HPP

#include <algorithm>
#include <functional>
#include <iterator>
#include <memory>
#include <ranges>

template <typename T>
class SetList {
	struct ListNode {
		T data;
		std::shared_ptr<ListNode> next;
		ListNode(const T& data) : data(data), next(nullptr) {}
        ListNode() = default;
	};

public:
	class ListIterator {
		public:
			using iterator_category = std::forward_iterator_tag;
		    using value_type = T;
			using difference_type = std::ptrdiff_t;
			using pointer = T*;
			using reference = T&;

			explicit ListIterator(std::shared_ptr<ListNode> ptr = nullptr) : ptr(ptr) {}
	
			ListIterator& operator++() {
				if (ptr) ptr = ptr->next;
				return *this;
			}
			ListIterator operator++(int) {
				ListIterator temp = *this;
    			++(*this);
    			return temp;
			}

			T& operator*() const {
				return ptr->data;
			}
			T* operator->() const {
				return &(ptr->data);
			}
			bool operator==(const ListIterator& other) const = default;
			//bool operator!=(const ListIterator& other) const {
            //	return ptr != other.ptr;
        	//}

		private:
			std::shared_ptr<ListNode> ptr;
	};
	using value_type = T;
	using iterator = ListIterator;

	SetList() = default;

	template <std::ranges::input_range Rng>
	explicit SetList(Rng&& rng) {
		std::ranges::for_each(std::forward<Rng>(rng),std::bind_front(&SetList::insert,this));
	}

	ListIterator begin() {
	return ListIterator(head);
	}	
	ListIterator end() {
		return ListIterator(nullptr);
	}
	bool contains(const T& value) {
		for (std::shared_ptr<ListNode> current = head; current != nullptr; 
		current = current->next) {
        if (current->data == value) {
            return true;
        }
    }
    	return false;
	}
	ListIterator insert(T value) {
		for (auto current = head; current != nullptr; current = current->next) {
        if (current->data == value) {
            return ListIterator(current);
        }
    }
    	//auto newNode = std::make_shared<ListNode>(value, head);
    	//head = newNode;
    	//return ListIterator(newNode);
		//std::shared_ptr<ListNode> newNode = std::make_shared<ListNode>();
		auto newNode = std::make_shared<ListNode>(value);
    	newNode->data = value;
    	newNode->next = head;
    	head = newNode;
		return ListIterator(newNode);
	}
private:
	std::shared_ptr<ListNode> head = nullptr;
};

#endif

