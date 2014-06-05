#include "common/stdafx.h"

#include <unistd.h>			// usleep
#include <sys/time.h>		// gettimeofday

#include "time/time.h"

//==============================================================================

#define TRACE_ENABLE false

//==============================================================================

namespace engine
{
	//============================================================================

	namespace time
	{
		//==========================================================================

		int64 g_platformTicksPerSecond = DECLARE_64BIT(1000000);

		//==========================================================================

		void CTime::Platform_Initialise(void)
		{
			TRACE(TRACE_ENABLE);
		}

		//==========================================================================

		const CTimeValue CTime::Platform_GetCurrentTime() const
		{
			TRACE(TRACE_ENABLE);

			::timeval time;
			::gettimeofday(&time, NULL);

			CTimeValue currentTime(static_cast<double>(time.tv_sec));
			currentTime += static_cast<int64>(time.tv_usec);

			return currentTime;
		}

		//==========================================================================

		void CTime::Platform_Sleep(uint32 microseconds)
		{
			TRACE(TRACE_ENABLE);

			::usleep(microseconds);
		}

		//==========================================================================
	} // End [namespace time]

	//============================================================================
} // End [namespace engine]

//==============================================================================
// [EOF]
