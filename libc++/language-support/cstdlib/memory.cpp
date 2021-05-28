/* 
 * The Koreh-v1 Project
 * Koreh-v1 C/C++ Compiler (ccxx)
 * 
 * Copyright (C) 2021, Bryan "/dev/core" M.
 * Licensed under the Mozilla Public License 2.0
 * https://www.mozilla.org/en-US/MPL/2.0/
 * 
 * Common language definitions as defined in
 * Clause 17.2 of the ISO-C++ 23 working draft.
 * 
 * Matching header <cstdlib>
 * 
 * The ISO documents referenced by this compiler can be found at
 * http://open-std.org/JTC1/SC22/WG21/docs/papers/2020/n4878.pdf (C++23 Working Draft)
 * http://open-std.org/JTC1/SC22/WG14/www/docs/n2310.pdf (C2x Working Draft)
 * 
 */

#include <cstdlib>

__BEGIN_NAMESPACE_STD

void* aligned_alloc(size_t alignment, size_t size) {
#ifdef __LIBCPP_IS_KERNEL
	
#else
	// todo: kernel call whenever kernel is a thing

#endif
}

void* calloc(size_t nmemb, size_t size) {
#ifdef __LIBCPP_IS_KERNEL
	
#else
	// todo: kernel call whenever kernel is a thing
	
#endif
}

__END_NAMESPACE_STD
