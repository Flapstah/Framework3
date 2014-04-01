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
			typedef bool (*TimerCallback)(CTimer*, void* const);

			~CTimer(void);

			CTimeValue GetCurrentTime(void) const;
			CTimeValue GetElapsedTime(void) const;
			CTimeValue GetFrameTime(void) const;
			bool Update(CTimeValue elapsed);
			void SetScale(float scale);
			float GetScale(void) const;
			void Pause(bool pause);
			bool IsPaused(void);
			void Reset(const CTimeValue& when);

			//------------------------------------------------------------------------

		private:
			CTimer(CTimer* pParent, float maxFrameTime, float scale, float callbackInterval, CTimer::TimerCallback pCallback, void* const pUserData);

			//------------------------------------------------------------------------

			CTimeValue m_timeNow;
			CTimeValue m_timeLast;
			CTimeValue m_timeElapsed;

			CTimer* m_pParent;
			TimerCallback m_pCallback;
			void* const m_pUserData;

			float m_callbackInterval;
			float m_callbackTicker;
			float m_maxFrameTime;
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

