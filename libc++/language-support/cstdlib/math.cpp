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

	int abs(int j) {
		return j > 0 ? j : (j * -1);
	}

	long int abs(long int j) {
		return j > 0 ? j : (j * -1);
	}

	long long int abs(long long int j) {
		return j > 0 ? j : (j * -1);
	}

	float abs(float j) {
		return j > 0.0f ? j : (j * -1.0f);
	}

	double abs(double j) {
		return j > 0.0 ? j : (j * -1.0);
	}

	long double abs(long double j) {
		return j > 0.0l ? j : (j * -1.0l);
	}

	long int labs(long int j) {
		return j > 0 ? j : (j * -1);
	}

	long long int llabs(long long int j) {
		return j > 0 ? j : (j * -1);
	}

	div_t div(int numer, int denom) {
		div_t ret;
		ret.quot = numer / denom;
		ret.rem = numer % denom;
		return ret;
	}

	ldiv_t div(long int numer, long int denom) {
		ldiv_t ret;
		ret.quot = numer / denom;
		ret.rem = numer % denom;
		return ret;
	}

	# if ARCH == 64
	lldiv_t div(long long int numer, long long int denom) {
		lldiv_t ret;
		ret.quot = numer / denom;
		ret.rem = numer % denom;
		return ret;
	}
	# endif
	
	ldiv_t ldiv(long int numer, long int denom) {
		ldiv_t ret;
		ret.quot = numer / denom;
		ret.rem = numer % denom;
		return ret;
	}

	# if ARCH == 64
	lldiv_t lldiv(long long int numer, long long int denom) {
		lldiv_t ret;
		ret.quot = numer / denom;
		ret.rem = numer % denom;
		return ret;
	}
	# endif

__END_NAMESPACE_STD
