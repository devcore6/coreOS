#include <string.h>

char* strcat(char* s1, const char* s2) {
	memmove((void*)s1 + strlen(s1), (const void*)s2, strlen(s2));
	return s1;
}
