ENTRY(main)
SECTIONS {
  . = 0x10000;
  .text : {
    *(.text.main)
    *(.text*)
  }
  .rodata : { *(.rodata*) }
  .data   : { *(.data*) }
  .bss    : { *(.bss*) *(COMMON) }
  . = ALIGN(4096);
  __disk_start = .;
  . += 0x800000;
  __disk_end = .;
}
