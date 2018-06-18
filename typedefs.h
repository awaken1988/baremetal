#ifndef TYPEDEFS_H
#define TYPEDEFS_H

//-------------------------------------------
// basic data types
//-------------------------------------------
typedef unsigned char             	u8_t;
typedef volatile unsigned char    	vu8_t;
typedef unsigned short            	u16_t;
typedef volatile unsigned short   	vu16_t;
typedef unsigned int              	u32_t;
typedef volatile unsigned int     	vu32_t;
typedef unsigned long long        	u64_t;
typedef volatile unsigned long long vu64_t;

typedef char             s8_t;
typedef short            s16_t;
typedef int              s32_t;
typedef long long        s64_t;

typedef long unsigned int   uptr_t;
typedef long unsigned int	size_t;


//TODO: move the follow stuff to a namespace
template<typename T> static void mem_write(uptr_t aAddress, T aValue)
{
	*((volatile T*)(aAddress)) = aValue;
}

template<typename T> static T mem_read(uptr_t aAddress)
{
	return *((volatile T*)(aAddress));
}

template<typename T> T extract_bits(T aValue, size_t aStartBit, size_t aEndBit)
{
	const size_t shleft = ( (sizeof(T)*8-1) - aEndBit );

	return (aValue<<shleft)>>(shleft+aStartBit);
}

//-------------------------------------------
// basic debug function declaration
//-------------------------------------------
extern "C" {
	extern void k_dbg_putchar(const char aChar);
}

//-------------------------------------------
// some other definitions
//-------------------------------------------
enum class num_format_e {
	BINARY  = 2,
	DECIMAL = 10,
	HEX     = 16,
};

static size_t num_output_size(num_format_e aFormat)
{
	switch(aFormat) {
	case num_format_e::BINARY: 	return 8;
	case num_format_e::DECIMAL:	return 3;
	case num_format_e::HEX:		return 2;
	}
	return 0xFFFFFFFF; //FAIL
}

#endif /* TYPEDEFS_H */
