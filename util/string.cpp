#include "string.h"

namespace ns_util {

	size_t strlen(const char* aStr)
	{
		if( nullptr == aStr)
			return 0;

		size_t iPos=0;
		while( '\0' != aStr[iPos] ) {
			iPos++;
		}

		return iPos;
	}

} /* namespace NsUtil */
