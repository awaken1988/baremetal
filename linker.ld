MEMORY
{
  RAM (rwx) : org = 0x40000000, l = 1M
}

SEARCH_DIR(out)
ENTRY(reset_entry)



SECTIONS
{


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

  . += 4096;
  . = ALIGN(8);
  stack_top = .;
}
