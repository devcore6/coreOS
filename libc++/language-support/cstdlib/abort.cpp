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

#ifndef __LIBCPP_IS_KERNEL
/* 
 * Perhaps not the best implementation, however it will be improved
 * In the future.
 */
	void (*atexit0)() = nullptr;
	void (*atexit1)() = nullptr;
	void (*atexit2)() = nullptr;
	void (*atexit3)() = nullptr;
	void (*atexit4)() = nullptr;
	void (*atexit5)() = nullptr;
	void (*atexit6)() = nullptr;
	void (*atexit7)() = nullptr;
	void (*atexit8)() = nullptr;
	void (*atexit9)() = nullptr;
	void (*atexit10)() = nullptr;
	void (*atexit11)() = nullptr;
	void (*atexit12)() = nullptr;
	void (*atexit13)() = nullptr;
	void (*atexit14)() = nullptr;
	void (*atexit15)() = nullptr;
	void (*atexit16)() = nullptr;
	void (*atexit17)() = nullptr;
	void (*atexit18)() = nullptr;
	void (*atexit19)() = nullptr;
	void (*atexit20)() = nullptr;
	void (*atexit21)() = nullptr;
	void (*atexit22)() = nullptr;
	void (*atexit23)() = nullptr;
	void (*atexit24)() = nullptr;
	void (*atexit25)() = nullptr;
	void (*atexit26)() = nullptr;
	void (*atexit27)() = nullptr;
	void (*atexit28)() = nullptr;
	void (*atexit29)() = nullptr;
	void (*atexit30)() = nullptr;
	void (*atexit31)() = nullptr;
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
		if(atexit0 == nullptr) { atexit0 = func; return 0; }
		if(atexit1 == nullptr) { atexit1 = func; return 0; }
		if(atexit2 == nullptr) { atexit2 = func; return 0; }
		if(atexit3 == nullptr) { atexit3 = func; return 0; }
		if(atexit4 == nullptr) { atexit4 = func; return 0; }
		if(atexit5 == nullptr) { atexit5 = func; return 0; }
		if(atexit6 == nullptr) { atexit6 = func; return 0; }
		if(atexit7 == nullptr) { atexit7 = func; return 0; }
		if(atexit8 == nullptr) { atexit8 = func; return 0; }
		if(atexit9 == nullptr) { atexit9 = func; return 0; }
		if(atexit10 == nullptr) { atexit10 = func; return 0; }
		if(atexit11 == nullptr) { atexit11 = func; return 0; }
		if(atexit12 == nullptr) { atexit12 = func; return 0; }
		if(atexit13 == nullptr) { atexit13 = func; return 0; }
		if(atexit14 == nullptr) { atexit14 = func; return 0; }
		if(atexit15 == nullptr) { atexit15 = func; return 0; }
		if(atexit16 == nullptr) { atexit16 = func; return 0; }
		if(atexit17 == nullptr) { atexit17 = func; return 0; }
		if(atexit18 == nullptr) { atexit18 = func; return 0; }
		if(atexit19 == nullptr) { atexit19 = func; return 0; }
		if(atexit20 == nullptr) { atexit20 = func; return 0; }
		if(atexit21 == nullptr) { atexit21 = func; return 0; }
		if(atexit22 == nullptr) { atexit22 = func; return 0; }
		if(atexit23 == nullptr) { atexit23 = func; return 0; }
		if(atexit24 == nullptr) { atexit24 = func; return 0; }
		if(atexit25 == nullptr) { atexit25 = func; return 0; }
		if(atexit26 == nullptr) { atexit26 = func; return 0; }
		if(atexit27 == nullptr) { atexit27 = func; return 0; }
		if(atexit28 == nullptr) { atexit28 = func; return 0; }
		if(atexit29 == nullptr) { atexit29 = func; return 0; }
		if(atexit30 == nullptr) { atexit30 = func; return 0; }
		if(atexit31 == nullptr) { atexit31 = func; return 0; }
#endif
		return -1;
	}
	int at_quick_exit(void (*func)()) __HAS_NOEXCEPT__ { return atexit(func); }

	__HAS_NORETURN__ void exit(int status) {
#ifndef __LIBCPP_IS_KERNEL
		if(atexit0 != nullptr) atexit0();
		if(atexit1 != nullptr) atexit1();
		if(atexit2 != nullptr) atexit2();
		if(atexit3 != nullptr) atexit3();
		if(atexit4 != nullptr) atexit4();
		if(atexit5 != nullptr) atexit5();
		if(atexit6 != nullptr) atexit6();
		if(atexit7 != nullptr) atexit7();
		if(atexit8 != nullptr) atexit8();
		if(atexit9 != nullptr) atexit9();
		if(atexit10 != nullptr) atexit10();
		if(atexit11 != nullptr) atexit11();
		if(atexit12 != nullptr) atexit12();
		if(atexit13 != nullptr) atexit13();
		if(atexit14 != nullptr) atexit14();
		if(atexit15 != nullptr) atexit15();
		if(atexit16 != nullptr) atexit16();
		if(atexit17 != nullptr) atexit17();
		if(atexit18 != nullptr) atexit18();
		if(atexit19 != nullptr) atexit19();
		if(atexit20 != nullptr) atexit20();
		if(atexit21 != nullptr) atexit21();
		if(atexit22 != nullptr) atexit22();
		if(atexit23 != nullptr) atexit23();
		if(atexit24 != nullptr) atexit24();
		if(atexit25 != nullptr) atexit25();
		if(atexit26 != nullptr) atexit26();
		if(atexit27 != nullptr) atexit27();
		if(atexit28 != nullptr) atexit28();
		if(atexit29 != nullptr) atexit29();
		if(atexit30 != nullptr) atexit30();
		if(atexit31 != nullptr) atexit31();
		/*
		 * todo: quit
		 */
#endif
	}

	__HAS_NORETURN__ void _Exit(int status) __HAS_NOEXCEPT__ { exit(status); }
	__HAS_NORETURN__ void quick_exit(int status) __HAS_NOEXCEPT__ { exit(status); }

__END_NAMESPACE_STD
