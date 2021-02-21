MEMORY
{
  RAM (rwx) : org = 0x48000000, l = 32M
}

SEARCH_DIR(out)
ENTRY(_reset_entry)



SECTIONS
{
  .text : { startup.o(.text) }  

  .text : { *(.text) }          >RAM

  .data : { *(.data) }          >RAM

  .bss :
  {
    . = ALIGN(8);
    __bss_start__ = .;
    *(.bss) *(COMMON)
    . = ALIGN(8);
    __bss_end__ = .;
  } >RAM

  .heap :
  {
    . = ALIGN(0x100000);
    heap_start = .;
    . += 0x100000;
    heap_end = .;
  }

  . += 4096;
  . = ALIGN(8);
  __stack = .;
}
