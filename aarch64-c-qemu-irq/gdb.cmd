set confirm off
file out/program
target remote | qemu-system-aarch64 -M virt -cpu cortex-a57 -kernel out/program -gdb stdio -S -semihosting
layout regs
#layout src

#misc breaks
#b gic_init
b gic_set_pending


set print array on
set print repeats 0

define print_malloc_entries
  print/x *((struct malloc_entry_kt*)(&heap_end-16*8))@8
end

define cpsr_flags
  if ( ($cpsr >> 31) & 0x1 )
      print  "N "
  end
  if ( ($cpsr >> 30) & 0x1 )
      print  "Z "
  end
  if ( ($cpsr >> 29) & 0x1 )
      print  "C "
  end
  if ( ($cpsr >> 28) & 0x1 )
      print  "V "
  end
  if ( ($cpsr >> 27) & 0x1 )
      print  "Q "
  end

  if ( ($cpsr >> 20) & 0x1 )
      print  "IL "
  end

  #if ( ($cpsr >> 9) & 0x1 )
  #    print  "BIGENDIAN "
  #else
  #    print  "LITTLEENDIAN "
  #end

  if ( ($cpsr >> 8) & 0x1 )
      print  "MASK_A"
  end

  if ( ($cpsr >> 7) & 0x1 )
      print  "MASK_I"
  end

  if ( ($cpsr >> 6) & 0x1 )
      print  "MASK_F"
  end

  if ( ($cpsr >> 4) & 0x1 )
    print "AArch32 "
  else
    print "AArch64 "
    if ( ($cpsr & 0xF) == 0 )
      print "EL0 "
    end
    if ( ($cpsr & 0xF) == 4 )
      print "EL1t "
    end
    if ( ($cpsr & 0xF) == 5 )
      print "EL1h "
    end
  end






end
