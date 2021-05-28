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
#include <limits>
#include <cctype>

__BEGIN_NAMESPACE_STD

	// todo: locale

	long int atol(const char* nptr) { return strtol(nptr, NULL, 10); }
	double atof(const char* nptr) { return strtod(nptr, nullptr); }
	int atoi(const char* nptr) { return strtol(nptr, nullptr, 10); }

# if __ARCH == 64 && __cplusplus >= 201103L
	long long int atoll(const char* nptr) { return strtoll(nptr, nullptr, 10); }
# endif // __ARCH == 64 && __cplusplus >= 201103L

	double strtod(const char* nptr, char** endptr) {
		char *Nptr = const_cast<char*>(nptr);
		if(!Nptr) return 0;
		while(isspace(*Nptr)) Nptr++;						// Skip all whitespaces
		double value = 0;
		int sign = 1;
		int factor = 10;
		if(*Nptr == '+' || *Nptr == '-') {					// Check for sign
			if(*Nptr == '-') sign = -1;
			Nptr++;											// Move to the next character
		}
#if __cplusplus >= 201103L									// C++11 adds support for NAN, INF/INFINITY and hex numbers in 0x formatting
		if(!isdigit(*Nptr)) {								// Not a character, check for NAN/INF/INFINITY
			if(tolower(*Nptr) == 'n' && tolower(*(Nptr + 1)) == 'a' && tolower(*(Nptr + 2)) == 'n') return numeric_limits<double>::signaling_NaN();
			if(tolower(*Nptr) == 'i' && tolower(*(Nptr + 1)) == 'n' && tolower(*(Nptr + 2)) == 'f' && *(Nptr + 3) == 0) return numeric_limits<double>::infinity();
			if(tolower(*Nptr) == 'i' && tolower(*(Nptr + 1)) == 'n' && tolower(*(Nptr + 2)) == 'f' && tolower(*(Nptr + 3)) == 'i' && \
			   tolower(*(Nptr + 4)) == 'n' && tolower(*(Nptr + 5)) == 'i' && tolower(*(Nptr + 6)) == 't' && tolower(*(Nptr + 7)) == 'y' && \
			  *(Nptr + 8) == 0) return numeric_limits<double>::infinity();
		}
		if(*Nptr == '0' && tolower(*(Nptr + 1)) == 'x') {	// 0x indicates a hex number
			Nptr + 2;										// Move two characters forward
			factor = 16;									// Factor is now 16
		}
		while(isdigit(*Nptr) || (factor == 16 && (tolower(*Nptr) >= 'a' && tolower(*Nptr) <= 'f'))) {
			if(tolower(*Nptr) >= 'a' && tolower(*Nptr) <= 'f') {
				value *= 16;								// Multiply the value by the factor (16) as we are now on the next digit
				value += (double)(tolower(*Nptr) - 'a' + 10); // Add the value of the character (lowercase character - a + 10)
				Nptr++;										// Step to next character
				continue;									// Go back to the top of the loop
			}
#else
		while(isdigit(*Nptr)) {
#endif // __cplusplus < 201103L
			value *= factor;								// Multiply the value by the factor as we are now on the next digit
			value += (double)(*Nptr - '0');					// Add the value of the character
			Nptr++;											// Step to next character
		}
		if(*Nptr == '.') {									// Found a dot
			Nptr++;											// Step to the next character
			int count = 0;									// Decimal place counter
#if __cplusplus >= 201103L									// C++11 adds support for hex numbers in 0x formatting
			while(isdigit(*Nptr) || (factor == 16 && (tolower(*Nptr) >= 'a' && tolower(*Nptr) <= 'f'))) {
			if(tolower(*Nptr) >= 'a' && tolower(*Nptr) <= 'f') {
				value += (double)(tolower(*Nptr) - 'a' + 10) / pow(16, count + 1); // Add the value of the character divided by
															// factor^(count+1) as we are adding a number in the decimal place
				count++;									// Increase decimal place counter
				Nptr++;										// Step to next character
				continue;									// Go back to the top of the loop
			}
#else
			while(isdigit(*Nptr)) {
#endif // __cplusplus < 201103L
				value += (double)(*Nptr - '0') / pow(factor, count + 1); // Add the value of the character divided by factor^(count+1)
															// as we are adding a number in the decimal place
				count++;									// Increase decimal place counter
				Nptr++;										// Step to next character
			}
			if((tolower(*Nptr) == 'e' && factor == 10) || \
			   (tolower(*Nptr) == 'p' && factor == 16)) {	// Scientific notation
				Nptr++;										// Step to next character
				double exponent = 0;						// Keep track of the exponent
				int expsign = 1;							// Keep track of the exponent sign
				if(*Nptr == '+' || *Nptr == '-') {
					if(*Nptr == '-') expsign = -1;			// Set exponent sign to -
					Nptr++;									// Step to next character
				}
				while(isdigit(*Nptr)) {
					exponent *= 10;							// Next digit, so multiply exponent by 10
					exponent += (double)(*Nptr - '0');		// Add the value of the character
					Nptr++;
				}
				if(factor == 10) value *= pow(10, exponent * expsign);
				else value *= pow(2, exponent * expsign);
			}
		}
		Nptr++;												// Step to next character
		if(endptr != nullptr) *endptr = Nptr;				// Set endptr to the current position
		return value * sign;
	}

	float strtof(const char* nptr, char** endptr) {
		char *Nptr = const_cast<char*>(nptr);
		if(!Nptr) return 0;
		while(isspace(*Nptr)) Nptr++;						// Skip all whitespaces
		float value = 0;
		int sign = 1;
		int factor = 10;
		if(*Nptr == '+' || *Nptr == '-') {					// Check for sign
			if(*Nptr == '-') sign = -1;
			Nptr++;											// Move to the next character
		}
#if __cplusplus >= 201103L									// C++11 adds support for NAN, INF/INFINITY and hex numbers in 0x formatting
		if(!isdigit(*Nptr)) {								// Not a character, check for NAN/INF/INFINITY
			if(tolower(*Nptr) == 'n' && tolower(*(Nptr + 1)) == 'a' && tolower(*(Nptr + 2)) == 'n') return numeric_limits<float>::signaling_NaN();
			if(tolower(*Nptr) == 'i' && tolower(*(Nptr + 1)) == 'n' && tolower(*(Nptr + 2)) == 'f' && *(Nptr + 3) == 0) return numeric_limits<float>::infinity();
			if(tolower(*Nptr) == 'i' && tolower(*(Nptr + 1)) == 'n' && tolower(*(Nptr + 2)) == 'f' && tolower(*(Nptr + 3)) == 'i' && \
			   tolower(*(Nptr + 4)) == 'n' && tolower(*(Nptr + 5)) == 'i' && tolower(*(Nptr + 6)) == 't' && tolower(*(Nptr + 7)) == 'y' && \
			  *(Nptr + 8) == 0) return numeric_limits<float>::infinity();
		}
		if(*Nptr == '0' && tolower(*(Nptr + 1)) == 'x') {	// 0x indicates a hex number
			Nptr + 2;										// Move two characters forward
			factor = 16;									// Factor is now 16
		}
		while(isdigit(*Nptr) || (factor == 16 && (tolower(*Nptr) >= 'a' && tolower(*Nptr) <= 'f'))) {
			if(tolower(*Nptr) >= 'a' && tolower(*Nptr) <= 'f') {
				value *= 16;								// Multiply the value by the factor (16) as we are now on the next digit
				value += (float)(tolower(*Nptr) - 'a' + 10);// Add the value of the character (lowercase character - a + 10)
				Nptr++;										// Step to next character
				continue;									// Go back to the top of the loop
			}
#else
		while(isdigit(*Nptr)) {
#endif // __cplusplus < 201103L
			value *= factor;								// Multiply the value by the factor as we are now on the next digit
			value += (float)(*Nptr - '0');					// Add the value of the character
			Nptr++;											// Step to next character
		}
		if(*Nptr == '.') {									// Found a dot
			Nptr++;											// Step to the next character
			int count = 0;									// Decimal place counter
#if __cplusplus >= 201103L									// C++11 adds support for hex numbers in 0x formatting
			while(isdigit(*Nptr) || (factor == 16 && (tolower(*Nptr) >= 'a' && tolower(*Nptr) <= 'f'))) {
			if(tolower(*Nptr) >= 'a' && tolower(*Nptr) <= 'f') {
				value += (float)(tolower(*Nptr) - 'a' + 10) / pow(16, count + 1); // Add the value of the character divided by
															// factor^(count+1) as we are adding a number in the decimal place
				count++;									// Increase decimal place counter
				Nptr++;										// Step to next character
				continue;									// Go back to the top of the loop
			}
#else
			while(isdigit(*Nptr)) {
#endif // __cplusplus < 201103L
				value += (float)(*Nptr - '0') / pow(factor, count + 1); // Add the value of the character divided by factor^(count+1)
															// as we are adding a number in the decimal place
				count++;									// Increase decimal place counter
				Nptr++;										// Step to next character
			}
			if((tolower(*Nptr) == 'e' && factor == 10) || \
			   (tolower(*Nptr) == 'p' && factor == 16)) {	// Scientific notation
				Nptr++;										// Step to next character
				float exponent = 0;							// Keep track of the exponent
				int expsign = 1;							// Keep track of the exponent sign
				if(*Nptr == '+' || *Nptr == '-') {
					if(*Nptr == '-') expsign = -1;			// Set exponent sign to -
					Nptr++;									// Step to next character
				}
				while(isdigit(*Nptr)) {
					exponent *= 10;							// Next digit, so multiply exponent by 10
					exponent += (float)(*Nptr - '0');		// Add the value of the character
					Nptr++;
				}
#if __cplusplus >= 201103L									// powf introduced in C++11
				if(factor == 10) value *= powf(10, exponent * expsign);
				else value *= powf(2, exponent * expsign);
#else
				if(factor == 10) value *= pow(10, exponent * expsign);
				else value *= pow(2, exponent * expsign);
#endif // __cplusplus >= 201103L
			}
		}
		Nptr++;												// Step to next character
		if(endptr != nullptr) *endptr = Nptr;				// Set endptr to the current position
		return value * sign;
	}

	long double strtold(const char* nptr, char** endptr) {
		char *Nptr = const_cast<char*>(nptr);
		if(!Nptr) return 0;
		while(isspace(*Nptr)) Nptr++;						// Skip all whitespaces
		long double value = 0;
		int sign = 1;
		int factor = 10;
		if(*Nptr == '+' || *Nptr == '-') {					// Check for sign
			if(*Nptr == '-') sign = -1;
			Nptr++;											// Move to the next character
		}
#if __cplusplus >= 201103L									// C++11 adds support for NAN, INF/INFINITY and hex numbers in 0x formatting
		if(!isdigit(*Nptr)) {								// Not a character, check for NAN/INF/INFINITY
			if(tolower(*Nptr) == 'n' && tolower(*(Nptr + 1)) == 'a' && tolower(*(Nptr + 2)) == 'n') return numeric_limits<long double>::signaling_NaN();
			if(tolower(*Nptr) == 'i' && tolower(*(Nptr + 1)) == 'n' && tolower(*(Nptr + 2)) == 'f' && *(Nptr + 3) == 0) return numeric_limits<long double>::infinity();
			if(tolower(*Nptr) == 'i' && tolower(*(Nptr + 1)) == 'n' && tolower(*(Nptr + 2)) == 'f' && tolower(*(Nptr + 3)) == 'i' && \
			   tolower(*(Nptr + 4)) == 'n' && tolower(*(Nptr + 5)) == 'i' && tolower(*(Nptr + 6)) == 't' && tolower(*(Nptr + 7)) == 'y' && \
			  *(Nptr + 8) == 0) return numeric_limits<long double>::infinity();
		}
		if(*Nptr == '0' && tolower(*(Nptr + 1)) == 'x') {	// 0x indicates a hex number
			Nptr + 2;										// Move two characters forward
			factor = 16;									// Factor is now 16
		}
		while(isdigit(*Nptr) || (factor == 16 && (tolower(*Nptr) >= 'a' && tolower(*Nptr) <= 'f'))) {
			if(tolower(*Nptr) >= 'a' && tolower(*Nptr) <= 'f') {
				value *= 16;								// Multiply the value by the factor (16) as we are now on the next digit
				value += (long double)(tolower(*Nptr) - 'a' + 10); // Add the value of the character (lowercase character - a + 10)
				Nptr++;										// Step to next character
				continue;									// Go back to the top of the loop
			}
#else
		while(isdigit(*Nptr)) {
#endif // __cplusplus < 201103L
			value *= factor;								// Multiply the value by the factor as we are now on the next digit
			value += (long double)(*Nptr - '0');			// Add the value of the character
			Nptr++;											// Step to next character
		}
		if(*Nptr == '.') {									// Found a dot
			Nptr++;											// Step to the next character
			int count = 0;									// Decimal place counter
#if __cplusplus >= 201103L									// C++11 adds support for hex numbers in 0x formatting
			while(isdigit(*Nptr) || (factor == 16 && (tolower(*Nptr) >= 'a' && tolower(*Nptr) <= 'f'))) {
			if(tolower(*Nptr) >= 'a' && tolower(*Nptr) <= 'f') {
				value += (long double)(tolower(*Nptr) - 'a' + 10) / pow(16, count + 1); // Add the value of the character divided by
															// factor^(count+1) as we are adding a number in the decimal place
				count++;									// Increase decimal place counter
				Nptr++;										// Step to next character
				continue;									// Go back to the top of the loop
			}
#else
			while(isdigit(*Nptr)) {
#endif // __cplusplus < 201103L
				value += (long double)(*Nptr - '0') / pow(factor, count + 1); // Add the value of the character divided by factor^(count+1)
															// as we are adding a number in the decimal place
				count++;									// Increase decimal place counter
				Nptr++;										// Step to next character
			}
			if((tolower(*Nptr) == 'e' && factor == 10) || \
			   (tolower(*Nptr) == 'p' && factor == 16)) {	// Scientific notation
				Nptr++;										// Step to next character
				long double exponent = 0;					// Keep track of the exponent
				int expsign = 1;							// Keep track of the exponent sign
				if(*Nptr == '+' || *Nptr == '-') {
					if(*Nptr == '-') expsign = -1;			// Set exponent sign to -
					Nptr++;									// Step to next character
				}
				while(isdigit(*Nptr)) {
					exponent *= 10;							// Next digit, so multiply exponent by 10
					exponent += (long double)(*Nptr - '0');	// Add the value of the character
					Nptr++;
				}
#if __cplusplus >= 201103L									// powl introduced in C++11
				if(factor == 10) value *= powl(10, exponent * expsign);
				else value *= powl(2, exponent * expsign);
#else
				if(factor == 10) value *= pow(10, exponent * expsign);
				else value *= pow(2, exponent * expsign);
#endif // __cplusplus >= 201103L
			}
		}
		Nptr++;												// Step to next character
		if(endptr != nullptr) *endptr = Nptr;				// Set endptr to the current position
		return value * sign;
	}

	long int strtol(const char* nptr, char** endptr, int base) {
		char *Nptr = const_cast<char*>(nptr);
		if(!Nptr) return 0;
		while(isspace(*Nptr)) Nptr++;						// Skip all whitespaces
		int value = 0;
		int sign = 1;
		if(*Nptr == '+' || *Nptr == '-') {					// Check sign
			if(*Nptr == '-') sign = -1;
			Nptr++;											// Step to next character
		}
		if(base == 0 || base == 8) if(*Nptr == '0' && isdigit(*Nptr + 1)) { // identifier 0 for base 8
			base = 8;
			Nptr++;											// Step to next character
		}
		if(base == 0 || base == 16) if(*Nptr == '0' && *(Nptr + 1) == 'x' && isdigit(*Nptr + 2)) { // identifier 0x for hex
			base = 16;
			Nptr++;											// Step to next character
		}
		while((isdigit(*Nptr) && (*Nptr - '0' < base)) || (tolower(*Nptr) - 'a' + 10 < base)) {
			value *= base;									// Multiply value by base (next character)
			if(isdigit(*Nptr)) value += (long)(*Nptr - '0');// Add value of character
			else value += (long)(tolower(*Nptr) - 'a' + 10);// Add value of character
			Nptr++;											// Step to next character
		}
		Nptr++;												// Step to next character
		if(endptr != nullptr) *endptr = Nptr;				// Set endptr to the current position
		return value * sign;
	}

# if __ARCH == 64 && __cplusplus >= 201103L
	long long int strtoll(const char* nptr, char** endptr, int base) {
		char *Nptr = const_cast<char*>(nptr);
		if(!Nptr) return 0;
		while(isspace(*Nptr)) Nptr++;						// Skip all whitespaces
		long long value = 0;
		int sign = 1;
		if(*Nptr == '+' || *Nptr == '-') {					// Check sign
			if(*Nptr == '-') sign = -1;
			Nptr++;											// Step to next character
		}
		if(base == 0 || base == 8) if(*Nptr == '0' && isdigit(*Nptr + 1)) { // identifier 0 for base 8
			base = 8;
			Nptr++;											// Step to next character
		}
		if(base == 0 || base == 16) if(*Nptr == '0' && *(Nptr + 1) == 'x' && isdigit(*Nptr + 2)) { // identifier 0x for hex
			base = 16;
			Nptr++;											// Step to next character
		}
		while((isdigit(*Nptr) && (*Nptr - '0' < base)) || (tolower(*Nptr) - 'a' + 10 < base)) {
			value *= base;									// Multiply value by base (next character)
			if(isdigit(*Nptr)) value += (long long)(*Nptr - '0'); // Add value of character
			else value += (long long)(tolower(*Nptr) - 'a' + 10); // Add value of character
			Nptr++;											// Step to next character
		}
		Nptr++;												// Step to next character
		if(endptr != nullptr) *endptr = Nptr;				// Set endptr to the current position
		return value * sign;
	}
# endif // __ARCH == 64 && __cplusplus >= 201103L

	unsigned long int strtoul(const char* nptr, char** endptr, int base) {
		char *Nptr = const_cast<char*>(nptr);
		if(!Nptr) return 0;
		while(isspace(*Nptr)) Nptr++;						// Skip all whitespaces
		unsigned long value = 0;
		if(base == 0 || base == 8) if(*Nptr == '0' && isdigit(*Nptr + 1)) { // identifier 0 for base 8
			base = 8;
			Nptr++;											// Step to next character
		}
		if(base == 0 || base == 16) if(*Nptr == '0' && *(Nptr + 1) == 'x' && isdigit(*Nptr + 2)) { // identifier 0x for hex
			base = 16;
			Nptr++;											// Step to next character
		}
		while((isdigit(*Nptr) && (*Nptr - '0' < base)) || (tolower(*Nptr) - 'a' + 10 < base)) {
			value *= base;									// Multiply value by base (next character)
			if(isdigit(*Nptr)) value += (unsigned long)(*Nptr - '0'); // Add value of character
			else value += (unsigned long)(tolower(*Nptr) - 'a' + 10); // Add value of character
			Nptr++;											// Step to next character
		}
		Nptr++;												// Step to next character
		if(endptr != nullptr) *endptr = Nptr;				// Set endptr to the current position
		return value;
	}

# if __ARCH == 64 && __cplusplus >= 201103L
	unsigned long long int strtoull(const char* nptr, char** endptr, int base) {
		char *Nptr = const_cast<char*>(nptr);
		if(!Nptr) return 0;
		while(isspace(*Nptr)) Nptr++;						// Skip all whitespaces
		unsigned long long value = 0;
		if(base == 0 || base == 8) if(*Nptr == '0' && isdigit(*Nptr + 1)) { // identifier 0 for base 8
			base = 8;
			Nptr++;											// Step to next character
		}
		if(base == 0 || base == 16) if(*Nptr == '0' && *(Nptr + 1) == 'x' && isdigit(*Nptr + 2)) { // identifier 0x for hex
			base = 16;
			Nptr++;											// Step to next character
		}
		while((isdigit(*Nptr) && (*Nptr - '0' < base)) || (tolower(*Nptr) - 'a' + 10 < base)) {
			value *= base;									// Multiply value by base (next character)
			if(isdigit(*Nptr)) value += (unsigned long long)(*Nptr - '0'); // Add value of character
			else value += (unsigned long long)(tolower(*Nptr) - 'a' + 10); // Add value of character
			Nptr++;											// Step to next character
		}
		Nptr++;												// Step to next character
		if(endptr != nullptr) *endptr = Nptr;				// Set endptr to the current position
		return value;
	}
# endif // __ARCH == 64 && __cplusplus >= 201103L

	int mblen(const char* s, size_t n) {
		if(!s || !*s) return 0;

	}

	int mbtowc(wchar_t* pwc, const char* s, size_t n) {

	}

	int wctomb(char* s, wchar_t wchar) {

	}

	size_t mbstowcs(wchar_t* pwcs, const char* s, size_t n) {

	}

	size_t wcstombs(char* s, const wchar_t* pwcs, size_t n) {

	}

__END_NAMESPACE_STD
