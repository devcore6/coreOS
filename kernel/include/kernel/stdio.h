#ifndef __KERNEL_STDIO_H
# define __KERNEL_STDIO_H
# ifdef __cplusplus
extern "C" {
# else
#  include <stdbool.h>
# endif
# include <stddef.h>
extern void flush_stdout();
extern char _kget();
extern void _kputchar(char c);
extern void _kprint(char *str);
extern bool _kprints(const char *str, size_t len);
extern void _kerror(char *str);
# ifdef __cplusplus
}
# endif
#endif
