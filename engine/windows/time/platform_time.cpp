#include "common/stdafx.h"

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

		// Set properly during platform initialisation
		int64 g_platformTicksPerSecond = 1;

		// Base time to add high resolution timer to in order that GetCurrentTime()
		// will return current time rather than time elapsed since the PC was turned
		// on.
		static int64 g_baseTime;

		//==========================================================================

		void CTime::Platform_Initialise(void)
		{
			TRACE(TRACE_ENABLE);

			LARGE_INTEGER frequency;

			::QueryPerformanceFrequency(&frequency);
			g_platformTicksPerSecond = static_cast<uint64>(frequency.QuadPart);

			// Grab current system time (in 100ns units) and convert it to local time
			FILETIME baseTime;
			::GetSystemTimeAsFileTime(&baseTime);
			FILETIME localTime;
			::FileTimeToLocalFileTime(&baseTime, &localTime);

			// Grab high performance tick count since machine was turned on
			LARGE_INTEGER time;
			::QueryPerformanceCounter(&time);

			int64 ns100 = localTime.dwHighDateTime;
			ns100 <<= 32;
			ns100 |= localTime.dwLowDateTime;

			double ticksPer100Nanoseconds = static_cast<double>(frequency.QuadPart) / 10000000.0;
			double base100nsTicks = static_cast<double>(ns100)-(static_cast<double>(time.QuadPart)/ticksPer100Nanoseconds);
			g_baseTime = static_cast<int64>(base100nsTicks*ticksPer100Nanoseconds);
		}

		//==========================================================================

		const CTimeValue CTime::Platform_GetCurrentTime() const
		{
			TRACE(TRACE_ENABLE);

			LARGE_INTEGER time;
			::QueryPerformanceCounter(&time);

			time.QuadPart += g_baseTime;
			CTimeValue currentTime(static_cast<int64>(time.QuadPart));

			return currentTime;
		}

		//==========================================================================

		void CTime::Platform_Sleep(uint32 microseconds)
		{
			TRACE(TRACE_ENABLE);

			// round up to the nearest 1/2 millisecond
			uint32 milliseconds = (microseconds+500)/1000;
			if ((milliseconds == 0) && (microseconds > 0))
			{
				milliseconds = 1;
			}

			::Sleep(milliseconds);
		}

		//==========================================================================
	} // End [namespace time]

	//============================================================================
} // End [namespace engine]

//==============================================================================
// [EOF]

