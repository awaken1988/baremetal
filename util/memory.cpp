#include "memory.h"

//-------------------------------
//
// allocate memory
//
//-------------------------------
extern char heap_start;
extern char heap_end;

struct malloc_entry_kt
{
	uptr_t address;
	size_t size;
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

void* k_malloc(size_t size)
{
  size = (size+7) & 0xFFFFFFFFFFFFFFF8ull;  //align to 8
  uptr_t free_addr = (uptr_t)&heap_start;
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



//-------------------------------
//
// C++ new/delete
//
//-------------------------------
void* operator new(size_t size)
{
    return k_malloc(size);
}

void operator delete(void *p)
{
    k_free(p);
}

void* operator new[](size_t size)
{
    return operator new(size); // Same as regular new
}

void operator delete[](void *p)
{
    operator delete(p); // Same as regular delete
}

