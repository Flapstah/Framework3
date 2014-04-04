#if !defined(__TIME_H__)
#define __TIME_H__

//==============================================================================

#include "time/timer.h"
#include "time/timevalue.h"

#include <deque>
#include <boost/shared_ptr.hpp>
#include <boost/make_shared.hpp>

//==============================================================================

namespace engine
{
	//============================================================================

	namespace time
	{
		//==========================================================================
		// CTime
		//==========================================================================
		class CTime
		{
			//------------------------------------------------------------------------

		public:

			typedef boost::shared_ptr<CTimer> TTimerPtr;

			//------------------------------------------------------------------------

		public:
			SINGLETON(CTime);
			~CTime(void);

			const CTimeValue Update(void);
			const CTimeValue GetCurrentTime(void) const;
			TTimerPtr CreateTimer(CTimeValue maxFrameTime, float scale, CTimeValue callbackInterval, CTimer::TimerCallback pCallback, void* const pUserData);
			TTimerPtr CreateTimer(TTimerPtr parent, CTimeValue maxFrameTime, float scale, CTimeValue callbackInterval, CTimer::TimerCallback pCallback, void* const pUserData);
			void DestroyTimer(TTimerPtr timer);
			static void Sleep(uint32 microseconds);

			// N.B. If GetAverageFPS() is called in the very first frame, you'll get a divide-by-zero exception
			inline float GetAverageFPS(void) { return 1.0f / GetAverageFrameTime(); }
			inline float GetAverageFrameTime(void) { return m_frameTimeAccumulator.GetSeconds()/(double)TIME_FRAME_TIME_BUFFER_SIZE; }
			inline float GetMinimumFrameTime(void) { return m_minFrameTime.GetSeconds(); }
			inline float GetMaximumFrameTime(void) { return m_maxFrameTime.GetSeconds(); }

			//------------------------------------------------------------------------

		protected:
			void Initialise(void);
			void Platform_Initialise(void);
			static void Platform_Sleep(uint32 microseconds);
			const CTimeValue Platform_GetCurrentTime(void) const;

			//------------------------------------------------------------------------

			typedef std::deque<TTimerPtr> TTimerDeque;
			TTimerDeque m_timers;

			CTimeValue m_lastUpdate;

			CTimeValue m_frameTimes[TIME_FRAME_TIME_BUFFER_SIZE];
			CTimeValue m_frameTimeAccumulator;
			CTimeValue m_minFrameTime;
			CTimeValue m_maxFrameTime;
			uint32 m_frameIndex;

			//========================================================================
		}; // End [class CTime]

		//============================================================================
	} // End [namespace time]

	//============================================================================
} // End [namespace engine]

//==============================================================================
#endif // !defined(__TIME_H__)
// [EOF]

