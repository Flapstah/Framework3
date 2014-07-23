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

		CGLFW::CGLFW(void)
			: m_flags(eF_NONE)
			, m_status(eS_UNINITIALISED)
		{
			TRACE(TRACE_ENABLE);

			// Set glfw callbacks
			glfwSetErrorCallback(glfwErrorCallback);

			// Set timer callback
			m_callback = engine::utility::MakeUnaryCallback<CGLFW, engine::time::CTimer>(*this, &CGLFW::TimerCallback);
			m_timer = engine::time::CTime::Get().CreateTimer(engine::time::CTimeValue(0.1), 1.0f, engine::time::CTimeValue(1.0/DEFAULT_FRAMERATE), m_callback);
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

			if (glfwInit())
			{
				m_status = eS_RUNNING;

				if (configuration.m_realtime)
				{
					m_flags = eF_REALTIME;
				}

				SetDesiredFramerate(configuration.m_desiredFrameRate);
			}

			return (m_status == eS_RUNNING);
		}

		//==========================================================================

		bool CGLFW::Update(void)
		{
			TRACE(TRACE_ENABLE);

			TDisplayMap activeWindows;

			for (TDisplayMap::iterator it = m_display.begin(), end = m_display.end(); it != end; ++it)
			{
				if (it->second.get()->Update() == true)
				{
					activeWindows[it->first] = it->second;
				}
			}

			m_display.swap(activeWindows);
			if (m_flags & eF_REALTIME)
			{
				glfwPollEvents();
			}
			else
			{
				glfwWaitEvents();
			}

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

			TCDisplayPtr pDisplay = boost::make_shared<CDisplay>();

			engine::glfw::CDisplay::TDisplayID id = pDisplay->Open(width, height, name, fullScreen);
			if (id != INVALID_DISPLAY_ID)
			{
				m_display[pDisplay->GetGLFWwindow()] = pDisplay;
			}

			return id;
		}

		//==========================================================================

		void CGLFW::CloseDisplay(engine::glfw::CDisplay::TDisplayID id)
		{
			TRACE(TRACE_ENABLE);

			for (TDisplayMap::iterator it = m_display.begin(), end = m_display.end(); it != end; ++it)
			{
				if (it->second.get()->GetID() == id)
				{
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

		void CGLFW::CloseAllDisplays(void)
		{
			TRACE(TRACE_ENABLE);

			// N.B. since the display map contains smart pointers, the CDisplay
			// destructors will be called by this
			m_display.clear();
		}

		//==========================================================================

		void CGLFW::TimerCallback(engine::time::CTimer* pTimer)
		{
			TRACE(TRACE_ENABLE);

			bool running = Update();
			m_fps.Update(pTimer->GetFrameTime());

			if (running == false)
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


