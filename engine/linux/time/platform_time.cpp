#include "common/stdafx.h"

#include <boost/thread.hpp>
#include <sys/time.h>		// gettimeofday

#include "time/time.h"

//==============================================================================

#if defined(TRACE_ENABLE)
#undef TRACE_ENABLE
#endif // defined(TRACE_ENABLE)
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

			boost::this_thread::sleep_for(boost::chrono::microseconds(microseconds));
		}

		//==========================================================================
	} // End [namespace time]

	//============================================================================
} // End [namespace engine]

//==============================================================================
// [EOF]
