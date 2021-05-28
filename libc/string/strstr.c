#include <string.h>

const char *strstr(const char *str1, const char *str2) {
	for(size_t i = 0; i < strlen(str1) - strlen(str2); i++) {
		int failed = 0;
		for(size_t j = 0; j < strlen(str2); j++) {
			if(str1[i + j] != str2[j]) {
				failed = 1;
				break;
			}
		}
		if(!failed) return str1 + i;
	}
	return 0;
}
