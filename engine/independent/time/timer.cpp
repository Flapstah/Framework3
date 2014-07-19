#include "common/stdafx.h"

#include "time/time.h"
#include "time/timer.h"

//==============================================================================

#if defined(TRACE_ENABLE)
#undef TRACE_ENABLE
#endif // defined(TRACE_ENABLE)
#define TRACE_ENABLE false

//==============================================================================

namespace engine
{
	namespace time
	{
		//==========================================================================

		CTimer::CTimer(const CTimer* pParent, CTimeValue maxFrameTime, float scale, CTimeValue callbackInterval, engine::utility::CCallbackBase& callback)
			: m_callbackInterval(callbackInterval)
			, m_maxFrameTime(maxFrameTime)
			, m_pParent(pParent)
			, m_callback(callback)
			, m_scale(scale)
			, m_flags(0)
		{
			TRACE(TRACE_ENABLE);

			Reset(INVALID_TIME);
		}

		//==========================================================================

		CTimer::~CTimer(void)
		{
			TRACE(TRACE_ENABLE);
		}

		//==========================================================================

		CTimeValue CTimer::GetCurrentTime(void) const
		{
			TRACE(TRACE_ENABLE);

			return m_timeNow;
		}

		//==========================================================================

		CTimeValue CTimer::GetElapsedTime(void) const
		{
			TRACE(TRACE_ENABLE);

			return m_timeElapsed;
		}

		//==========================================================================

		CTimeValue CTimer::GetFrameTime(void) const
		{
			TRACE(TRACE_ENABLE);

			return (m_timeLastCallback - m_timePreviousCallback);
		}

		//==========================================================================

		void CTimer::Update(CTimeValue elapsed)
		{
			TRACE(TRACE_ENABLE);

			if (IsPaused() == false)
			{
				CTimeValue scaledElapsed(static_cast<int64>(static_cast<double>(elapsed.GetTicks())*m_scale));
				CTimeValue frameTime = (scaledElapsed > m_maxFrameTime) ? m_maxFrameTime : scaledElapsed;
				m_timeNow += frameTime;
				m_timeElapsed += frameTime;
				m_callbackTicker -= frameTime;
				if (m_callbackTicker.GetTicks() <= 0L)
				{
					m_timePreviousCallback = m_timeLastCallback;
					m_timeLastCallback = m_timeNow;

					m_callback((void*)this);
					m_callbackTicker += m_callbackInterval;
				}
			}
		}

		//==========================================================================

		void CTimer::SetScale(float scale)
		{
			TRACE(TRACE_ENABLE);

			m_scale = scale;
		}

		//==========================================================================

		float CTimer::GetScale(void) const
		{
			TRACE(TRACE_ENABLE);

			return m_scale;
		}

		CTimeValue CTimer::GetCallbackInterval(void) const
		{
			return m_callbackInterval;
		}

		//==========================================================================

		void CTimer::SetCallbackInterval(CTimeValue interval)
		{
			m_callbackInterval = interval;
		}

		//==========================================================================

		void CTimer::Pause(bool pause)
		{
			TRACE(TRACE_ENABLE);

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
			TRACE(TRACE_ENABLE);

			return ((m_flags & TF_PAUSED) == TF_PAUSED);
		}

		//==========================================================================

		void CTimer::Reset(const CTimeValue& when)
		{
			TRACE(TRACE_ENABLE);

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

			m_timeElapsed = DECLARE_64BIT(0);
			m_callbackTicker = m_callbackInterval;
			m_timeLastCallback = m_timeNow;
			m_timePreviousCallback = m_timeLastCallback - m_callbackInterval;
		}

		//==========================================================================
	} // End [namespace time]

	//============================================================================
} // End [namespace engine]

//==============================================================================
// [EOF]

