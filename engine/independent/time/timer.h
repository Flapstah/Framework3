#if !defined(__TIMER_H__)
#define __TIMER_H__

//==============================================================================

#include "common/itime.h"

//==============================================================================

namespace engine
{
	namespace time
	{
		//==========================================================================
		// CTimer
		//==========================================================================
		class CTimer : public ITimer
		{
			public:

			// ITimer
			virtual CTimeValue GetCurrentTime(void) const;
			virtual CTimeValue GetElapsedTime(void) const;
			virtual CTimeValue GetFrameTime(void) const;
			virtual float GetMaxFrameTime(void) const;
			virtual void SetMaxFrameTime(float maxFrameTime);
			virtual void SetScale(float scale);
			virtual float GetScale(void) const;
			virtual void Pause(bool pause);
			virtual void Reset(const CTimeValue& when);
			virtual void SetCallbackInterval(const CTimeValue& interval);
			virtual const CTimeValue& GetCallbackInterval(void);
			// ~ITimer

			private:
			CTimeValue m_timeNow;
			CTimeValue m_timeLast;
			CTimeValue m_timeElapsed;
			CTimeValue m_callbackInterval;
			CTimeValue m_callbackTicker;

			TimerCallback* m_pCallback;
			void* const m_pUserData;

			enum eFlags
			{
				TF_ACTIVE							= 1 << 0,
				TF_PAUSED							= 1 << 1,
				TF_SUSPEND_CALLBACKS	= 1 << 2
			}; // End [enum eFlags]
			uint32 m_flags;
		}; // End [class CTimer : public ITimer]

		//==========================================================================
	} // End [namespace time]

	//============================================================================
} // End [namespace engine]

//==============================================================================
#endif // !defined(__TIMER_H__)
// [EOF]

