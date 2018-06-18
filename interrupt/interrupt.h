#ifndef INTERRUPT_H
#define INTERRUPT_H

#include "../typedefs.h"
#include <functional>

namespace NsInterrupt
{
	#define EXCEPTION_ENTRY(aOffset, aName) aName = aOffset,
	enum class exception_entry_e
	{
		#include "exception_entries.h"
	};
	#undef EXCEPTION_ENTRY

	constexpr u32_t MAX_EXEPTIONS = 1024;

	void set_handler(int aIrqNum, std::function<void()> aHndler);
	void set_enabled(int aIrqNum, bool aEnable);


}


#endif //INTERRUPT_H
