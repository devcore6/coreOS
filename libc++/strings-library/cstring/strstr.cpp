#include <cstring>

__BEGIN_NAMESPACE_STD
	char* strstr(char* s1, const char* s2) {
		for(size_t i = 0; i < strlen(const_cast<const char*>(s1)) - strlen(const_cast<const char*>(s2)); i++) {
			int failed = 0;
			for(size_t j = 0; j < strlen(const_cast<const char*>(s2)); j++) {
				if(s1[i + j] != s2[j]) {
					failed = 1;
					break;
				}
			}
			if(!failed) return s1 + i;
		}
		return 0;
	}
__END_NAMESPACE_STD
