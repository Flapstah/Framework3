#if !defined(__FPSCALCULATOR_H__)
#define __FPSCALCULATOR_H__

//==============================================================================
#include "timevalue.h"

//==============================================================================
namespace engine
{
	//============================================================================
	namespace time
	{
		//==========================================================================
		class CFPSCalculator
		{
			//------------------------------------------------------------------------
		public:
			CFPSCalculator(void);
			~CFPSCalculator(void) {};

			void Update(CTimeValue elapsed);

			// N.B. If GetAverageFPS() is called in the very first frame, you'll get a divide-by-zero exception
			inline float GetAverageFPS(void) { return 1.0f / GetAverageFrameTime(); }
			inline float GetAverageFrameTime(void) { return m_frameTimeAccumulator.GetSeconds()/(double)TIME_FRAME_TIME_BUFFER_SIZE; }
			inline float GetMinimumFrameTime(void) { return m_minFrameTime.GetSeconds(); }
			inline float GetMaximumFrameTime(void) { return m_maxFrameTime.GetSeconds(); }

			//------------------------------------------------------------------------
		private:
			CTimeValue m_frameTimes[TIME_FRAME_TIME_BUFFER_SIZE];
			CTimeValue m_frameTimeAccumulator;
			CTimeValue m_minFrameTime;
			CTimeValue m_maxFrameTime;
			uint32 m_frameIndex;

			//========================================================================
		}; // End [class CFPSCalculator]
		//==========================================================================
	} // End [namespace time]
	//============================================================================
} // End [namespace engine]

//==============================================================================
#endif // !defined(__FPSCALCULATOR_H__)
// [EOF]

