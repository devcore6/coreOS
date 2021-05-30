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

/* 
 * synopsis:
 * 
 * int isalnum(int c);
 * int isalpha(int c);
 * int isblank(int c);
 * int iscntrl(int c);
 * int isdigit(int c);
 * int isgraph(int c);
 * int islower(int c);
 * int isprint(int c);
 * int ispunct(int c);
 * int isspace(int c);
 * int isupper(int c);
 * int isxdigit(int c);
 * int tolower(int c);
 * int toupper(int c);
 *
 */

#ifndef __LIBC_CTYPE_H
# define __LIBC_CTYPE_H
# ifdef __cplusplus
extern "C" {
# endif
extern int isalnum(int c);
extern int isalpha(int c);
extern int isblank(int c);
extern int iscntrl(int c);
extern int isdigit(int c);
extern int isgraph(int c);
extern int islower(int c);
extern int isprint(int c);
extern int ispunct(int c);
extern int isspace(int c);
extern int isupper(int c);
extern int isxdigit(int c);
extern int tolower(int c);
extern int toupper(int c);
# ifdef __cplusplus
}
# endif
#endif
