#include <string.h>

const void *memchr(const void *str, int character, size_t n) {
	for(size_t i = 0; i < n; i++) if(((const char*)str)[i] == character) return str + i;
	return 0;
}
