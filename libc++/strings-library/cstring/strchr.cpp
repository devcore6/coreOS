#include <cstring>

__BEGIN_NAMESPACE_STD
	char* strchr(char* s, int c) {
		return (char *)std::memchr((void *)s, c, strlen(s));
	}
__END_NAMESPACE_STD
