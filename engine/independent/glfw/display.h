#if !defined(__DISPLAY_H__)
#define __DISPLAY_H__

//==============================================================================

#include <GLFW/glfw3.h>

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

				bool Update(void);
				TDisplayID GetID(void) const { return m_id; }

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
				TDisplayID m_id;
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


