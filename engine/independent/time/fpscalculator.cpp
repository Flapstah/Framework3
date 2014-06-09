#include "common/stdafx.h"

#include "fpscalculator.h"

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

		CFPSCalculator::CFPSCalculator(void)
			: m_frameIndex(0)
		{
			TRACE(TRACE_ENABLE);

			memset(m_frameTimes, 0, sizeof(m_frameTimes));
		}

		//==========================================================================

		void CFPSCalculator::Update(CTimeValue elapsed)
		{
			TRACE(TRACE_ENABLE);

			m_frameTimeAccumulator -= m_frameTimes[m_frameIndex];
			m_frameTimeAccumulator += elapsed;

			m_frameTimes[m_frameIndex] = elapsed;
			++m_frameIndex &= (TIME_FPS_FRAME_BUFFER_SIZE-1);

			if (elapsed < m_minFrameTime)
			{
				m_minFrameTime = elapsed;
			}

			if (elapsed > m_maxFrameTime)
			{
				m_maxFrameTime = elapsed;
			}
		}

		//==========================================================================
	} // End [namespace time]

	//============================================================================
} // End [namespace engine]

//==============================================================================
// [EOF]

