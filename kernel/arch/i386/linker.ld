ENTRY(_loader)
OUTPUT_FORMAT(elf32-i386)
 
SECTIONS {
   /* The kernel will live at -511MB in the virtual
      address space, which will be mapped to 1MB in the
      physical address space. */
   . = 0xE0100000;
 
   .text : AT(ADDR(.text) - 0xE0000000) {
       *(.text)
       *(.rodata*)
   }
 
   .data ALIGN (0x1000) : AT(ADDR(.data) - 0xE0000000) {
       *(.data)
   }
 
   .bss : AT(ADDR(.bss) - 0xE0000000) {
       _sbss = .;
       *(COMMON)
       *(.bss)
       _ebss = .;
   }
}