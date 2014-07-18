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
			TTimerPtr CreateTimer(CTimeValue maxFrameTime, float scale, CTimeValue callbackInterval, engine::utility::CCallbackBase& callback);
			TTimerPtr CreateTimer(TTimerPtr parent, CTimeValue maxFrameTime, float scale, CTimeValue callbackInterval, engine::utility::CCallbackBase& callback);
			void DestroyTimer(TTimerPtr timer);
			static void Sleep(uint32 microseconds);

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

			//========================================================================
		}; // End [class CTime]

		//============================================================================
	} // End [namespace time]

	//============================================================================
} // End [namespace engine]

//==============================================================================
#endif // !defined(__TIME_H__)
// [EOF]

