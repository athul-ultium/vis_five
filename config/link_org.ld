ENTRY(_start)

/*_stack_start = 0x023FFFFFFF;*/


MEMORY 
{
       DDR (xrw) : ORIGIN =0x40000000, LENGTH =0x20000000
}


SECTIONS
{
    .text : {
        KEEP(*(.text.boot))  
        *(.text*)
        lib/libthreadx.a 
        . = ALIGN(8);
    } > DDR

    .rodata : {
        . = ALIGN(8);
        __global_pointer$ = . + 0x800;
        *(.rodata*)
        *(.srodata*)
        *(.interp)
        *(.note.gnu.build-id)
        *(.dynsym)
        *(.dynstr)
        *(.gnu.hash)
        *(.rela*)
        . = ALIGN(8);
    } >DDR

    .compiler_sec : {
        *(.riscv.attributes) 
        *(.debug*)
    } > DDR

    .data : { 
        . = ALIGN(8);
        *(.sdata*)
        *(.data*)
        *(.dynamic)
        *(.got)
        *(.got.plt)
        . = ALIGN(8);
    } > DDR 

    .bss : {
        . = ALIGN(8);
        _bss_start = .;
        *(.sbss*)
        *(.bss*)
        *(COMMON)
        . = ALIGN(8);
        _bss_end = .;
    } > DDR

    ._user_heap (NOLOAD) : {
        PROVIDE(_heap_start = . );
        *(.heap)
        . += 64K;
        . = ALIGN(16);
    } > DDR



    .kstack (NOLOAD) : {
        . = ALIGN(16);
        . += 10K;
        _stack_start = .;
    } > DDR

    /DISCARD/ : { *(.comment .note .eh_frame) }
}
