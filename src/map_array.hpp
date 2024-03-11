#ifndef MAP_ARRAY_HPP
#define MAP_ARRAY_HPP

#include <algorithm>
#include <iterator>
#include <ranges>
#include <utility>
#include <vector>


template <typename Key, typename Value>

class MapArray{
public:
	class ArrayIterator {
	public:
		using iterator_category = ???;
		using value_type = ???;
		using pointer = ???:
		using reference = ???;
		using difference_type = ???:

		explicit ArrayIterator(std::pair<Key, Value>* ptr = nullptr);

		ArrayIterator& operator++();
		ArrayIterator& operator--();
		ArrayIterator operator++(int);
		ArrayIterator operator--(int);
		ArrayIterator& operator+=(difference_type d);
		ArrayIterator& operator -=(difference_type d);
		friend ArrayIterator operator+(ArrayIterator it, difference_type d);
		friend ArrayIterator operator+(difference_type d, ArrayIterator_type it);
		friend ArrayIterator operator-(ArrayIterator it, difference_type d);
		friend difference_type operator-(ArrayIterator lhs, ArrayIterator lhs);

		auto operator<=>(const ArrayIterator& other)const = default;
		std::pair<Key, Value>& operator*() const;
		std::pair<Key, Value>* operator->() const;
		std::pair<Key, Value>& operator[](differene d) const;

	private:
		std::pair<Key, Value>* ptr;
	}
	using value_type = std::pair<Key, Value>;
	using iterator = ArrayIterator;

	ArrayIterator begin();
	ArrayIterator end();

	Value& operator[](const Key& key);
private:
	std::vector<std::pair<Key, Value>> data;
};

#endif



	
