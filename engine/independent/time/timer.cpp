#include "common/stdafx.h"

#include "time/time.h"
#include "time/timer.h"

//==============================================================================

namespace engine
{
	namespace time
	{
		//==========================================================================

		CTimer::CTimer(CTimer* pParent, float maxFrameTime, float scale, CTimeValue& callbackInterval, CTimer::TimerCallback pCallback, void* const pUserData)
			: m_callbackInterval(callbackInterval)
			, m_pParent(pParent)
			, m_pCallback(pCallback)
			, m_pUserData(pUserData)
			,	m_maxFrameTime(maxFrameTime)
			, m_scale(scale)
			, m_flags(0)
		{
			Reset(INVALID_TIME);
		}

		//==========================================================================

		CTimer::~CTimer(void)
		{
		}

		//==========================================================================

		CTimeValue CTimer::GetCurrentTime(void) const
		{
			return m_timeNow;
		}

		//==========================================================================

		CTimeValue CTimer::GetElapsedTime(void) const
		{
			return m_timeElapsed;
		}

		//==========================================================================

		CTimeValue CTimer::GetFrameTime(void) const
		{
			return (m_timeNow-m_timeLast);
		}

		//==========================================================================

		float CTimer::GetMaxFrameTime(void) const
		{
			return m_maxFrameTime;
		}

		//==========================================================================

		void CTimer::SetMaxFrameTime(float maxFrameTime)
		{
			m_maxFrameTime = maxFrameTime;
		}

		//==========================================================================

		void CTimer::SetScale(float scale)
		{
			m_scale = scale;
		}

		//==========================================================================

		float CTimer::GetScale(void) const
		{
			return m_scale;
		}

		//==========================================================================

		void CTimer::Pause(bool pause)
		{
			if (pause)
			{
				m_flags |= TF_PAUSED;
			}
			else
			{
				m_flags &= ~TF_PAUSED;
			}
		}

		//==========================================================================

		bool CTimer::IsPaused(void)
		{
			return ((m_flags & TF_PAUSED) == TF_PAUSED);
		}

		//==========================================================================

		void CTimer::SuspendCallbacks(bool suspend)
		{
			if (suspend)
			{
				m_flags |= TF_SUSPEND_CALLBACKS;
			}
			else
			{
				m_flags &= ~TF_SUSPEND_CALLBACKS;
			}
		}

		//==========================================================================

		bool CTimer::HasSuspendedCallbacks(void)
		{
			return ((m_flags & TF_SUSPEND_CALLBACKS) == TF_SUSPEND_CALLBACKS);
		}

		//==========================================================================

		void CTimer::Reset(const CTimeValue& when)
		{
			if (when == INVALID_TIME)
			{
				if (m_pParent != NULL)
				{
					m_timeNow = m_pParent->GetCurrentTime();
				}
				else
				{
					m_timeNow = CTime::Get().GetCurrentTime();
				}
			}
			else
			{
				m_timeNow = when;
			}

			m_timeLast = m_timeNow;
			m_timeElapsed = DECLARE_64BIT(0);
		}

		//==========================================================================

		void CTimer::SetCallbackInterval(const CTimeValue& interval)
		{
			m_callbackInterval = interval;
		}

		//==========================================================================

		const CTimeValue& CTimer::GetCallbackInterval(void)
		{
			return m_callbackInterval;
		}

		//==========================================================================
	} // End [namespace time]

	//============================================================================
} // End [namespace engine]

//==============================================================================
// [EOF]

