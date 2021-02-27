arm-none-eabi-g++ -c -o out/main.o     main.cpp         -mcpu=cortex-a9 -marm
arm-none-eabi-as  -c -o out/startup.o  startup.s        -mcpu=cortex-a9 

arm-none-eabi-g++    -o out/program.elf out/main.o out/startup.o -marm  --specs=nano.specs -ggdb -Wl,-Map=out/program.map,-Tlinker.ld -mcpu=cortex-a9 
arm-none-eabi-objdump -D out/program.elf > out/disassembly.txt