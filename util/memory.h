#ifndef UTIL_MEMORY_H_
#define UTIL_MEMORY_H_
#include "../typedefs.h"

extern "C" {
	//-------------------------------
	// allocate memory
	//-------------------------------

	//! returns a pointer to allocated memory or NULL
	void* k_malloc(size_t size);

	//! free allocated memory
	void k_free(void* ptr);
}

#endif /* UTIL_MEMORY_H_ */
