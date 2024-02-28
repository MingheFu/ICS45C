#ifndef ARRAY_HPP
#define ARRAY_HPP

#include <iomanip>
#include <iostream>
#include <sstream>
#include <utility>

template <typename T>
class Array {
public:
	explicit Array(int size = 0) : len(size), buf(size ? new T[size]: nullptr) {}

	Array(const Array& other) :len(other.len), buf(other.len ? new T[other.len] : nullptr) {
		for (int i = 0; i < len; ++i) {
			buf[i] = other.buf[i];
		}
	}

	Array(Array&& other) noexcept : len(other.len), buf(other.buf) {
		other.len = 0;
		other.buf = nullptr;
	}

	friend void swap(Array<T>& lhs, Array<T>& rhs) noexcept {
		std::swap(lhs.len, rhs.len);
		std::swap(lhs.buf, rhs.buf);
	}

	Array& operator=(Array&& other) noexcept {
		if (this!= &other) {
			delete[] buf;
			len = other.len;
			buf = other.buf;
			other.len = 0;
			other.buf = nullptr;
		}
		return *this;
	}

	Array& operator=(const Array& other) {
        if (this != &other) {
            T* new_buf = other.len ? new T[other.len] : nullptr;
            for (int i = 0; i < other.len; ++i) {
                new_buf[i] = other.buf[i];
            }
            delete[] buf;
            len = other.len;
            buf = new_buf;
        }
        return *this;
    }

	T& operator[](int index) {
        if (in_bounds(index)) {
            return buf[index];
        } else {
			throw std::string("Exception operator[](" + std::to_string(index) + ") Out Of Range");
    	}
	}
	const T& operator[](int index) const {
        if (in_bounds(index)) {
            return buf[index];
        } else {
			throw std::string("Exception operator[](" + std::to_string(index) + ") Out Of Range");
		}
    }

	int length() const {
		return len;
	}


	~Array() {
        delete[] buf;
    }

	void fill(const T& value) {
		for (int i = 0; i < len; ++i) {
			buf[i] = value;
		}
	}
			

	template <typename Fn>
	void fill_with_fn(Fn fn) {
		for (int i = 0; i < len; ++i) {
			buf[i] = fn(i);
		}
	}

private:
	int len;
	T* buf;

	bool in_bounds(int index) const {
		return index >= 0 && index < len;
	}
};

template <typename T>
std::ostream& operator<<(std::ostream& out, const Array<T>& array) {
     std::stringstream temp;
    temp << std::fixed << std::setprecision(2) << std::right;   
    for (int i = 0; i < array.length(); ++i) {
        temp << std::setw(8) << array[i] << ' ';
  }
    out << temp.str();
    return out;
}



template <typename T>
std::istream& operator>>(std::istream& in, Array<T>& array) {
    for (int i = 0; i < array.length(); ++i) {
        in >> array[i];
    }
    return in;
}

#endif

