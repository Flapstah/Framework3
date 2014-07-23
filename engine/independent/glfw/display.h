#if !defined(__DISPLAY_H__)
#define __DISPLAY_H__

//==============================================================================

#include <GLFW/glfw3.h>

#include "time/time.h"

//==============================================================================

#define INVALID_DISPLAY_ID (0xffffffff)

//==============================================================================

namespace engine
{
	//============================================================================

	namespace glfw
	{
		//==========================================================================
		// CDisplay
		//==========================================================================
		class CDisplay
		{
			//========================================================================
			public:
				typedef uint32 TDisplayID;

				CDisplay(void);
				TDisplayID Open(uint32 width, uint32 height, const char* title, bool fullScreen);
				void Close(void);
				~CDisplay(void);

				bool Update(engine::time::CTimer* pTimer);
				TDisplayID GetID(void) const { return m_id; }
				GLFWwindow* GetGLFWwindow(void) const { return m_window; }

				//----------------------------------------------------------------------

				// GLFW callbacks
				virtual bool glfwKeyCallback(int key, int scancode, int action, int mods);
				void glfwFramebufferSizeCallback(int width, int height);

				//----------------------------------------------------------------------

			protected:
				GLFWwindow* m_window;
				TDisplayID m_id;
				int m_width;
				int m_height;
				bool m_active;

				static TDisplayID s_id;

			//========================================================================
		}; // End [class CDisplay]

		//==========================================================================
	} // End [namespace glfw]

	//============================================================================
} // End [namespace engine]

//==============================================================================
#endif // End [!defined(__DISPLAY_H__)]
// EOF


