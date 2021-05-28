#include <cstring>

__BEGIN_NAMESPACE_STD
	void* memchr(void* s, int c, size_t n) {
		for(size_t i = 0; i < n; i++) if(((char*)s)[i] == c) return s + i;
		return 0;
	}
__END_NAMESPACE_STD
