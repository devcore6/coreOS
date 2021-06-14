/* 
 * The Koreh-v1 Project
 * Koreh-v1 C/C++ Compiler (ccxx)
 * 
 * Copyright (C) 2021, Bryan "/dev/core" M.
 * Licensed under the Mozilla Public License 2.0
 * https://www.mozilla.org/en-US/MPL/2.0/
 * 
 * Boolean type and values
 * Clause 7.18 of the ISO-C2x working draft.
 * 
 * The ISO documents referenced by this compiler can be found at
 * http://open-std.org/JTC1/SC22/WG21/docs/papers/2021/n4885.pdf (C++23 Working Draft)
 * http://open-std.org/JTC1/SC22/WG14/www/docs/n2310.pdf (C2x Working Draft)
 * 
 */

/* 
 * synopsis:
 * 
 * #define bool _Bool.
 * #define true 1
 * #define false 0
 * #define __bool_true_false_are_defined 1
 *
 */

#ifndef __bool_true_false_are_defined
typedef _Bool bool;
# define true 1
# define false 0
# define __bool_true_false_are_defined 1
#endif
