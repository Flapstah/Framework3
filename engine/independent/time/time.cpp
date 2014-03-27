#include "common/stdafx.h"

#include "time/time.h"

//==============================================================================

namespace engine
{
	//============================================================================

	namespace time
	{
		//==========================================================================

		CTime::CTime(void)
		{
			Platform_Initialise();
		}

		//==========================================================================

		CTime::~CTime(void)
		{
		}

		//==========================================================================

		const CTimeValue CTime::Update(void)
		{
			//TODO: pump elapsed time here (capped to some maximum value)
			return INVALID_TIME;
		}

		//==========================================================================

		const CTimeValue CTime::GetCurrentTime(void) const
		{
			return Platform_GetCurrentTime();
		}

		//==========================================================================

		CTimer* CTime::CreateTimer(CTimer& parent, float maxFrameTime, float scale, CTimeValue& callbackInterval, CTimer::TimerCallback pCallback, void* const pUserData)
		{
			IGNORE_PARAMETER(parent);
			IGNORE_PARAMETER(maxFrameTime);
			IGNORE_PARAMETER(scale);
			IGNORE_PARAMETER(callbackInterval);
			IGNORE_PARAMETER(pCallback);
			IGNORE_PARAMETER(pUserData);
			return NULL;
		}

		//==========================================================================

		void CTime::Sleep(uint32 microseconds)
		{
			Platform_Sleep(microseconds);
		}

		//==========================================================================

		void CTime::Initialise(void)
		{
			Platform_Initialise();
		}

		//==========================================================================
	} // End [namespace time]

	//============================================================================
} // End [namespace engine]

//==============================================================================
// [EOF]

