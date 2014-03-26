#if !defined(__TIME_H__)
#define __TIME_H__

//==============================================================================

#include "time/itime.h"

//==============================================================================

namespace engine
{
	//============================================================================

	namespace time
	{
		class CTime : public ITime
		{
			public:
				SINGLETON(CTime);
				virtual ~CTime(void);

			// ITime
			virtual	const CTimeValue Update(void);
			virtual const CTimeValue GetCurrentTime(void) const;
			virtual ITimer* CreateTimer(ITimer& parent, float maxFrameTime, float scale, CTimeValue& callbackInterval, ITimer::TimerCallback pCallback, void* const pUserData);
			virtual void Sleep(uint32 microseconds);
			// ~ITime

			protected:
			void Initialise(void);
			void Platform_Initialise(void);
			void Platform_Sleep(uint32 microseconds);
			const CTimeValue Platform_GetCurrentTime(void) const;
		}; // End [class CTime : public ITime]

		//============================================================================
	} // End [namespace time]

	//============================================================================
} // End [namespace engine]

//==============================================================================
#endif // !defined(__TIME_H__)
// [EOF]

