#ifndef _STRING_H
#define _STRING_H 1

#include <sys/cdefs.h>

#include <stddef.h>

#ifdef __cplusplus
extern "C" {
#endif

void* memcpy(void* s1, const void* s2, size_t n);
void* memmove(void* s1, const void* s2, size_t n);
char* strcpy(char* s1, const char* s2);
char* strncpy(char* s1, const char* s2, size_t n);
char* strcat(char* s1, const char* s2);
char* strncat(char* s1, const char* s2, size_t n);
int memcmp(const void* s1, const void* s2, size_t n);
int strcmp(const char* s1, const char* s2);
int strcoll(const char* s1, const char* s2);
int strncmp(const char* s1, const char* s2, size_t n);
size_t strxfrm(char* s1, const char* s2, size_t n);
const void* memchr(const void* s, int c, size_t n);
const char* strchr(const char* s, int c);
/*size_t strcspn(const char* s1, const char* s2);
const char* strpbrk(const char* s1, const char* s2);
const char* strrchr(const char* s, int c);
size_t strspn(const char* s1, const char* s2);*/
const char* strstr(const char* s1, const char* s2);
//char* strtok(char* s1, const char* s2);
void* memset(void* s, int c, size_t n);
//char* strerror(int errnum);
size_t strlen(const char* s);

#ifdef __cplusplus
}
#endif

#endif
