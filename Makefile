CROSS_PREFIX=aarch64-none-elf-
CC=$(CROSS_PREFIX)gcc
AS=$(CROSS_PREFIX)as
AR=$(CROSS_PREFIX)ar
OBJDUMP=$(CROSS_PREFIX)objdump
OBJCOPY=$(CROSS_PREFIX)objcopy
CFLAGS= -Wall -ggdb
LDFLAGS= -nostartfiles -nodefaultlibs -ggdb

dir_guard=mkdir -p ./out
.PHONY=all clean gdb

all: out/program.elf
	$(dir_guard)
	$(OBJDUMP) -D out/program.elf > out/program.dis
	$(OBJCOPY) -O binary out/program.elf out/program.bin


out/program.elf:	out/startup.o out/main.o
	$(dir_guard)
	$(CC) $(CFLAGS) $(LDFLAGS) -T linker.ld $^ -o out/program.elf

out/startup.o: startup.s
	$(dir_guard)
	$(AS) $^ -o out/startup.o

out/main.o: main.c
	$(dir_guard)
	$(CC) $(CFLAGS) $(LDFLAGS) -c $^ -o out/main.o

.PHONY: clean
clean:
	$(dir_guard)
	-rm -f out/startup.o
	-rm -f out/program.elf
	-rm -f out/program.dis
	-rm -f out/program.bin
	-rm -f out/main.o

qemu: all
	$(dir_guard)
	qemu-system-aarch64 	-M virt \
												-cpu cortex-a57	\
												-kernel out/program.elf

gdb: all
	$(dir_guard)
	aarch64-none-elf-gdb --command=gdb.cmd
