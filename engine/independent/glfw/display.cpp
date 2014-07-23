#include "common/stdafx.h" // log.h included here

#include "glfw/display.h"

//==============================================================================

#if defined(TRACE_ENABLE)
#undef TRACE_ENABLE
#endif // defined(TRACE_ENABLE)
#define TRACE_ENABLE false

//==============================================================================

namespace engine
{
	//============================================================================

	namespace glfw
	{
		//==========================================================================

		CDisplay::TDisplayID CDisplay::s_id = 0;

		//==========================================================================

		CDisplay::CDisplay(void)
			: m_window(NULL)
			, m_width(0)
			, m_height(0)
			, m_active(false)
		{
			TRACE(TRACE_ENABLE);
		}

		//==========================================================================

		CDisplay::~CDisplay(void)
		{
			TRACE(TRACE_ENABLE);

			Close();
		}

		//==========================================================================

		CDisplay::TDisplayID CDisplay::Open(uint32 width, uint32 height, const char* title, bool fullScreen)
		{
			TRACE(TRACE_ENABLE);

			m_active = false;
			m_id = INVALID_DISPLAY_ID;

			glfwWindowHint(GLFW_DEPTH_BITS, 32);
			m_window = glfwCreateWindow(width, height, title, (fullScreen == true) ? glfwGetPrimaryMonitor() : NULL, NULL);
			if (m_window != NULL)
			{
				// Make this display the current OpenGL context
				glfwMakeContextCurrent(m_window);

				// Set initial dimensions
				glfwGetFramebufferSize(m_window, &m_width, &m_height);
				glViewport(0, 0, m_width, m_height);

				/*
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
				*/

				m_active = true;
				m_id = s_id++;
			}
			else
			{
				LOG_ERROR(ENGINE_LOGGER, "Failed to open GLFW window");
			}

			return m_id;
		}

		//==========================================================================

		void CDisplay::Close(void)
		{
			TRACE(TRACE_ENABLE);

			if (m_active)
			{
				glfwSetWindowShouldClose(m_window, GL_TRUE);
				m_active = false;
			}
		}

		//==========================================================================

		bool CDisplay::Update(void)
		{
			TRACE(TRACE_ENABLE);

			if (m_active == true)
			{
				// Make this display the current OpenGL context
				glfwMakeContextCurrent(m_window);

				/*
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
				*/
				glfwSwapBuffers(m_window);

				m_active = !glfwWindowShouldClose(m_window);
			}

			return m_active;
		}

		//==========================================================================

		bool CDisplay::glfwKeyCallback(int key, int scancode, int action, int mods)
		{
			IGNORE_PARAMETER(key);
			IGNORE_PARAMETER(scancode);
			IGNORE_PARAMETER(action);
			IGNORE_PARAMETER(mods);
			// N.B. this is a virtual function and can be overridden in derived classes
			// to customise behaviour
			//
			// Returns true if the input event was consumed, otherwise false

			return false;
		}

		//==========================================================================

		void CDisplay::glfwFramebufferSizeCallback(int width, int height)
		{
			m_width = width;
			m_height = height;
			glViewport(0, 0, width, height);
		}

		//==========================================================================
	} // End [namespace glfw]

	//============================================================================
} // End [namespace engine]

//==============================================================================
// EOF


