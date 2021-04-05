MEMORY
{
  RAM (rwx) : org = 0x40000000, l = 32M
}

SEARCH_DIR(out)
ENTRY(_reset_entry)

 

SECTIONS
{
  .text : { *(.text.irqtable) }

  .text : { *startup*(.text) }  

  .text : { *(.text) }          >RAM

  .data : { *(.data) }          >RAM

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
    . = ALIGN(8);
    __bss_start__ = .;
    *(.bss) *(COMMON)
    . = ALIGN(8);
    __bss_end__ = .;
  } >RAM

  .heap(NOLOAD) :
  {
    . = ALIGN(0x100000);
    heap_start = .;
    . += 0x400000;
    heap_end = .;
  }

  . += 0x100000;
  . = ALIGN(8);
  __stack = .;
}
