#include "common/stdafx.h"

#include "time/time.h"

//==============================================================================

namespace engine
{
	//============================================================================

	namespace time
	{
		//==========================================================================

		ITime* GetITime(void)
		{
			return &CTime::Get();
		}

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
			return INVALID_TIME;
		}

		//==========================================================================

		const CTimeValue CTime::GetCurrentTime(void) const
		{
			return Platform_GetCurrentTime();
		}

		//==========================================================================

		ITimer* CTime::CreateTimer(ITimer& parent, float maxFrameTime, float scale, CTimeValue& callbackInterval, ITimer::TimerCallback pCallback, void* const pUserData)
		{
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

