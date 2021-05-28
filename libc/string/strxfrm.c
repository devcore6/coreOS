#include <string.h>

size_t strxfrm(char* s1, const char* s2, size_t n) {
	memcpy((void*)s1, (const void*)s2, n);
	return n;
}
