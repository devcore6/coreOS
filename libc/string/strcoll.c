#include <string.h>

int strcoll(const char *str1, const char *str2) {
	return memcmp(str1, str2, strlen(str1) > strlen(str2) ? strlen(str2) : strlen(str1));
}
