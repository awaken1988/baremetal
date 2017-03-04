import os

VariantDir('out', './', duplicate=0)
env = Environment(  ENV = os.environ,
                    CC='aarch64-none-elf-gcc',
                    AS='aarch64-none-elf-as',
                    OBJDUMP='aarch64-none-elf-objdump',
                    OBJCOPY='aarch64-none-elf-objcopy',
                    LINKFLAGS=' -nostartfiles -nodefaultlibs -ggdb -Tlinker.ld -Xlinker -Map=out/program.map')

program = env.Program('out/program', [      'out/main.c',
                                            'out/kernel_lib.c',
                                            'out/startup.s' ])
env.Clean(program, 'out/program.map')

#create dissassembly
disassembly = env.Command('out/program.dis', 'out/program', '${OBJDUMP} -D $SOURCE > $TARGET')

#create raw binary
rawbinary = env.Command('out/program.bin', 'out/program', '${OBJCOPY} -O binary $SOURCE  $TARGET')

#start qemu + gdb
if 'gdb' in COMMAND_LINE_TARGETS:
    qemugdb = env.Command('gdb', 'out/program', 'aarch64-none-elf-gdb --command=gdb.cmd')
    env.Depends(qemugdb, disassembly)
    env.Depends(qemugdb, rawbinary)
