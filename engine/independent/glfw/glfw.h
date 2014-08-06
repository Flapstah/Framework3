#if !defined(__GLFW_H__)
#define __GLFW_H__

//==============================================================================

#include <map>
#include <boost/shared_ptr.hpp>
#include <boost/make_shared.hpp>

#include "glfw/display.h"
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

			bool m_realtime;
			bool m_vsync;
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
				bool Update(engine::time::CTimer* pTimer);
				void Uninitialise(void);

				engine::glfw::CDisplay::TDisplayID OpenDisplay(uint32 width, uint32 height, const char* name, bool fullScreen);
				void CloseDisplay(engine::glfw::CDisplay::TDisplayID id);

				const engine::time::CFPSCalculator* GetFPS(void) const;
				void SetDesiredFramerate(uint32 framerate);

				//----------------------------------------------------------------------

				// GLFW callbacks
				void glfwKeyCallback(GLFWwindow* window, int key, int scancode, int action, int mods);
				void glfwFramebufferSizeCallback(GLFWwindow* window, int width, int height);

				//----------------------------------------------------------------------

			protected:
				void CloseAllDisplays(void);
				void SetDisplayCallbacks(GLFWwindow* window, bool set);
				void TimerCallback(engine::time::CTimer* pTimer);

				enum eFlags
				{
					eF_NONE = 0,
					eF_REALTIME = 1 << 0,
				}; // End [enum eFlags]

				typedef boost::shared_ptr<CDisplay> TCDisplayPtr;
				typedef std::map<GLFWwindow*, TCDisplayPtr> TDisplayMap;
				TDisplayMap m_display;
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


