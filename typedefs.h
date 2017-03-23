#ifndef TYPEDEFS_H
#define TYPEDEFS_H

typedef unsigned char             uint8_t;
typedef unsigned char             u8_t;
typedef unsigned short            uint16_t;
typedef unsigned short            u16_t;
typedef unsigned int              uint32_t;
typedef unsigned int              u32_t;
typedef unsigned long long        uint64_t;
typedef unsigned long long        u64_t;

typedef char             int8_t;
typedef char             s8_t;
typedef short            int16_t;
typedef short            s16_t;
typedef int              int32_t;
typedef int              s32_t;
typedef long long        int64_t;
typedef long long        s64_t;



typedef unsigned long long        uptr_t;
typedef unsigned long long		  size_t;

typedef unsigned char             bool_t;

#define true  (1)
#define false (0)
#define ON  (1)
#define OFF (0)


#define UINT32_PTR(x) ((volatile uint32_t*)(x))
#define UINT64_PTR(x) ((volatile uint32_t*)(x))

#define UINT32_REF(x) ( *(UINT32_PTR(x)) )
#define UINT64_REF(x) ( *(UINT64_PTR(x)) )

#define UPTR_VAL(x) ((uptr_t)x)

#define BASE_OFFSET_PTR_32(base, offset) 	((uint32_t*)(UPTR_VAL( UPTR_VAL(base)+UPTR_VAL(offset) ) ) )
#define BASE_OFFSET_32(base, offset)		(*(BASE_OFFSET_PTR_32(base,offset)))


//----------------------------
//
// Variant type
//
//----------------------------
typedef union _variant_t
{
	u8_t	m_u8_t;
	u16_t	m_u16_t;
	u32_t	m_u32_t;
	u64_t	m_u64_t;
	float	m_float;
	double	m_double;
} variant_t;

#define VA_UNUM(x)		( (variant_t){.m_u64_t = x} )
#define VA_FLOAT(x)		( (variant_t){.m_float = x} )
#define VA_DOUBLE(x)	( (variant_t){.m_double = x} )

//----------------------------
//
// Counted Array
//
//----------------------------

//x = typename
#define KVECTOR_DECLARE(x) struct x ## _array_t { 	size_t count; 		\
													x*	   elements;	\
										    	};

#define KVECTOR_CREATE(x, ...) (__VA_ARGS__)

//for each type we need arrays
//	we declare them here
KVECTOR_DECLARE(variant_t)



#endif /* TYPEDEFS_H */
