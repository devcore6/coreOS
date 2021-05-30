/* 
 * The Koreh-v1 Project
 * Koreh-v1 C/C++ Compiler (ccxx)
 * 
 * Copyright (C) 2021, Bryan "/dev/core" M.
 * Licensed under the Mozilla Public License 2.0
 * https://www.mozilla.org/en-US/MPL/2.0/
 * 
 * Integer types definitions as defined in
 * Clause 7.20 of the ISO-C2x working draft.
 * 
 * The ISO documents referenced by this compiler can be found at
 * http://open-std.org/JTC1/SC22/WG21/docs/papers/2021/n4885.pdf (C++23 Working Draft)
 * http://open-std.org/JTC1/SC22/WG14/www/docs/n2310.pdf (C2x Working Draft)
 * 
 */

#ifndef __LIBC_STDINT_H
# define __LIBC_STDINT_H
typedef char int8_t;
typedef short int16_t;
# ifdef __LP64__
    typedef int int32_t;
    typedef long int64_t;
# else
    typedef long int32_t;
    typedef long long int64_t;
# endif // __LP64__

typedef char int_fast8_t;
typedef short int_fast16_t;
# ifdef __LP64__
    typedef int int_fast32_t;
    typedef long int_fast64_t;
# else
    typedef long int_fast32_t;
    typedef long long int_fast64_t;
# endif // __LP64__

typedef char int_least8_t;
typedef short int_least16_t;
# ifdef __LP64__
    typedef int int_least32_t;
    typedef long int_least64_t;
# else
    typedef long int_least32_t;
    typedef long long int_least64_t;
# endif // __LP64__

# ifdef __LP64__
    typedef long intmax_t;
    typedef long intptr_t;
# else
    typedef long long intmax_t;
    typedef long long intptr_t;
# endif // __LP64__

typedef unsigned char uint8_t;
typedef unsigned short uint16_t;
# ifdef __LP64__
    typedef unsigned int uint32_t;
    typedef unsigned long uint64_t;
# else
    typedef unsigned long uint32_t;
    typedef unsigned long long uint64_t;
# endif // __LP64__

typedef unsigned char uint_fast8_t;
typedef unsigned short uint_fast16_t;
# ifdef __LP64__
    typedef unsigned int uint_fast32_t;
    typedef unsigned long uint_fast64_t;
# else
    typedef unsigned long uint_fast32_t;
    typedef unsigned long long uint_fast64_t;
# endif // __LP64__

typedef unsigned char uint_least8_t;
typedef unsigned short uint_least16_t;
# ifdef __LP64__
    typedef unsigned int uint_least32_t;
    typedef unsigned long uint_least64_t;
# else
    typedef unsigned long uint_least32_t;
    typedef unsigned long long uint_least64_t;
# endif // __LP64__

# ifdef __LP64__
    typedef unsigned long uintmax_t;
    typedef unsigned long uintptr_t;
# else
    typedef unsigned long long uintmax_t;
    typedef unsigned long long uintptr_t;
# endif // __LP64__

# define INT8_MIN -128
# define INT8_MAX 127
# define UINT8_MAX 255

# define INT16_MIN -32768
# define INT16_MAX 32767
# define UINT16_MAX 65535

# define INT32_MIN -2147483648
# define INT32_MAX 2147483647
# define UINT32_MAX 4294967295

# define INT64_MIN -9223372036854775808
# define INT64_MAX 9223372036854775807
# define UINT64_MAX 18446744073709551615u

# define INT_LEAST8_MIN -127
# define INT_LEAST8_MAX 127
# define UINT_LEAST8_MAX 255

# define INT_LEAST16_MIN -32767
# define INT_LEAST16_MAX 32767
# define UINT_LEAST16_MAX 65535

# define INT_LEAST32_MIN -2147483647
# define INT_LEAST32_MAX 2147483647
# define UINT_LEAST32_MAX 4294967295

# define INT_LEAST64_MIN -9223372036854775807
# define INT_LEAST64_MAX 9223372036854775807
# define UINT_LEAST64_MAX 18446744073709551615u

# define INT_FAST8_MIN -127
# define INT_FAST8_MAX 127
# define UINT_FAST8_MAX 255

# define INT_FAST16_MIN -32767
# define INT_FAST16_MAX 32767
# define UINT_FAST16_MAX 65535

# define INT_FAST32_MIN -2147483647
# define INT_FAST32_MAX 2147483647
# define UINT_FAST32_MAX 4294967295

# define INT_FAST64_MIN -9223372036854775807
# define INT_FAST64_MAX 9223372036854775807
# define UINT_FAST64_MAX 18446744073709551615u

# define INTPTR_MIN INT64_MIN
# define INTPTR_MAX INT64_MAX
# define UINTPTR_MAX UINT64_MAX

# define INTMAX_MIN INT64_MIN
# define INTMAX_MAX INT64_MAX
# define UINTMAX_MAX UINT64_MAX

#endif // __LIBC_STDINT_H