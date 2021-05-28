#!/bin/sh
set -e
. ./build.sh

mkdir -p isodir
mkdir -p isodir/boot
mkdir -p isodir/boot/grub

cp sysroot/boot/coreOS.kernel isodir/boot/coreOS.kernel
cat > isodir/boot/grub/grub.cfg << EOF
menuentry "coreOS" {
	multiboot /boot/coreOS.kernel
}
EOF
grub-mkrescue -o coreOS.iso isodir
mv coreOS.iso /mnt/c/Users/korereh/coreOS.iso
