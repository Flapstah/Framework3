#if !defined(__TIMER_H__)
#define __TIMER_H__

//==============================================================================

#include "time/timevalue.h"

//==============================================================================

namespace engine
{
	//============================================================================

	namespace time
	{
		//==========================================================================
		// CTimer
		//==========================================================================
		class CTimer
		{
		public:
			typedef bool (*TimerCallback)(CTimer*, void* const);

			CTimer(CTimer* pParent, float maxFrameTime, float scale, CTimeValue& callbackInterval, CTimer::TimerCallback pCallback, void* const pUserData);
			~CTimer(void);

			CTimeValue GetCurrentTime(void) const;
			CTimeValue GetElapsedTime(void) const;
			CTimeValue GetFrameTime(void) const;
			float GetMaxFrameTime(void) const;
			void SetMaxFrameTime(float maxFrameTime);
			void SetScale(float scale);
			float GetScale(void) const;
			void Pause(bool pause);
			bool IsPaused(void);
			void SuspendCallbacks(bool suspend);
			bool HasSuspendedCallbacks(void);
			void Reset(const CTimeValue& when);
			void SetCallbackInterval(const CTimeValue& interval);
			const CTimeValue& GetCallbackInterval(void);

			//------------------------------------------------------------------------

		private:
			CTimeValue m_timeNow;
			CTimeValue m_timeLast;
			CTimeValue m_timeElapsed;
			CTimeValue m_callbackInterval;
			CTimeValue m_callbackTicker;

			CTimer* m_pParent;
			TimerCallback m_pCallback;
			void* const m_pUserData;

			float m_maxFrameTime;
			float m_scale;

			enum eFlags
			{
				TF_ACTIVE							= 1 << 0,
				TF_PAUSED							= 1 << 1,
				TF_SUSPEND_CALLBACKS	= 1 << 2
			}; // End [enum eFlags]
			uint32 m_flags;

			//========================================================================
		}; // End [class CTimer]

		//==========================================================================
	} // End [namespace time]

	//============================================================================
} // End [namespace engine]

//==============================================================================
#endif // !defined(__TIMER_H__)
// [EOF]

