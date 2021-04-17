#ifndef MK_TYPES_H
#define MK_TYPES_H

#include <stdint.h>
#include <stddef.h>

namespace mk
{
   
}



typedef uint8_t             	    u8_t;
typedef volatile uint8_t    	    vu8_t;
typedef uint16_t            	    u16_t;
typedef volatile uint16_t   	    vu16_t;
typedef uint32_t              	    u32_t;
typedef volatile uint32_t     	    vu32_t;

typedef uint64_t        	        u64_t;
typedef volatile uint64_t	        vu64_t;

typedef int8_t                      s8_t;
typedef int16_t                     s16_t;
typedef uint32_t                    s32_t;
typedef int64_t                     s64_t;
typedef uintptr_t                   uptr_t;

#define ON  (1)
#define OFF (0)


#define UINT32_PTR(x) ((volatile uint32_t*)(x))
#define UINT64_PTR(x) ((volatile uint32_t*)(x))

#define UINT32_REF(x) ( *(UINT32_PTR(x)) )
#define UINT64_REF(x) ( *(UINT64_PTR(x)) )

#define UPTR_VAL(x) ((uptr_t)x)

#define BASE_OFFSET_PTR_32(base, offset) 	((uint32_t*)(UPTR_VAL( UPTR_VAL(base)+UPTR_VAL(offset) ) ) )
#define BASE_OFFSET_32(base, offset)		(*(BASE_OFFSET_PTR_32(base,offset)))




#endif // MK_TYPES_H