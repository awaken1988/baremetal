import os

VariantDir('out', './', duplicate=0)
env = Environment(  ENV = os.environ,
                    CC='aarch64-elf-gcc',
                    AS='aarch64-elf-as',
                    OBJDUMP='aarch64-elf-objdump',
                    OBJCOPY='aarch64-elf-objcopy',
                    LINKFLAGS=' -nostartfiles -nodefaultlibs -Wl,--build-id=none -ggdb -Tlinker.ld -Xlinker -Map=out/program.map',
                    CFLAGS=' -ggdb ')

source = ['out/main.c', 'out/kernel_lib.c','out/cpu.c', 'out/startup.s' ]

program = env.Program('out/program.elf', source)
env.Clean(program, 'out/program.map')

#create dissassembly
disassembly = env.Command('out/program.dis', 'out/program.elf', '${OBJDUMP} -D $SOURCE > $TARGET')

#create raw binary
rawbinary = env.Command('out/program.bin', 'out/program.elf', '${OBJCOPY} -O binary $SOURCE  $TARGET')

#start qemu + gdb
if 'gdb' in COMMAND_LINE_TARGETS:
    qemugdb = env.Command('gdb', 'out/program.elf', 'aarch64-elf-gdb --command=gdb.cmd')
    env.Depends(qemugdb, disassembly)
    env.Depends(qemugdb, rawbinary)

#start qemu only
if 'qemu' in COMMAND_LINE_TARGETS:
    qemu = env.Command('qemu', 'out/program.elf', 'qemu-system-aarch64 -M virt -cpu cortex-a57 -kernel out/program.elf -gdb stdio -S -semihosting & sleep 3')
    env.Depends(qemu, disassembly)
    env.Depends(qemu, rawbinary)
    
#start qemu gdbserver
if 'gdbserver' in COMMAND_LINE_TARGETS:
    qemu = env.Command('gdbserver', 'out/program.elf', 'qemu-system-aarch64 -M virt -cpu cortex-a57 -kernel out/program.elf -s -S -semihosting')
    env.Depends(qemu, disassembly)
    env.Depends(qemu, rawbinary)


#--------------------------------------------------------------------------------------------------------
#prerocessed output
#
#	based on: http://stackoverflow.com/questions/25195644/generate-preprocessed-source-with-scons
#--------------------------------------------------------------------------------------------------------

# Create pseudo-builder and add to enviroment
def pre_process(env, source):
    env = env.Clone()
    env.Replace(OBJSUFFIX = '.E')
    env.Prepend(CFLAGS = '-E')
    return env.Object(source)
env.AddMethod(pre_process, 'PreProcess')
env.Alias('preprocess', env.PreProcess(source))
