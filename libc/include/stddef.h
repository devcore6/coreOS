/* 
 * The Koreh-v1 Project
 * Koreh-v1 C/C++ Compiler (ccxx)
 * 
 * Copyright (C) 2021, Bryan "/dev/core" M.
 * Licensed under the Mozilla Public License 2.0
 * https://www.mozilla.org/en-US/MPL/2.0/
 * 
 * Common language definitions as defined in
 * Clause 7.19 of the ISO-C2x working draft.
 * 
 * The ISO documents referenced by this compiler can be found at
 * http://open-std.org/JTC1/SC22/WG21/docs/papers/2021/n4885.pdf (C++23 Working Draft)
 * http://open-std.org/JTC1/SC22/WG14/www/docs/n2310.pdf (C2x Working Draft)
 * 
 */

/* 
 * synopsis:
 * 
 * #if __ARCH == 64
 * typedef long long ptrdiff_t;
 * typedef unsigned long long size_t;
 * #else
 * typedef long ptrdiff_t;
 * typedef unsigned long size_t;
 * #endif
 * typedef long double max_align_t;
 * 
 * #define NULL
 * #define offsetof(P, D)
 * 
 */

#ifndef __LIBC_STDDEF_H
# define __LIBC_STDDEF_H

# if __ARCH == 64
#  ifdef __LP64__
    typedef long ptrdiff_t;
    typedef unsigned long size_t;
#  else
    typedef long long ptrdiff_t;
    typedef unsigned long long size_t;
#  endif
# else
    typedef long ptrdiff_t;
    typedef unsigned long size_t;
# endif // __ARCH == 64

typedef long double max_align_t;

/*
 * Clause 17.2.3 paragraph 2 of the ISO-C++23 workign draft defines
 * NULL as a macro to a null pointer constant, while clause 7.19 paragraph
 * 3 defines NULL as an implementation-defined null-pointer constant.
 */
# ifdef NULL
#  undef NULL
# endif // NULL

# ifdef __cplusplus
#  define NULL nullptr
# else  // C++
#  define NULL ((void*)0)
# endif // C

/*
 * We define offsetoff through a builtin language extension in the compiler
 */
# define offsetof(P, D) \
	__builtin_offsetof(P, D)

#endif // __LIBC_STDDEF_H
