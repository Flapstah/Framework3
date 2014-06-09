#include "common/stdafx.h"

#include "time/time.h"

//==============================================================================

#if defined(TRACE_ENABLE)
#undef TRACE_ENABLE
#endif // defined(TRACE_ENABLE)
#define TRACE_ENABLE false

//==============================================================================

namespace engine
{
	//============================================================================

	namespace time
	{
		//==========================================================================

		CTime::CTime(void)
		{
			TRACE(TRACE_ENABLE);

			Platform_Initialise();
			m_lastUpdate = GetCurrentTime();
		}

		//==========================================================================

		CTime::~CTime(void)
		{
			TRACE(TRACE_ENABLE);

			if (m_timers.empty() == false)
			{
				LOG_ERROR(ENGINE_LOGGER, "CTime still has timers attached at destruction");
			}
		}

		//==========================================================================

		const CTimeValue CTime::Update(void)
		{
			TRACE(TRACE_ENABLE);

			CTimeValue now = GetCurrentTime();
			CTimeValue elapsed = now - m_lastUpdate;
			m_lastUpdate = now;

			for (TTimerDeque::iterator it = m_timers.begin(), end = m_timers.end(); it != end; ++it)
			{
				it->get()->Update(elapsed);
			}

			return elapsed;
		}

		//==========================================================================

		const CTimeValue CTime::GetCurrentTime(void) const
		{
			TRACE(TRACE_ENABLE);

			return Platform_GetCurrentTime();
		}

		//==========================================================================

		CTime::TTimerPtr CTime::CreateTimer(CTimeValue maxFrameTime, float scale, CTimeValue callbackInterval, CTimer::TimerCallback pCallback, void* const pUserData)
		{
			TRACE(TRACE_ENABLE);

			TTimerPtr timer = boost::make_shared<CTimer>(CTimer(NULL, maxFrameTime, scale, callbackInterval, pCallback, pUserData));
			m_timers.push_back(timer);
			return timer;
		}

		//==========================================================================

		CTime::TTimerPtr CTime::CreateTimer(TTimerPtr parent, CTimeValue maxFrameTime, float scale, CTimeValue callbackInterval, CTimer::TimerCallback pCallback, void* const pUserData)
		{
			TRACE(TRACE_ENABLE);

			TTimerPtr timer = boost::make_shared<CTimer>(CTimer(parent.get(), maxFrameTime, scale, callbackInterval, pCallback, pUserData));
			m_timers.push_back(timer);
			return timer;
		}

		//==========================================================================

		void CTime::DestroyTimer(TTimerPtr timer)
		{
			TRACE(TRACE_ENABLE);

			for (TTimerDeque::iterator it = m_timers.begin(), end = m_timers.end(); it != end; ++it)
			{
				if (*it == timer)
				{
					m_timers.erase(it);
					break;
				}
			}

			return;
		}
		//==========================================================================

		void CTime::Sleep(uint32 microseconds)
		{
			TRACE(TRACE_ENABLE);

			Platform_Sleep(microseconds);
		}

		//==========================================================================

		void CTime::Initialise(void)
		{
			TRACE(TRACE_ENABLE);

			Platform_Initialise();
		}

		//==========================================================================
	} // End [namespace time]

	//============================================================================
} // End [namespace engine]

//==============================================================================
// [EOF]

