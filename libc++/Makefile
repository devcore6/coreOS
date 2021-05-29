DEFAULT_HOST!=../default-host.sh
HOST?=DEFAULT_HOST
HOSTARCH!=../target-triplet-to-arch.sh $(HOST)

CFLAGS?=-O2 -g
CPPFLAGS?=
LDFLAGS?=
LIBS?=

DESTDIR?=
PREFIX?=/usr/local
EXEC_PREFIX?=$(PREFIX)
INCLUDEDIR?=$(PREFIX)/include
LIBDIR?=$(EXEC_PREFIX)/lib

CFLAGS:=$(CFLAGS) -ffreestanding -Wall -Wextra
CPPFLAGS:=$(CPPFLAGS) -D__is_libcpp -D__is_libc -Iinclude -std=c++2a -I$(DESTDIR)$(INCLUDEDIR) -nostdlib -nostdinc -lk
LIBKPP_CFLAGS:=$(CFLAGS)
LIBKPP_CPPFLAGS:=$(CPPFLAGS) -D__is_libkpp -D__is_libk

ARCHDIR=arch/$(HOSTARCH)

include $(ARCHDIR)/make.config

CFLAGS:=$(CFLAGS) $(ARCH_CFLAGS)
CPPFLAGS:=$(CPPFLAGS) $(ARCH_CPPFLAGS)
LIBKPP_CFLAGS:=$(LIBKPP_CFLAGS) $(KERNEL_ARCH_CFLAGS)
LIBKPP_CPPFLAGS:=$(LIBKPP_CPPFLAGS) $(KERNEL_ARCH_CPPFLAGS)

FREEOBJS=\
$(ARCH_FREEOBJS) \
../libc/stdlib/malloc.o \
../libc/stdlib/free.o \
language-support/new/delete.o \
language-support/new/new.o \
language-support/cstdlib/abort.o \
language-support/cstdlib/cstdlib.o \
language-support/cstdlib/math.o \
language-support/cstdlib/memory.o \
strings-library/cstring/memchr.o \
strings-library/cstring/strchr.o \
strings-library/cstring/strstr.o \
# language-support/cstdlib/string.o \

HOSTEDOBJS=\
$(ARCH_HOSTEDOBJS) \

OBJS=\
$(FREEOBJS) \
$(HOSTEDOBJS) \

LIBKPP_OBJS=$(FREEOBJS:.o=.libkpp.o)

#BINARIES=libcpp.a libkpp.a # Not ready for libc++ yet.
BINARIES=libkpp.a

.PHONY: all clean install install-headers install-libs
.SUFFIXES: .o .libkpp.o .c .S

all: $(BINARIES)

libcpp.a: $(OBJS)
	$(AR) rcs $@ $(OBJS)

libkpp.a: $(LIBKPP_OBJS)
	$(AR) rcs $@ $(LIBKPP_OBJS)

.c.o:
	$(CC) -c $< -o $@ $(CFLAGS) $(CPPFLAGS)

.cpp.o:
	$(CXX) -c $< -o $@ $(CFLAGS) $(CPPFLAGS)

.cpp.S:
	$(CXX) -c $< -o $@ $(CFLAGS) $(CPPFLAGS)

.c.libkpp.o:
	$(CC) -c $< -o $@ $(LIBKPP_CFLAGS) $(LIBKPP_CPPFLAGS)

.cpp.libkpp.o:
	$(CXX) -c $< -o $@ $(LIBKPP_CFLAGS) $(LIBKPP_CPPFLAGS)

.Spp.libkpp.o:
	$(CXX) -c $< -o $@ $(LIBKPP_CFLAGS) $(LIBKPP_CPPFLAGS)

clean:
	rm -f $(BINARIES) *.a
	rm -f $(OBJS) $(LIBKPP_OBJS) *.o */*.o */*/*.o
	rm -f $(OBJS:.o=.d) $(LIBKPP_OBJS:.o=.d) *.d */*.d */*/*.d

install: install-headers install-libs

install-headers:
	mkdir -p $(DESTDIR)$(INCLUDEDIR)
	cp -R --preserve=timestamps include/. $(DESTDIR)$(INCLUDEDIR)/.

install-libs: $(BINARIES)
	mkdir -p $(DESTDIR)$(LIBDIR)
	cp $(BINARIES) $(DESTDIR)$(LIBDIR)

-include $(OBJS:.o=.d)
-include $(LIBKPP_OBJS:.o=.d)
