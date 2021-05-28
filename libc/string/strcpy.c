#include <string.h>

char *strcpy(char *str1, const char *str2) {
	(char*)memcpy((void*)str1, (const void*)str2, strlen(str2));
	str1[strlen(str2)] = 0;
	return str1;
}
