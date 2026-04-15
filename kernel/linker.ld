ENTRY(kernel_main)
SECTIONS {
    . = 0x10000;
    .text : {
        *(.text.kernel_main)
        *(.text*)
    }
    .data : { *(.data) }
    .bss  : { *(.bss)  }
}
