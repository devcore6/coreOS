/* 
 * The Koreh-v1 Project
 * Koreh-v1 C/C++ Compiler (ccxx)
 * 
 * Copyright (C) 2021, Bryan "/dev/core" M.
 * Licensed under the Mozilla Public License 2.0
 * https://www.mozilla.org/en-US/MPL/2.0/
 * 
 * Type size limits as defined in clause 7.10.
 * 
 * The ISO documents referenced by this compiler can be found at
 * http://open-std.org/JTC1/SC22/WG21/docs/papers/2021/n4885.pdf (C++23 Working Draft)
 * http://open-std.org/JTC1/SC22/WG14/www/docs/n2310.pdf (C2x Working Draft)
 * 
 */

/* 
 * synopsis:
 * 
 * #define CHAR_BIT 
 * #define SCHAR_MIN 
 * #define SCHAR_MAX 
 * #define UCHAR_MAX 
 * #define CHAR_MIN 
 * #define CHAR_MAX 
 * #define MB_LEN_MAX 
 * #define SHRT_MIN 
 * #define SHRT_MAX 
 * #define USHRT_MAX 
 * #define INT_MIN 
 * #define INT_MAX 
 * #define UINT_MAX 
 * #define LONG_MIN 
 * #define LONG_MAX 
 * #define ULONG_MAX 
 * #define LLONG_MIN 
 * #define LLONG_MAX 
 * #define ULLONG_MAX 
 * 
 */

#ifndef __LIBC_LIMITS_H
# define __LIBC_LIMITS_H

# define CHAR_BIT __CHAR_BIT__
# define SCHAR_MIN -127
# define SCHAR_MAX 127
# define UCHAR_MAX 255

# ifdef __CHAR_UNSIGNED__
#  define CHAR_MIN	0
#  define CHAR_MAX	UCHAR_MAX
# else
#  define CHAR_MIN	SCHAR_MIN
#  define CHAR_MAX	SCHAR_MAX
# endif

# define MB_LEN_MAX 16
# define SHRT_MIN -32767
# define SHRT_MAX 32767
# define USHRT_MAX 65535
# define INT_MIN -32767
# define INT_MAX 32767
# define UINT_MAX 65535
# define LONG_MIN -2147483647
# define LONG_MAX 2147483647
# define ULONG_MAX 4294967295
# define LLONG_MIN -9223372036854775807
# define LLONG_MAX 9223372036854775807
# define ULLONG_MAX 18446744073709551615

#endif // __LIBC_LIMITS_H
