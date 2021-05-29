#include <stdio.h>
#ifdef __is_libk
# include <kernel/stdio.h>
#endif
int getchar() {
#ifdef __is_libk
	return _kget();
#else

#endif
}
