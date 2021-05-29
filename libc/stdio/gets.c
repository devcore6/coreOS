#include <stdio.h>
#include <stddef.h>
#include <stdbool.h>

char *gets(char *str) {
	size_t pos = 0;
	while(true) {
		char c = getchar();
		if(c == '\n') {
			str[pos] = 0;
			return str;
		}
		str[pos] = c;
		pos++;
	}
}
