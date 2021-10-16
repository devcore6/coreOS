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
 * http://open-std.org/JTC1/SC22/WG21/docs/papers/2021/n4885.pdf (C++23 Working Draft)
 * http://open-std.org/JTC1/SC22/WG14/www/docs/n2310.pdf (C2x Working Draft)
 * 
 */

#include <cstdlib>

__BEGIN_NAMESPACE_STD

#ifndef __LIBCPP_IS_KERNEL
	
/* 
 * Perhaps not the best implementation, however it will be improved
 * In the future.
 */
	void (*_atexit)()[32] = { nullptr; }

#endif

	__HAS_NORETURN__ void abort() __HAS_NOEXCEPT__ {
#ifndef __LIBCPP_IS_KERNEL
		/* 
		 * todo: quit
		 */
#endif
	}

	int atexit(void (*func)()) __HAS_NOEXCEPT__ {
#ifndef __LIBCPP_IS_KERNEL
		for(auto a : _atexit)
			if(a == nullptr) {
                atexit0 = func;
                return 0;
            }
#endif
		return -1;
	}
	int at_quick_exit(void (*func)()) __HAS_NOEXCEPT__ { return atexit(func); }

	__HAS_NORETURN__ void exit(int status) {
#ifndef __LIBCPP_IS_KERNEL
		for(auto a : _atexit)
            if(a != nullptr)
                a();
		/*
		 * todo: quit
		 */
#endif
	}

	__HAS_NORETURN__ void _Exit(int status) __HAS_NOEXCEPT__ { exit(status); }
	__HAS_NORETURN__ void quick_exit(int status) __HAS_NOEXCEPT__ { exit(status); }

__END_NAMESPACE_STD
