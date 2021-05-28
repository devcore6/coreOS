#include <new>
#include <cstdlib>

void operator delete(void* ptr) __HAS_NOEXCEPT__ {
	free(ptr);
}

void operator delete[](void* ptr) __HAS_NOEXCEPT__ {
	free(ptr);
}

void operator delete(void* ptr, std::size_t size) __HAS_NOEXCEPT__ {
	free(ptr);
}

void operator delete[](void* ptr, std::size_t size) __HAS_NOEXCEPT__ {
	free(ptr);
}
