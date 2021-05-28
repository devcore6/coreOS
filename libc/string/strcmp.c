#include <string.h>

int strcmp(const char *str1, const char *str2) {
	if(strlen(str1) != strlen(str2)) return -1;
	return memcmp((const void*)str1, (const void*)str2, strlen(str1));
}
