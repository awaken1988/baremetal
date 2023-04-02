.global _reset_entry

_reset_entry:
    .option push
    .option norelax
    la    gp, __global_pointer$
    .option pop

    la    sp, __stack
    jal   main
