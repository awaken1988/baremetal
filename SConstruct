import os

VariantDir('out', './')
env = Environment(  ENV = {'PATH' : os.environ['PATH']},
                    CC='aarch64-none-elf-gcc',
                    AS='aarch64-none-elf-as',
                    OBJDUMP='aarch64-none-elf-objdump',
                    LINKFLAGS=' -nostartfiles -nodefaultlibs -ggdb -Tlinker.ld ')

program = env.Program('out/program', [      'out/main.c',
                                            'out/kernel_lib.c',
                                            'out/startup.s' ])

#create dissassembly
disassembly = env.Command('out/program.dis', 'out/program', 'aarch64-none-elf-objdump -D $SOURCE > $TARGET')
env.Depends(disassembly, program)

#start qemu + gdb
qemugdb = env.Command()
