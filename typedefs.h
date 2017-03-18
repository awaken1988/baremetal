#ifndef TYPEDEFS_H
#define TYPEDEFS_H

typedef unsigned char             uint8_t;
typedef unsigned short            uint16_t;
typedef unsigned int              uint32_t;
typedef unsigned long long        uint64_t;

typedef unsigned long long        uptr_t;

typedef unsigned char             bool_t;

#define true  (1)
#define false (0)
#define ON  (1)
#define OFF (0)


#define UINT32_PTR(x) ((volatile uint32_t*)x)
#define UINT64_PTR(x) ((volatile uint32_t*)x)
#define UPTR_VAL(x) ((uptr_t)x)

#define BASE_OFFSET_PTR_32(base, offset) 	((uint32_t*)(UPTR_VAL( UPTR_VAL(base)+UPTR_VAL(offset) ) ) )
#define BASE_OFFSET_32(base, offset)		(*(BASE_OFFSET_PTR_32(base,offset)))


#endif /* TYPEDEFS_H */
