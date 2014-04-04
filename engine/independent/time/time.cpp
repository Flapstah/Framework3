#include "common/stdafx.h"

#include "time/time.h"

//==============================================================================

namespace engine
{
	//============================================================================

	namespace time
	{
		//==========================================================================

		CTime::CTime(void)
			: m_frameIndex(0)
		{
			memset(m_frameTimes, 0, sizeof(m_frameTimes));

			Platform_Initialise();
			m_lastUpdate = GetCurrentTime();
		}

		//==========================================================================

		CTime::~CTime(void)
		{
			if (m_timers.empty() == false)
			{
				LOG_ERROR(ENGINE_LOGGER, "CTime still has timers attached at destruction");
			}
		}

		//==========================================================================

		const CTimeValue CTime::Update(void)
		{
			CTimeValue now = GetCurrentTime();
			CTimeValue elapsed = now - m_lastUpdate;
			m_lastUpdate = now;

			for (TTimerDeque::iterator it = m_timers.begin(), end = m_timers.end(); it != end; ++it)
			{
				it->get()->Update(elapsed);
			}

			m_frameTimeAccumulator -= m_frameTimes[m_frameIndex];
			m_frameTimeAccumulator += elapsed;

			m_frameTimes[m_frameIndex] = elapsed;
			m_frameIndex = ++m_frameIndex & (TIME_FRAME_TIME_BUFFER_SIZE-1);

			if (elapsed < m_minFrameTime)
			{
				m_minFrameTime = elapsed;
			}

			if (elapsed > m_maxFrameTime)
			{
				m_maxFrameTime = elapsed;
			}

			return elapsed;
		}

		//==========================================================================

		const CTimeValue CTime::GetCurrentTime(void) const
		{
			return Platform_GetCurrentTime();
		}

		//==========================================================================

		CTime::TTimerPtr CTime::CreateTimer(CTimeValue maxFrameTime, float scale, CTimeValue callbackInterval, CTimer::TimerCallback pCallback, void* const pUserData)
		{
			TTimerPtr timer = boost::make_shared<CTimer>(CTimer(NULL, maxFrameTime, scale, callbackInterval, pCallback, pUserData));
			m_timers.push_back(timer);
			return timer;
		}

		//==========================================================================

		CTime::TTimerPtr CTime::CreateTimer(TTimerPtr parent, CTimeValue maxFrameTime, float scale, CTimeValue callbackInterval, CTimer::TimerCallback pCallback, void* const pUserData)
		{
			TTimerPtr timer = boost::make_shared<CTimer>(CTimer(parent.get(), maxFrameTime, scale, callbackInterval, pCallback, pUserData));
			m_timers.push_back(timer);
			return timer;
		}

		//==========================================================================

		void CTime::DestroyTimer(TTimerPtr timer)
		{
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
			Platform_Sleep(microseconds);
		}

		//==========================================================================

		void CTime::Initialise(void)
		{
			Platform_Initialise();
		}

		//==========================================================================
	} // End [namespace time]

	//============================================================================
} // End [namespace engine]

//==============================================================================
// [EOF]

