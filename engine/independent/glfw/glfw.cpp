#include "common/stdafx.h" // log.h included here

#include "glfw/glfw.h"

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
		// glfw callbacks
		//==========================================================================

		void glfwErrorCallback(int error, const char* description)
		{
			TRACE(TRACE_ENABLE);

			LOG_ERROR(ENGINE_LOGGER, "[GLFW] [%d] [%s]", error, description);
		}
		
		//==========================================================================

		SConfiguration::SConfiguration(void)
			: m_continuousUpdate(true)
		{
			TRACE(TRACE_ENABLE);
		}

		//==========================================================================

		SConfiguration::~SConfiguration(void)
		{
			TRACE(TRACE_ENABLE);
		}

		//==========================================================================

		CGLFW::CGLFW(void)
			: m_flags(eF_NONE)
			, m_status(eS_UNINITIALISED)
		{
			TRACE(TRACE_ENABLE);

			// Set glfw callbacks
			glfwSetErrorCallback(glfwErrorCallback);
		}

		//==========================================================================

		CGLFW::~CGLFW(void)
		{
			TRACE(TRACE_ENABLE);

			Uninitialise();
		}

		//==========================================================================

		bool CGLFW::Initialise(engine::glfw::SConfiguration& configuration)
		{
			TRACE(TRACE_ENABLE);

			if (glfwInit())
			{
				m_status = eS_RUNNING;

				if (configuration.m_continuousUpdate)
				{
					m_flags = eF_CONTINOUS_UPDATE;
				}
			}

			return (m_status == eS_RUNNING);
		}

		//==========================================================================

		bool CGLFW::Update(void)
		{
			TRACE(TRACE_ENABLE);

			TDisplayVec activeWindows;
			activeWindows.reserve(m_display.size());

			for (TDisplayVec::iterator it = m_display.begin(), end = m_display.end(); it != end; ++it)
			{
				if (it->get()->Update() == true)
				{
					activeWindows.push_back(*it);
				}
			}

			m_display.swap(activeWindows);
			glfwPollEvents();

			return (m_display.size() > 0);
		}

		//==========================================================================

		void CGLFW::Uninitialise(void)
		{
			TRACE(TRACE_ENABLE);

			if (m_status == eS_RUNNING)
			{
				glfwTerminate();
			}

			m_status = eS_UNINITIALISED;
		}

		//==========================================================================

		engine::glfw::CDisplay::TDisplayID CGLFW::OpenDisplay(uint32 width, uint32 height, const char* name, bool fullScreen)
		{
			TRACE(TRACE_ENABLE);

			TCDisplayPtr pDisplay = boost::make_shared<CDisplay>();

			engine::glfw::CDisplay::TDisplayID id = pDisplay->Open(width, height, name, fullScreen);
			if (id != INVALID_DISPLAY_ID)
			{
				m_display.push_back(pDisplay);
			}

			return id;
		}

		//==========================================================================

		void CGLFW::CloseDisplay(engine::glfw::CDisplay::TDisplayID id)
		{
			TRACE(TRACE_ENABLE);

			for (TDisplayVec::iterator it = m_display.begin(), end = m_display.end(); it != end; ++it)
			{
				if (it->get()->GetID() == id)
				{
					it->get()->Close();
					break;
				}
			}
		}

		//==========================================================================
	} // End [namespace base]

	//============================================================================
} // End [namespace engine]

//==============================================================================
// EOF


