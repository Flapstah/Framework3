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
			friend class CTime;

		public:
			~CTimer(void);

			CTimeValue GetCurrentTime(void) const;
			CTimeValue GetElapsedTime(void) const;
			CTimeValue GetFrameTime(void) const;
			void Update(const CTimeValue elapsed);
			void SetScale(float scale);
			float GetScale(void) const;
			CTimeValue GetCallbackInterval(void) const;
			void SetCallbackInterval(CTimeValue interval);
			void Pause(bool pause);
			bool IsPaused(void);
			void Reset(const CTimeValue& when);

			//------------------------------------------------------------------------

		private:
			CTimer(const CTimer* pParent, CTimeValue maxFrameTime, float scale, CTimeValue callbackInterval, engine::utility::CCallbackBase& callback);

			//------------------------------------------------------------------------

			CTimeValue m_timeNow;
			CTimeValue m_timeElapsed;

			CTimeValue m_callbackInterval;
			CTimeValue m_callbackTicker;
			CTimeValue m_timeLastCallback;
			CTimeValue m_timePreviousCallback;
			CTimeValue m_maxFrameTime;

			const CTimer* m_pParent;
			engine::utility::CCallbackBase& m_callback;

			float m_scale;

			enum eFlags
			{
				TF_PAUSED							= 1 << 0,
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

