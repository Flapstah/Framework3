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

				// Set up view
				SetViewport();

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

		bool CDisplay::Update(engine::time::CTimer* pTimer)
		{
			TRACE(TRACE_ENABLE);

			if (m_active == true)
			{
				// Make this display the current OpenGL context
				glfwMakeContextCurrent(m_window);

				// Clear back buffer
				glClear(GL_COLOR_BUFFER_BIT);

				glMatrixMode(GL_MODELVIEW);
				glLoadIdentity();
				glRotatef((float)pTimer->GetElapsedTime().GetSeconds() * 50.0f, 0.0f, 0.0f, 1.0f);

				glBegin(GL_TRIANGLES);
				glColor3f(1.0f, 0.0f, 0.0f);
				glVertex3f(-0.6f, -0.4f, 0.0f);
				glColor3f(0.0f, 1.0f, 0.0f);
				glVertex3f(0.6f, -0.4f, 0.0f);
				glColor3f(0.0f, 0.0f, 1.0f);
				glVertex3f(0.0f, 0.6f, 0.0f);
				glEnd();

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

			// Update view
			SetViewport();
		}

		//==========================================================================

		void CDisplay::SetViewport(void)
		{
			glViewport(0, 0, m_width, m_height);
			glMatrixMode(GL_PROJECTION);
			glLoadIdentity();
			float ratio = m_width / (float)m_height;
			glOrtho(-ratio, ratio, -1.0f, 1.0f, 1.0f, -1.0f);
		}

		//==========================================================================
	} // End [namespace glfw]

	//============================================================================
} // End [namespace engine]

//==============================================================================
// EOF

