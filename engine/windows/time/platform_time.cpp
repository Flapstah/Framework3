#include "common/stdafx.h"

#include "time/time.h"

//==============================================================================

namespace engine
{
	//============================================================================

	namespace time
	{
		//==========================================================================

		// Set properly during platform initialisation
		int64 g_platformTicksPerSecond = 1;

		//==========================================================================

		void CTime::Platform_Initialise(void)
		{
			LARGE_INTEGER frequency;

			::QueryPerformanceFrequency(&frequency);
			g_platformTicksPerSecond = static_cast<uint64>(frequency.QuadPart);
		}

		//==========================================================================

		const CTimeValue CTime::Platform_GetCurrentTime() const
		{
			LARGE_INTEGER time;
			::QueryPerformanceCounter(&time);

			CTimeValue currentTime(static_cast<int64>(time.QuadPart));

			return currentTime;
		}

		//==========================================================================

		void CTime::Platform_Sleep(uint32 microseconds)
		{
			// round up to the nearest 1/2 millisecond
			uint32 milliseconds = (microseconds+500)/1000;
			if ((milliseconds == 0) && (microseconds > 0))
			{
				milliseconds = 0;
			}

			::Sleep(milliseconds);
		}

		//==========================================================================
	} // End [namespace time]

	//============================================================================
} // End [namespace engine]

//==============================================================================
// [EOF]

