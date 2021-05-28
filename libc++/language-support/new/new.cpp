#include <new>
#include <cstdlib>

__HAS_NODISCARD__ void* operator new(std::size_t size) {
	if(size == 0) size = 1;
	void *p = malloc(size);
	//if(p == nullptr) throw std::bad_alloc();
	return p;
}

__HAS_NODISCARD__ void* operator new[](std::size_t size) {
	if(size == 0) size = 1;
	void *p = malloc(size);
	//if(p == nullptr) throw std::bad_alloc();
	return p;
}
