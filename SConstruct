import os

VariantDir('out', './', duplicate=0)
env = Environment(  ENV = os.environ,
                    CC='aarch64-none-elf-gcc',
                    AS='aarch64-none-elf-as',
                    OBJDUMP='aarch64-none-elf-objdump',
                    OBJCOPY='aarch64-none-elf-objcopy',
                    LINKFLAGS=' -nostartfiles -nodefaultlibs -ggdb -Tlinker.ld -Xlinker -Map=out/program.map',
                    CFLAGS=' -ggdb ')

source = ['out/main.c', 'out/kernel_lib.c','out/cpu.c', 'out/startup.s' ]

program = env.Program('out/program', source)
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


 