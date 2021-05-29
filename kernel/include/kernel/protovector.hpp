#ifndef __KERNEL_PROTOVECTOR_HPP
# define __KERNEL_PROTOVECTOR_HPP
# include <cstddef>
# include <cstring>
# include <cstdlib>

template<class T>
class protovector {						// Temporary oversimplified implementation of std::vector, because they're useful for so many things
private:
	size_t _alloc_size = 4096;
	size_t _max_size = 0;
	size_t _size = 0;
	T* _data = nullptr;
	T noelem = T();						// Need this as we don't have exceptions yet

public:
	protovector() = default;
	protovector(const protovector& rhs) {			// Copy constructor
		_size = rhs._size;
		_max_size = _size;
		if(rhs._data != nullptr) {		
			_data = (T*)malloc(sizeof(T) * _max_size);
			std::memcpy(_data, rhs._data, _size * sizeof(T));
		}
	}

	T* data() { return _data; }
	size_t size() { return _size; }
	size_t max_size() { return _max_size; }
	size_t alloc_size() { return _alloc_size; }
	void alloc_size(size_t size) { _alloc_size = size; }

	void push_back(T s) {
		if(_size == _max_size) {		// If size == max_size (meaning we have filled the whole allocated memory)
										// We then need to resize the array, which means we need to make a new
										// Buffer, copy the data over and then delete the original buffer
			if(_data) {
				_max_size += _alloc_size;
				_data = (T*)realloc(_data, sizeof(T) * _max_size);
				std::memset(&_data[_size], 0, _alloc_size * sizeof(T));
			} else {
				_max_size = _alloc_size;
				_data = (T*)malloc(sizeof(T) * _max_size);
				std::memset(_data, 0, _alloc_size * sizeof(T));
			}
			// if(_data == nullptr) { throw std::bad_alloc(""); }
		}
		_data[_size] = s;
		_size++;
	}

	void pop_back() {
		if(_size > 0) {
			_size--;
			_data[_size] = T();
			if(_size == 0) {			// Deleting the allocated buffer if we just deleted the last element. This
										// Is optional, but I thought it was worth doing for the memory savings
										// Even though it comes at a slight performance cost having to reallocate
										// The memory later on.
				_max_size = 0;
				free(_data);
				_data = nullptr;
			}
		}
	}

	void clear() {
		free(_data);
		_data = nullptr;
		_size = _max_size = 0;
	}

	void erase(size_t i) noexcept(false) {
		if(i >= _size) { /* throw std::out_of_range("out of bounds"); */ return; }
		for(size_t j = i; j < _size - 1; j++) _data[j] = _data[j + 1];
		_size--;
		_data[_size] = T();
		if(_size == 0) {			// Deleting the allocated buffer if we just deleted the last element. This
									// Is optional, but I thought it was worth doing for the memory savings
									// Even though it comes at a slight performance cost having to reallocate
									// The memory later on.
			_max_size = 0;
			free(_data);
			_data = nullptr;
		}
	}

	T& operator[](size_t i) noexcept(false) {
		if(i >= _size) { /* throw std::out_of_range("out of bounds"); */ return noelem; }
		return _data[i];
	}

	T& at(size_t i) noexcept(false) {
		if(i >= _size) { /* throw std::out_of_range("out of bounds"); */ return noelem; }
		return _data[i];
	}

	~protovector() {
		if(_data != nullptr) free(_data);
	}
};
#endif
