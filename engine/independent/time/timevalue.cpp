#include "common/stdafx.h"

#include "common/itime.h"

//==============================================================================

namespace engine
{
	namespace time
	{
		//==========================================================================

		extern int64 g_platformTicksPerSecond;
		const int64& g_kTICKS_PER_SECOND = g_platformTicksPerSecond;
		const CTimeValue INVALID_TIME(int64(DECLARE_64BIT(0xf000000000000000)));

		//==========================================================================

		void CTimeValue::GetTime(int32& days, int32& hours, int32& minutes, float& seconds)
		{
			// remove sign (2's complement); user calls GetTicks() to determine the sign
			int64 time = m_ticks;
			int64 mask = m_ticks >> 63;
			time = (time ^ mask) - mask;

			int64 unit = g_kTICKS_PER_SECOND*60*60*24; // ticks per day
			days = time/unit;
			time -= unit*days;

			unit /= 24; // ticks per hour
			hours = time/unit;
			time -= unit*hours;

			unit /= 60; // ticks per minute
			minutes = time/unit;
			seconds = static_cast<float>(time-(unit*minutes))/g_kTICKS_PER_SECOND;
		}

		//==========================================================================
	} // End [namespace time]

	//============================================================================
} // End [namespace engine]

//==============================================================================
// [EOF]

