#include <limits.h>
#include <stdbool.h>
#include <stdarg.h>
#include <stdio.h>
#include <string.h>
#include <stdint.h>

#ifdef __is_libk
# include <kernel/stdio.h>
#endif

static bool print(const char* data, size_t length) {
#ifdef __is_libk
	return _kprints((char*)data, length);
#else
	const unsigned char* bytes = (const unsigned char*) data;
	for(size_t i = 0; i < length; i++)
		if(putchar(bytes[i]) == EOF)
			return false;
	return true;
#endif
}

int printf(const char* restrict format, ...) {
	va_list parameters;
	va_start(parameters, format);

	int written = 0;

	while (*format != '\0') {
		size_t maxrem = INT_MAX - written;

		if (format[0] != '%' || format[1] == '%') {
			if (format[0] == '%')
				format++;
			size_t amount = 1;
			while (format[amount] && format[amount] != '%')
				amount++;
			if (maxrem < amount) {
				// TODO: Set errno to EOVERFLOW.
				return -1;
			}
			if (!print(format, amount))
				return -1;
			format += amount;
			written += amount;
			continue;
		}

		const char* format_begun_at = format++;

		if (*format == 'c') {
			format++;
			char c = (char) va_arg(parameters, int /* char promotes to int */);
			if (!maxrem) {
				// TODO: Set errno to EOVERFLOW.
				return -1;
			}
			if (!print(&c, sizeof(c)))
				return -1;
			written++;
		} else if (*format == 's') {
			format++;
			const char* str = va_arg(parameters, const char*);
			size_t len = strlen(str);
			if (maxrem < len) {
				// TODO: Set errno to EOVERFLOW.
				return -1;
			}
			if (!print(str, len))
				return -1;
			written += len;
		} else if(*format == 'i') {
			format++;
			int i = va_arg(parameters, int);
			if (!maxrem) {
				// TODO: Set errno to EOVERFLOW.
				return -1;
			}
			if(i == 0) {
				if(!print("0", sizeof(char))) return -1; else written++;
			} else {
				if(i < 0) {
					i *= -1;
					if(!print("-", sizeof(char))) return -1;
					written++;
				}
				char s[16] = { };
				int pos = 0;
				while(i > 0) {
					s[pos] = '0' + (i % 10);
					pos++;
					i -= i % 10;
					i /= 10;
				}
				for(int j = pos; j > 0; j--) {
					if (!print(s + j - 1, sizeof(char))) return -1;
					written++;
				}
			}
		} else if(*format == '0') {
			format++;
			int total_digits = *format - '0';
			format++;
			if(total_digits == 8 && *format == 'x') {
				format++;
				uint32_t i = (uint32_t)va_arg(parameters, int);
				if (!maxrem) {
					// TODO: Set errno to EOVERFLOW.
					return -1;
				}
				char s[9] = { '0', '0', '0', '0', '0', '0', '0', '0', 0 };
				int pos = 7;
				while(i > 0 && pos >= 0) {
					s[pos] = '0' + (i % 16);
					if(s[pos] > '9') s[pos] = s[pos] - '9' + 'a' - 1;
					pos--;
					i -= i % 16;
					i /= 16;
				}
				if(!print("0x", sizeof(char) * 2)) return -1;
				written += 2;
				if(!print(s, sizeof(char) * strlen(s))) return -1;
				written += strlen(s);
			} else if(total_digits == 4 && *format == 'x') {
				format++;
				uint32_t i = (uint32_t)va_arg(parameters, int);
				if (!maxrem) {
					// TODO: Set errno to EOVERFLOW.
					return -1;
				}
				char s[5] = { '0', '0', '0', '0', 0 };
				int pos = 3;
				while(i > 0 && pos > 0) {
					s[pos] = '0' + (i % 16);
					if(s[pos] > '9') s[pos] = s[pos] - '9' + 'a' - 1;
					pos--;
					i -= i % 16;
					i /= 16;
				}
				if(!print("0x", sizeof(char) * 2)) return -1;
				written += 2;
				if(!print(s, sizeof(char) * strlen(s))) return -1;
				written += strlen(s);
			} else {
				format = format_begun_at;
				size_t len = strlen(format);
				if (maxrem < len) {
					// TODO: Set errno to EOVERFLOW.
					return -1;
				}
				if (!print(format, len))
					return -1;
				written += len;
				format += len;
			}
		} else {
			format = format_begun_at;
			size_t len = strlen(format);
			if (maxrem < len) {
				// TODO: Set errno to EOVERFLOW.
				return -1;
			}
			if (!print(format, len))
				return -1;
			written += len;
			format += len;
		}
	}

	va_end(parameters);
	return written;
}
