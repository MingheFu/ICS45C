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
		using iterator_category = std::random_access_iterator_tag;
		using value_type = std::pair<Key, Value>;
		using pointer = value_type*;
		using reference = value_type&;
		using difference_type = std::ptrdiff_t;

		explicit ArrayIterator(std::pair<Key, Value>* ptr = nullptr) : ptr(ptr) {}

		

		ArrayIterator& operator++() {
			++ptr;
			return *this;
		}
		ArrayIterator& operator--() {
			--ptr;
			return *this;
		}

		ArrayIterator operator++(int) {
			ArrayIterator temp = *this;
            ++(*this);
            return temp;
		}
		ArrayIterator operator--(int) {
			ArrayIterator temp = *this;
            --(*this);
            return temp;
		}
		ArrayIterator& operator+=(difference_type d) {
			ptr += d;
            return *this;
		}
		ArrayIterator& operator -=(difference_type d) {
			ptr -= d;
            return *this;
		}
		//std::pair<Key, Value>*  get_ptr() const { return ptr; }
		friend ArrayIterator operator+(ArrayIterator it, difference_type d) {
			return ArrayIterator(it.ptr + d);
		}
		friend ArrayIterator operator+(difference_type d, ArrayIterator it) {
			return ArrayIterator(it.ptr + d);
		}
		friend ArrayIterator operator-(ArrayIterator it, difference_type d) {
			return ArrayIterator(it.ptr - d);
		}
		friend difference_type operator-(ArrayIterator lhs, ArrayIterator rhs) {
			return lhs.ptr - rhs.ptr;
		}

		auto operator<=>(const ArrayIterator& other)const = default;
		std::pair<Key, Value>& operator*() const {return *ptr;}
		std::pair<Key, Value>* operator->() const {return ptr;}
		std::pair<Key, Value>& operator[](difference_type d) const {
			return *(ptr+d);
		}

	private:
		std::pair<Key, Value>* ptr;
	};
	using value_type = std::pair<Key, Value>;
	using iterator = ArrayIterator;

	ArrayIterator begin() {
		return ArrayIterator(data.data());
	}
	ArrayIterator end() {
		return ArrayIterator(data.data() + data.size());
	}

	Value& operator[](const Key& key) {
		auto std_end_it = data.end();
		auto it = std::lower_bound(data.begin(), std_end_it, key,
        [](const value_type& a, const Key& b) {
            return a.first < b;
        });
    if (it != std_end_it && it->first == key) {
        return it->second;
    }
   
    auto inserted = data.insert(it, std::make_pair(key, Value{}));
    return inserted->second;
	}
private:
	std::vector<std::pair<Key, Value>> data;
};

#endif
	
