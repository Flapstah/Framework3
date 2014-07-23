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
			inline double GetAverageFPS(void) const { return 1.0 / GetAverageFrameTime(); }
			inline double GetAverageFrameTime(void) const { return m_frameTimeAccumulator.GetSeconds()/(double)TIME_FPS_FRAME_BUFFER_SIZE; }
			inline double GetMinimumFrameTime(void) const { return m_minFrameTime.GetSeconds(); }
			inline double GetMaximumFrameTime(void) const { return m_maxFrameTime.GetSeconds(); }

			//------------------------------------------------------------------------
		private:
			CTimeValue m_frameTimes[TIME_FPS_FRAME_BUFFER_SIZE];
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

