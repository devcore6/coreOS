#include <string.h>

char* strncat(char* s1, const char* s2, size_t n) {
	memmove((void*)s1 + strlen(s1), (const void*)s2, n - strlen(s1));
	return s1;
}
