MEMORY
{
  RAM (rwx) : org = 0x40000000, l = 32M
}

SEARCH_DIR(out)
ENTRY(reset_entry)



SECTIONS
{
  .text : { *(.text.irqtable) }  

  .text : { *(.text) }          >RAM

  .data : { *(.data) }          >RAM

  .bss :
  {
    . = ALIGN(8);
    _bss_start = .;
    *(.bss) *(COMMON)
    . = ALIGN(8);
    _bss_end = .;
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
  stack_top = .;
}
