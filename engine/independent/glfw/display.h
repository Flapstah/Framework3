#if !defined(__DISPLAY_H__)
#define __DISPLAY_H__

//==============================================================================

#include <GLFW/glfw3.h>

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
				CDisplay(void);
				bool Initialise(uint32 width, uint32 height, const char* title, bool fullScreen);
				bool Uninitialise(void);
				~CDisplay(void);

				bool Update(void);

			protected:
				enum eDisplaySize
				{
					eDS_WIDTH = 1024,
					eDS_HEIGHT = 576
				};

				uint32 m_memory[eDS_WIDTH*eDS_HEIGHT];

				enum eTextureID
				{
					eTID_Main = 1
				};

				GLFWwindow* m_window;

			//========================================================================
		}; // End [class CDisplay]

		//==========================================================================
	} // End [namespace glfw]

	//============================================================================
} // End [namespace engine]

//==============================================================================
#endif // End [!defined(__DISPLAY_H__)]
// EOF


