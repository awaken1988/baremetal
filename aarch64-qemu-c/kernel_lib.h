#ifndef KERNEL_LIB_H
#define KERNEL_LIB_H
#include "typedefs.h"

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

void k_print_str(const char *s);

void k_print_ull(	unsigned long long num,
					enum print_flags_kt flags,
					int digits);



//----------------------------------------------
// print to console
//----------------------------------------------
typedef struct _k_print_args_t
{
	size_t count;
	variant_t* elements;
} k_print_args_t;

void k_print(const char* fmt, variant_t* args);
void k_print_char(const char ch);





//-------------------------------
// allocate memory
//-------------------------------

//! returns a pointer to allocated memory or NULL
void* k_malloc(size_kt size);

//! free allocated memory
void k_free(void* ptr);





#endif
