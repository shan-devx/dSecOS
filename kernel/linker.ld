ENTRY(kernel_main)
SECTIONS {
    . = 0x10000;
    .text : {
        *(.text.main)
        *(.text*)
    }
    .data : { *(.data) }
    .bss  : { *(.bss)  }
}
