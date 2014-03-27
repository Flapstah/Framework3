#if !defined(__TIME_H__)
#define __TIME_H__

//==============================================================================

#include "time/timer.h"
#include "time/timevalue.h"

//==============================================================================

namespace engine
{
	//============================================================================

	namespace time
	{
		class CTime
		{
		public:
			SINGLETON(CTime);
			~CTime(void);

			const CTimeValue Update(void);
			const CTimeValue GetCurrentTime(void) const;
			CTimer* CreateTimer(CTimer& parent, float maxFrameTime, float scale, CTimeValue& callbackInterval, CTimer::TimerCallback pCallback, void* const pUserData);
			void Sleep(uint32 microseconds);

			protected:
			void Initialise(void);
			void Platform_Initialise(void);
			void Platform_Sleep(uint32 microseconds);
			const CTimeValue Platform_GetCurrentTime(void) const;
		}; // End [class CTime]

		//============================================================================
	} // End [namespace time]

	//============================================================================
} // End [namespace engine]

//==============================================================================
#endif // !defined(__TIME_H__)
// [EOF]

