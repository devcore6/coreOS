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
BOOTDIR?=$(EXEC_PREFIX)/boot
INCLUDEDIR?=$(PREFIX)/include

CFLAGS:=$(CFLAGS) -ffreestanding -Wall -Wextra
CPPFLAGS:=$(CPPFLAGS) -D__is_kernel -Iinclude -fno-exceptions -fno-rtti -fno-use-cxa-atexit -D_ARCH_$(HOSTARCH)
LDFLAGS:=$(LDFLAGS)
LIBS:=$(LIBS) -nostdlib -lk -lkpp -lgcc

ARCHDIR=arch/$(HOSTARCH)

include $(ARCHDIR)/make.config
include drivers/make.config
include drivers/arch/$(HOSTARCH)/make.config

CFLAGS:=$(CFLAGS) $(KERNEL_ARCH_CFLAGS)
CPPFLAGS:=$(CPPFLAGS) $(KERNEL_ARCH_CPPFLAGS)
LDFLAGS:=$(LDFLAGS) $(KERNEL_ARCH_LDFLAGS)
LIBS:=$(LIBS) $(KERNEL_ARCH_LIBS)

KERNEL_OBJS=\
$(KERNEL_ARCH_OBJS) \
$(DRIVER_OBJS) \
$(DRIVER_ARCH_OBJS) \
kernel/kernel.o \
kernel/find_keyboard.o \
kernel/stdio.o \

OBJS=$(KERNEL_OBJS) \

LINK_LIST=$(LDFLAGS) \
$(KERNEL_OBJS) \
$(LIBS) \

.PHONY: all clean install install-headers install-kernel
.SUFFIXES: .o .cpp .c .S .asm

all: coreOS.kernel

coreOS.kernel: $(OBJS) $(ARCHDIR)/linker.ld
	$(CXX) -T $(ARCHDIR)/linker.ld -o $@ $(CFLAGS) $(LINK_LIST)	
	grub-file --is-x86-multiboot coreOS.kernel

$(ARCHDIR)/isr.o:
	$(CXX) $(CFLAGS) $(CPPFLAGS) -mgeneral-regs-only -o $(ARCHDIR)/isr.o -c $(ARCHDIR)/isr.cpp

%.o: %.cpp
	$(CXX) $(CFLAGS) $(CPPFLAGS) -o $@ -c $<

%.o: %.c
	$(CC) $(CFLAGS) $(CPPFLAGS) -o $@ -c $< -std=gnu11

.S.o:
	$(CC) -MD -c $< -o $@ $(CFLAGS) $(CPPFLAGS)

.asm.o:
	nasm -f elf32 $< -o $@

clean:
	rm -f coreOS.kernel
	rm -f $(OBJS) *.o */*.o */*/*.o
	rm -f $(OBJS:.o=.d) *.d */*.d */*/*.d

install: install-headers install-kernel

install-headers:
	mkdir -p $(DESTDIR)$(INCLUDEDIR)
	cp -R --preserve=timestamps include/. $(DESTDIR)$(INCLUDEDIR)/.

install-kernel: coreOS.kernel
	mkdir -p $(DESTDIR)$(BOOTDIR)
	cp coreOS.kernel $(DESTDIR)$(BOOTDIR)

-include $(OBJS:.o=.d)
