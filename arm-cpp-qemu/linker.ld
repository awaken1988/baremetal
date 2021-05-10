HEAPSIZE  = 1024;
STACKSIZE = 1024;

MEMORY
{
  RAM (rwx) : org = 0x48000000, l = 32M
}

SEARCH_DIR(out)
ENTRY(_reset_entry)

 

SECTIONS
{
  .text : { *startup*(.text) }  

  .text : { *(.text) }          >RAM

  .data : { *(.data) }          >RAM

  .ARM.exidx : {
      __exidx_start = .;
      *(.ARM.exidx* .gnu.linkonce.armexidx.*)
      __exidx_end = .;
  } > RAM


  .preinit_array     :
  {
    PROVIDE_HIDDEN (__preinit_array_start = .);
    KEEP (*(.preinit_array))
    PROVIDE_HIDDEN (__preinit_array_end = .);
  } > RAM

  .init_array     :
  {
    PROVIDE_HIDDEN (__init_array_start = .);
    KEEP (*(SORT(.init_array.*)))
    KEEP (*(.init_array ))
    PROVIDE_HIDDEN (__init_array_end = .);
  } > RAM

  .fini_array     :
  {
    PROVIDE_HIDDEN (__fini_array_start = .);
    KEEP (*(SORT(.fini_array.*)))
    KEEP (*(.fini_array ))
    PROVIDE_HIDDEN (__fini_array_end = .);
  } > RAM

  .bss (NOLOAD) :
  {
    . = ALIGN(16);
    __bss_start__ = .;
    *(.bss) *(COMMON)
    . = ALIGN(16);
    __bss_end__ = .;
  } >RAM

  .heap(NOLOAD) :
  {
    . = ALIGN(16);
    heap_start = .;
    . += HEAPSIZE;
    heap_end = .;
  }

  . += STACKSIZE;
  . = ALIGN(16);
  __stack = .;
}
