#if !defined(__GLFW_H__)
#define __GLFW_H__

//==============================================================================

#include <vector>
#include <boost/shared_ptr.hpp>
#include <boost/make_shared.hpp>
#include <GLFW/glfw3.h>

#include "glfw/display.h"
#include "time/time.h"
#include "time/fpscalculator.h"

//==============================================================================

namespace engine
{
	//============================================================================

	namespace glfw
	{
		//==========================================================================
		// Forward declarations
		//==========================================================================

		class CDisplay;

		//==========================================================================
		// SConfiguration
		//==========================================================================
		struct SConfiguration
		{
			SConfiguration(void);
			~SConfiguration(void);

			bool m_continuousUpdate;
			uint32 m_desiredFrameRate;
		}; // End [struct SConfiguration]

		//==========================================================================
		// CGLFW
		//==========================================================================
		class CGLFW
		{
			//========================================================================
			public:
				enum eStatus
				{
					eS_UNINITIALISED,
					eS_RUNNING,
				}; // End [enum eStatus]

				SINGLETON(CGLFW);
				virtual ~CGLFW(void);

				bool Initialise(engine::glfw::SConfiguration& configuration);
				bool Update(void);
				void Uninitialise(void);

				engine::glfw::CDisplay::TDisplayID OpenDisplay(uint32 width, uint32 height, const char* name, bool fullScreen);
				void CloseDisplay(engine::glfw::CDisplay::TDisplayID id);

				//======================================================================
				// FPS
				//======================================================================
				void SetDesiredFramerate(uint32 framerate);
				// N.B. If GetAverageFPS() is called in the very first frame, you'll get a divide-by-zero exception
				inline double GetAverageFPS(void) { return m_fps.GetAverageFPS(); }
				inline double GetAverageFrameTime(void) { return m_fps.GetAverageFrameTime(); }
				inline double GetMinimumFrameTime(void) { return m_fps.GetMinimumFrameTime(); }
				inline double GetMaximumFrameTime(void) { return m_fps.GetMaximumFrameTime(); }
				//======================================================================

			protected:
				void CloseAllDisplays(void);
				void TimerCallback(engine::time::CTimer* pTimer);

				enum eFlags
				{
					eF_NONE = 0,
					eF_CONTINOUS_UPDATE = 1 << 0,
				}; // End [enum eFlags]

				typedef boost::shared_ptr<CDisplay> TCDisplayPtr;
				typedef std::vector<TCDisplayPtr> TDisplayVec;
				TDisplayVec m_display;
				engine::time::CTime::TTimerPtr m_timer;
				engine::time::CFPSCalculator m_fps;
				engine::utility::CUnaryCallback<CGLFW, engine::time::CTimer> m_callback;
				eFlags m_flags;
				eStatus m_status;

			//========================================================================
		}; // End [class CGLFW]

		//==========================================================================
	} // End [namespace glfw]

	//============================================================================
} // End [namespace engine]

//==============================================================================
#endif // End [!defined(__GLFW_H__)]
// [EOF]


