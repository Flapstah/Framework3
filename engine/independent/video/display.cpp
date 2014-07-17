#include "common/stdafx.h" // log.h included here

#include "video/display.h"

//==============================================================================

namespace engine
{
	//============================================================================

	namespace video
	{
		//==========================================================================

		void glfwErrorCallback(int error, const char* description)
		{
			LOG_ERROR(ENGINE_LOGGER, "[GLFW] [%d] [%s]", error, description);
		}

		//==========================================================================

		CDisplay::CDisplay(void)
			: m_window(NULL)
		{
			glfwSetErrorCallback(glfwErrorCallback);
		}

		//==========================================================================

		CDisplay::~CDisplay(void)
		{
			Uninitialise();
		}

		//==========================================================================

		bool CDisplay::Initialise(uint32 width, uint32 height, const char* title, bool fullScreen)
		{
			bool ok = false;

			if (glfwInit())
			{
				glfwWindowHint(GLFW_DEPTH_BITS, 32);
				m_window = glfwCreateWindow(width, height, title, NULL, NULL);
				if (m_window != NULL)
				{
					glfwSwapInterval(0);

					glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
					glShadeModel(GL_FLAT);

					// Do texture stuff (http://www.gamedev.net/page/resources/_/reference/programming/opengl/269/opengl-texture-mapping-an-introduction-r947)
					glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
					glBindTexture(GL_TEXTURE_2D, eTID_Main);
					glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
					glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);
					glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
					glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);

					ok = true;
				}
				else
				{
					LOG_ALWAYS(ENGINE_LOGGER, "Failed to open GLFW window");
				}
			}
			else
			{
				LOG_ALWAYS(ENGINE_LOGGER, "Failed to initialise GLFW");
			}

			return ok;
		}

		//==========================================================================

		bool CDisplay::Uninitialise(void)
		{
			glfwTerminate();
			return true;
		}

		//==========================================================================

		bool CDisplay::Update(void)
		{
			int width, height;

			// Get window size (and protect against height being 0)
			glfwGetWindowSize(m_window, &width, &height);
			height = (height > 0) ? height : 1;

			// Set up view
			glViewport(0, 0, width, height);
			glMatrixMode(GL_PROJECTION);
			glLoadIdentity();
//			gluOrtho2D(0.0, (GLdouble)width, 0.0, (GLdouble)height);

			// Clear back buffer
			glClear(GL_COLOR_BUFFER_BIT);

			// Select texture
			glEnable(GL_TEXTURE_2D);
			glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE);
			glBindTexture(GL_TEXTURE_2D, eTID_Main);
			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, eDS_WIDTH, eDS_HEIGHT, 0, GL_RGBA, GL_UNSIGNED_BYTE, m_memory);

			int32 scaledWidth = eDS_WIDTH;
			int32 scaledHeight = eDS_HEIGHT;
			int32 x = (width - scaledWidth) / 2;
			int32 y = (height - scaledHeight) / 2;

			// Render textured quad
			glBegin(GL_QUADS);
			{
				glTexCoord2f(0.0f, 1.0f);
				glVertex2i(x, y);
				glTexCoord2f(0.0f, 0.0f);
				glVertex2i(x, y + scaledHeight);
				glTexCoord2f(1.0f, 0.0f);
				glVertex2i(x + scaledWidth, y + scaledHeight);
				glTexCoord2f(1.0f, 1.0f);
				glVertex2i(x + scaledWidth, y);
			}
			glEnd();

			glfwSwapBuffers(m_window);
			glDisable(GL_TEXTURE_2D);

			bool cont = (glfwWindowShouldClose(m_window) == GL_TRUE) ? false : true;

			return cont;
		}

		//==========================================================================
	} // End [namespace video]

	//============================================================================
} // End [namespace engine]

//==============================================================================
// EOF


