/* 
 * The Koreh-v1 Project
 * Koreh-v1 C/C++ Compiler (ccxx)
 * 
 * Copyright (C) 2021, Bryan "/dev/core" M.
 * Licensed under the Mozilla Public License 2.0
 * https://www.mozilla.org/en-US/MPL/2.0/
 * 
 * Character handling as defined in
 * Clause 7.4 of the ISO-C2x working draft.
 * 
 * The ISO documents referenced by this compiler can be found at
 * http://open-std.org/JTC1/SC22/WG21/docs/papers/2021/n4885.pdf (C++23 Working Draft)
 * http://open-std.org/JTC1/SC22/WG14/www/docs/n2310.pdf (C2x Working Draft)
 * 
 */

#include <ctype.h>

int isalnum(int c) {
	return isalpha(c) || isdigit(c);
}

int isalpha(int c) {
	return tolower(c) >= 'a' && tolower(c) <= 'z';
}

int isblank(int c) {
	return c == '\t' || c == ' ';
}

int iscntrl(int c) {
	return (c >= 0x00 && c <= 0x1f) || c == 0x7f;
}

int isdigit(int c) {
	return c >= '0' && c <= '9';
}

int isgraph(int c) {
	return isprint(c) && c != ' ';
}

int islower(int c) {
	return c >= 'a' && c <= 'z';
}

int isprint(int c) {
	return !iscntrl(c);
}

int ispunct(int c) {
	return isgraph(c) && !isalnum(c);
}

int isspace(int c) {
	return c == ' ' || c == '\t' || c == '\n' || c == '\v' || c == '\f' || c == '\r';
}

int isupper(int c) {
	return c >= 'A' && c <= 'Z';
}

int isxdigit(int c) {
	return isdigit(c) || (tolower(c) >= 'a' && tolower(c) <= 'f'); 
}

int tolower(int c) {
	if(!isalpha(c) || islower(c)) return c;
	return c - 'A' + 'a';
}

int toupper(int c) {
	if(!isalpha(c) || isupper(c)) return c;
	return c - 'a' + 'A';
}
