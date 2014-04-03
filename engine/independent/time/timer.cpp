#include "common/stdafx.h"

#include "time/time.h"
#include "time/timer.h"

//==============================================================================

namespace engine
{
	namespace time
	{
		//==========================================================================

		CTimer::CTimer(CTimer* pParent, CTimeValue maxFrameTime, float scale, CTimeValue callbackInterval, CTimer::TimerCallback pCallback, void* const pUserData)
			: m_callbackInterval(callbackInterval)
			, m_maxFrameTime(maxFrameTime)
			, m_pParent(pParent)
			, m_pCallback(pCallback)
			, m_pUserData(pUserData)
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

		bool CTimer::Update(CTimeValue elapsed)
		{
			bool active = true;

			if (IsPaused() == false)
			{
				CTimeValue scaledElapsed(static_cast<int64>(static_cast<double>(elapsed.GetTicks())*m_scale));
				CTimeValue frameTime = (scaledElapsed < m_maxFrameTime) ? scaledElapsed : m_maxFrameTime;
				m_timeLast = m_timeNow;
				m_timeNow += frameTime;
				m_timeElapsed += frameTime;
				m_callbackTicker -= frameTime;
				if (m_callbackTicker.GetTicks() <= 0L)
				{
					active = m_pCallback(this, m_pUserData);
					m_callbackTicker += m_callbackInterval;
				}
			}

			return active;
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
			m_callbackTicker = m_callbackInterval;
		}

		//==========================================================================
	} // End [namespace time]

	//============================================================================
} // End [namespace engine]

//==============================================================================
// [EOF]

