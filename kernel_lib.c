#include "kernel_lib.h"

//-------------------------------
//
// console print
//
//-------------------------------
volatile unsigned int * const UART0DR = (unsigned int *) 0x09000000;

char k_digit_to_hex(int digit)
{
   switch(digit & 0xF) {
	  case 0x0: return '0';
	  case 0x1: return '1';
	  case 0x2: return '2';
	  case 0x3: return '3';
	  case 0x4: return '4';
	  case 0x5: return '5';
	  case 0x6: return '6';
	  case 0x7: return '7';
	  case 0x8: return '8';
	  case 0x9: return '9';
	  case 0xA: return 'A';
	  case 0xB: return 'B';
	  case 0xC: return 'C';
	  case 0xD: return 'D';
	  case 0xE: return 'E';
	  case 0xF: return 'F';
	}

   return  '?';
}

char k_digit_to_bin(int digit)
{
	if( digit )
		return '1';
	return '0';
}


void k_print_str(const char *s)
{
    while(*s != '\0') {
    	k_print_char(*s);
        s++;
    }
}

void k_print_char(const char ch)
{
	*UART0DR = (unsigned int)(ch);
}


//! convert num to string
//!
//!	buff should have enough place for digits
void k_print_ull(	unsigned long long num,
					enum print_flags_kt flags,
					int digits)
{
	int step_width = 0;
	int num_mask = 0;
	char buff;

	//get the step bit width
	if( flags & PRINT_FLAG_BIN) {
		step_width = 1;
		num_mask = 0x1;
	}
	else {
		step_width = 4;
		num_mask = 0xF;
	}

	for(int iDigit=digits-1; iDigit>=0; iDigit--) {

		const int val = (num>>(4*iDigit)) & num_mask;

		if( flags & PRINT_FLAG_BIN ) {
			buff = k_digit_to_bin(val);
		}
		else {
			buff = k_digit_to_hex(val);
		}

		k_print_char(buff);
	}
}



static char peek_char (const char* ptr)
{
	return *(ptr+1);
}

//! print formated char
//!
//!	\return last character consumed
static char* print_formated(char* fmt, variant_t* arg)
{
	int digits = 0;
	char type = '\0';
	char saved_fmt = *fmt;

	switch( saved_fmt )
	{
	case 'x':	digits = sizeof(unsigned long long)*2; break;
	case 'b':	digits = sizeof(unsigned long long)*8; break;
		break;
	default:
		return fmt;
	}

	//get digit width
	for(int i=0; i<2; i++) {

		if( '\0' == peek_char(++fmt) )
			return fmt;
		if( 0 == i )
			digits = 0;

		if( *fmt >= '0' && *fmt <= '9' ) {
			digits += i * (*(fmt)-48 ); 		//TODO: create defines for ASCII stuff
		}
	}


	switch( saved_fmt )
		{
		case 'x':
			k_print_ull(arg->m_u64_t, PRINT_FLAG_HEX, digits);
			break;
		case 'b':
			k_print_ull(arg->m_u64_t, PRINT_FLAG_BIN, digits);
			break;
	}

	return fmt+1;
}

#define NEXT_CHAR_RETURN(fmt) if('\0' == peek_char(fmt) ) return; fmt++;

void k_print(const char* fmt, variant_t* args)
{
	int arg_idx = 0;

	if( 0 == fmt || '\0' == *fmt )
		return;

	do
	{
		switch(*fmt)
		{
			case '\\':
			{
				NEXT_CHAR_RETURN(fmt);
				//do special character here
			} break;

			case '%':
			{
				NEXT_CHAR_RETURN(fmt);
			} break;

		}
	} while( *(++fmt) != '\0');
}


//-------------------------------
//
// allocate memory
//
//-------------------------------
extern char heap_start;
extern char heap_end;

struct malloc_entry_kt
{
  ptr_kt    address;
  size_kt   size;
};

//! get the first entry of entry table
static struct malloc_entry_kt* impl_alloc_first_entry()
{
	return (struct malloc_entry_kt*)
			(&heap_end - sizeof(struct malloc_entry_kt));
}

static int impl_alloc_entry_count()
{
	int count = 0;
	struct malloc_entry_kt* entry_iter = impl_alloc_first_entry();

	while( entry_iter->size != 0 ) {
		count++;
		entry_iter--;
	}

	return count;
}

//! sort mallocs entry table
static void impl_alloc_entry_sort()
{
  while( 1 ) {
    int isTouched = 0;
    struct malloc_entry_kt* start_entry = impl_alloc_first_entry();

    while( start_entry->size != 0 ) {
      struct malloc_entry_kt* next_entry = start_entry - 1;


      if( next_entry->size == 0 )
        break;

      if( start_entry->address > next_entry->address ) {
        struct malloc_entry_kt tmp = *start_entry;
        *start_entry = *next_entry;
        *next_entry = tmp;
        isTouched  = 1;
      }

      start_entry--;
    }

    if( !isTouched )
      break;
  }
}

void* k_malloc(size_kt size)
{
  size = (size+7) & 0xFFFFFFFFFFFFFFF8ull;  //align to 8
  ptr_kt free_addr = (ptr_kt)&heap_start;
  struct malloc_entry_kt* start_entry = impl_alloc_first_entry();
  struct malloc_entry_kt* free_entry = start_entry;
  struct malloc_entry_kt* entry_iter  = 0;

  //looking for a free chunk of memory
  //  go throug the sorted list of allocated memories
  //    and take the first chunk which fits in size
  entry_iter = start_entry;
  while( entry_iter->size != 0 ) {
      if( free_addr < entry_iter->address && free_addr+size < entry_iter->address)
        break;
      free_addr = entry_iter->address + entry_iter->size;
      entry_iter--;
  }
  //TODO: check if we collide with the data;

  //looking for the next entry
  //  entry table grows downwards  "heap_end"
  //  TODO: add a guard if we collide with the data
  while( free_entry->size != 0) {
    free_entry--;
  }

  free_entry->address = free_addr;
  free_entry->size = size;

  //sorted the entries
  impl_alloc_entry_sort();

  return (void*)free_entry->address;
}

void k_free(void* ptr)
{
	struct malloc_entry_kt* entry_start = impl_alloc_first_entry();
	int entry_count = impl_alloc_entry_count();
	int overwrite = 0;

	for(int i=0; i < entry_count; i++) {
		struct malloc_entry_kt* curr_entry = &entry_start[-i];
		struct malloc_entry_kt* next_entry = &entry_start[-i-1];

		if( ptr == (void*)curr_entry->address) {
			overwrite = 1;
		}

		if( overwrite && i+1 == entry_count) {
			curr_entry->size = 0;
			curr_entry->address = 0;
		}
		else if( overwrite ) {
			*curr_entry = *next_entry;
		}
	}
}
