#include <string.h>

const char *strchr(const char *str, int character) {
	return (const char *)memchr((const void *)str, character, strlen(str));
}
