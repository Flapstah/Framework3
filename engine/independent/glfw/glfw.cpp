#include "common/stdafx.h" // log.h included here

#include "base/engine.h"
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

		void glfwKeyCallback(GLFWwindow* window, int key, int scancode, int action, int mods)
		{
			CGLFW::Get().glfwKeyCallback(window, key, scancode, action, mods);
		}

		//==========================================================================

		void glfwSetFramebufferSizeCallback(GLFWwindow* window, int width, int height)
		{
			CGLFW::Get().glfwFramebufferSizeCallback(window, width, height);
		}

		//==========================================================================
		// SConfiguration
		//==========================================================================

		SConfiguration::SConfiguration(void)
			: m_realtime(true)
			, m_desiredFrameRate(DEFAULT_FRAMERATE)
		{
			TRACE(TRACE_ENABLE);
		}

		//==========================================================================

		SConfiguration::~SConfiguration(void)
		{
			TRACE(TRACE_ENABLE);
		}

		//==========================================================================
		// CGLFW
		//==========================================================================

		CGLFW::CGLFW(void)
			: m_flags(CDisplay::eF_NONE)
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

			engine::time::CTime::Get().DestroyTimer(m_timer);
			Uninitialise();
		}

		//==========================================================================

		bool CGLFW::Initialise(engine::glfw::SConfiguration& configuration)
		{
			TRACE(TRACE_ENABLE);
			m_status = eS_RUNNING;
			m_flags = CDisplay::eF_NONE;

			if (configuration.m_realtime)
			{
				m_flags = static_cast<CDisplay::eFlags>(m_flags | CDisplay::eF_REALTIME);
			}

			if (configuration.m_vsync)
			{
				m_flags = static_cast<CDisplay::eFlags>(m_flags | CDisplay::eF_VSYNC);
			}

			if (glfwInit())
			{
				// Set timer callback
				m_callback = engine::utility::MakeUnaryCallback<CGLFW, engine::time::CTimer>(*this, &CGLFW::TimerCallback);
				m_timer = engine::time::CTime::Get().CreateTimer(engine::time::CTimeValue(0.1), 1.0f, engine::time::CTimeValue(1.0/DEFAULT_FRAMERATE), m_callback);

				SetDesiredFramerate(configuration.m_desiredFrameRate);
			}
			else
			{
				m_status = eS_INITFAIL;
			}

			return (m_status == eS_RUNNING);
		}

		//==========================================================================

		bool CGLFW::Update(engine::time::CTimer* pTimer)
		{
			TRACE(TRACE_ENABLE);

			TDisplayMap activeWindows;

			// Gather events
			if (m_flags & CDisplay::eF_REALTIME)
			{
				glfwPollEvents();
			}
			else
			{
				glfwWaitEvents();
			}

			// Update display(s)
			for (TDisplayMap::iterator it = m_display.begin(), end = m_display.end(); it != end; ++it)
			{
				if (it->second.get()->Update(pTimer) == true)
				{
					activeWindows[it->first] = it->second;
				}
			}

			// Clean up inactive displays
			m_display.swap(activeWindows);

			return (m_display.size() > 0);
		}

		//==========================================================================

		void CGLFW::Uninitialise(void)
		{
			TRACE(TRACE_ENABLE);

			if (m_status == eS_RUNNING)
			{
				CloseAllDisplays();
				glfwTerminate();
			}

			m_status = eS_UNINITIALISED;
		}

		//==========================================================================

		engine::glfw::CDisplay::TDisplayID CGLFW::OpenDisplay(uint32 width, uint32 height, const char* name, bool fullScreen)
		{
			TRACE(TRACE_ENABLE);

			m_flags = static_cast<CDisplay::eFlags>((m_flags & ~CDisplay::eF_FULLSCREEN) | (-fullScreen & CDisplay::eF_FULLSCREEN));

			TCDisplayPtr pDisplay = boost::make_shared<CDisplay>();

			engine::glfw::CDisplay::TDisplayID id = pDisplay->Open(width, height, name, m_flags);
			if (id != INVALID_DISPLAY_ID)
			{
				GLFWwindow* pWindow = pDisplay->GetGLFWwindow();
				m_display[pWindow] = pDisplay;
				SetDisplayCallbacks(pWindow, true);
			}

			return id;
		}

		//==========================================================================

		void CGLFW::GetDisplayInfo(engine::glfw::CDisplay::TDisplayID id, CDisplay::eDisplayInfoFlags flags /* = CDisplay::eDIF_DISPLAY*/) const
		{
			TRACE(TRACE_ENABLE);

			for (TDisplayMap::const_iterator it = m_display.begin(), end = m_display.end(); it != end; ++it)
			{
				if (it->second.get()->GetID() == id)
				{
					it->second.get()->GetInfo(flags);
					break;
				}
			}
		}

		//==========================================================================

		void CGLFW::CloseDisplay(engine::glfw::CDisplay::TDisplayID id)
		{
			TRACE(TRACE_ENABLE);

			for (TDisplayMap::iterator it = m_display.begin(), end = m_display.end(); it != end; ++it)
			{
				if (it->second.get()->GetID() == id)
				{
					SetDisplayCallbacks(it->first, false);
					// N.B. since the display map contains smart pointers, the CDisplay
					// destructors will be called by this
					m_display.erase(it);
					break;
				}
			}
		}

		//==========================================================================

		const engine::time::CFPSCalculator* CGLFW::GetFPS(void) const
		{
			TRACE(TRACE_ENABLE);

			return (m_status == eS_RUNNING) ? &m_fps : NULL;
		}

		//==========================================================================

		void CGLFW::SetDesiredFramerate(uint32 framerate)
		{
			TRACE(TRACE_ENABLE);

			m_timer->SetCallbackInterval(engine::time::CTimeValue(1.0/framerate));
		}

		//==========================================================================

		void CGLFW::glfwKeyCallback(GLFWwindow* window, int key, int scancode, int action, int mods)
		{
			TDisplayMap::iterator it = m_display.find(window);
			bool consumed = false;

			if (it != m_display.end())
			{
				consumed = it->second.get()->glfwKeyCallback(key, scancode, action, mods);
			}

			if (!consumed)
			{
				// Global key handling
				if ((key == GLFW_KEY_ESCAPE) && (action == GLFW_PRESS))
				{
					CloseAllDisplays();
				}
			}
		}

		//==========================================================================

		void CGLFW::glfwFramebufferSizeCallback(GLFWwindow* window, int width, int height)
		{
			TDisplayMap::iterator it = m_display.find(window);

			if (it != m_display.end())
			{
				it->second.get()->glfwFramebufferSizeCallback(width, height);
			}
		}

		//==========================================================================

		void CGLFW::CloseAllDisplays(void)
		{
			TRACE(TRACE_ENABLE);

			for (TDisplayMap::iterator it = m_display.begin(), end = m_display.end(); it != end; ++it)
			{
				SetDisplayCallbacks(it->first, false);
			}

			// N.B. since the display map contains smart pointers, the CDisplay
			// destructors will be called by this
			m_display.clear();
		}

		//==========================================================================

		void CGLFW::SetDisplayCallbacks(GLFWwindow* window, bool set)
		{
			// Set/clear GLFW callbacks for the given display
			glfwSetKeyCallback(window, (set) ? engine::glfw::glfwKeyCallback : NULL);
			glfwSetFramebufferSizeCallback(window, (set) ? engine::glfw::glfwSetFramebufferSizeCallback : NULL);
		}

		//==========================================================================

		void CGLFW::TimerCallback(engine::time::CTimer* pTimer)
		{
			TRACE(TRACE_ENABLE);

			m_fps.Update(pTimer->GetFrameTime());

			if (Update(pTimer) == false)
			{
				engine::base::CEngine::Get().Terminate();
			}
		}

		//==========================================================================
	} // End [namespace base]

	//============================================================================
} // End [namespace engine]

//==============================================================================
// EOF


