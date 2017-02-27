#ifndef KERNEL_LIB_H
#define KERNEL_LIB_H

typedef unsigned long long size_kt;
typedef unsigned long long ptr_kt;


//-------------------------------
// print to qemus console
//-------------------------------
enum print_flags_kt
{
	PRINT_FLAG_HEX = 0x1,
	PRINT_FLAG_BIN = 0x2,
};

char k_digit_to_hex(int digit);
char k_digit_to_bin(int digit);

void k_print(const char *s);

void k_print_ull(	unsigned long long num,
					enum print_flags_kt flags);








//-------------------------------
// allocate memory
//-------------------------------

//! returns a pointer to allocated memory or NULL
void* k_malloc(size_kt size);

//! free allocated memory
void k_free(void* ptr);



#endif
