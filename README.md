example of using aarch64-none-elf-gcc cross compiler with qemu and gdb.

to compile and run the bare metal program with qemu type:
```
  make gdb
```

prerequisites to run this are:
* aarch64-none-elf-{binutils,gcc,gdb}
* qemu-system-aarch64

![Run and Debug](/screenshots/qemu_gdb.jpg?raw=true "Register Analyzer")
![Codesnippet](/screenshots/atom_main_c.jpg?raw=true "Register Analyzer")
