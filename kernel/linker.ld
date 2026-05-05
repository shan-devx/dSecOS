ENTRY(main)
SECTIONS {
  . = 0x100000;
  .text : {
    *(.text.main)
    *(.text*)
  }
  .rodata : { *(.rodata*) }
  .data   : { *(.data*) }
  .bss    : { *(.bss*) *(COMMON) }
  __heap_start = .;
  . += 0x4000000;
  __heap_end = .;
  . = ALIGN(4096);
  __disk_start = .;
  . += 0x800000;
  __disk_end = .;
}
