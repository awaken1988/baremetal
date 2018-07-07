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

	class Interrupt
	{
	public:
		virtual void global_enable() = 0;
		virtual void global_disable() = 0;
		virtual void set_handler(int aIrqNum, std::function<void()> aHndler) = 0;
		virtual void set_enabled(int aIrqNum, bool aEnable) = 0;

	};



}


#endif //INTERRUPT_H
