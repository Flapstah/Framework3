#include "common/stdafx.h" // log.h included here

#include "base/engine.h"
#include "system/console.h"

//==============================================================================

#if defined(TRACE_ENABLE)
#undef TRACE_ENABLE
#endif // defined(TRACE_ENABLE)
#define TRACE_ENABLE false

//==============================================================================

namespace engine
{
	//============================================================================

	namespace base
	{
		//==========================================================================

		CEngine::CEngine(void)
			: m_flags(0)
		{
			TRACE(TRACE_ENABLE);
		}

		//==========================================================================

		CEngine::~CEngine(void)
		{
			TRACE(TRACE_ENABLE);

			Terminate();
		}

		//==========================================================================

		bool CEngine::Initialise(engine::system::CConfiguration& config)
		{
			TRACE(TRACE_ENABLE);

			bool ok = true;

			//------------------------------------------------------------------------
			// The passed arguments are scanned for '-root' and '-log' as these must
			// be set very early (preferably before any systems other than filesystem
			// are initialised)
			//------------------------------------------------------------------------
			const engine::system::CConfiguration::COption* pOption = config.GetOption(engine::system::CConfiguration::eSID_ROOT);
			if (pOption != NULL)
			{
				CFileSystem::Get().SetRootPath(pOption->GetArg(0));
			}
			pOption = config.GetOption(engine::system::CConfiguration::eSID_LOG);
			if (pOption != NULL)
			{
				CFileSystem::Get().SetLogFile(pOption->GetArg(0));
			}

			//------------------------------------------------------------------------
			// Initialise the main engine singletons by intanciating them
			//------------------------------------------------------------------------
			CFileSystem::Get(); // in case -root/-log weren't specified (above)
			time::CTime::Get();
			system::CConsole::Get();

			TODO("Read config here and add contents to CConsole::SetInitialValue()")

			if (ok)
			{
				//----------------------------------------------------------------------
				// Register cvars
				//----------------------------------------------------------------------
#if defined(DEBUG)
				// Can't use REGISTER_DEBUG_NAMED_VARIABLE as that tries to set the
				// initial value of the variable, and s_logLevel *must* be const in
				// release builds for the LOG_xxx macros to be elided successfully.
				REGISTER_NAMED_VARIABLE("log_level", engine::system::CLog::s_logLevel, static_cast<int64>(LOG_DEFAULT_DEBUG_LOG_LEVEL), 0, NULL, "Set the debug logging level (0=NONE, 1=ALWAYS, 2=FATAL, 3=ERROR, 4=WARNING, 5=INFO, 6=DEBUG)");
#endif // defined(DEBUG)

				m_flags |= eF_INITIALISED;
			}

			return ok;
		}

		//==========================================================================

		engine::time::CTimeValue CEngine::Update(void)	
		{
			TRACE(TRACE_ENABLE);

			engine::time::CTimeValue frameTime;

			if (m_flags & eF_INITIALISED)
			{
				frameTime = time::CTime::Get().Update();
				m_fps.Update(frameTime);
			}

			if (m_flags & eF_SIGNAL_TERMINATE)
			{
				LOG_INFO(ENGINE_LOGGER, "CEngine::Update(): SIGNAL_TERMINATE");
				frameTime = engine::time::INVALID_TIME;
			}

			return frameTime;
		}

		//==========================================================================

		bool CEngine::Uninitialise(void)
		{
			TRACE(TRACE_ENABLE);

			if (m_flags & eF_INITIALISED)
			{
				glfw::CGLFW::Get().Uninitialise();
#if defined(DEBUG)
				UNREGISTER_VARIABLE_BY_NAME("log_level");
#endif // defined(DEBUG)

				m_flags &= ~eF_INITIALISED;
			}

			return true;
		}

		//==========================================================================

		bool CEngine::Terminate(void)
		{
			TRACE(TRACE_ENABLE);

			Uninitialise();
			m_flags |= eF_SIGNAL_TERMINATE;

			return true;
		}

		//==========================================================================

		engine::base::CFileSystem* CEngine::GetFileSystem(void) const
		{
			TRACE(TRACE_ENABLE);

			return (m_flags & eF_INITIALISED) ? &base::CFileSystem::Get() : NULL;
		}

		//==========================================================================

		engine::glfw::CGLFW* CEngine::GetGLFW(void) const
		{
			TRACE(TRACE_ENABLE);

			return (m_flags & eF_INITIALISED) ? &glfw::CGLFW::Get() : NULL;
		}

		//==========================================================================

		engine::time::CTime* CEngine::GetTime(void) const
		{
			TRACE(TRACE_ENABLE);

			return (m_flags & eF_INITIALISED) ? &time::CTime::Get() : NULL;
		}

		//==========================================================================

		engine::system::CConsole* CEngine::GetConsole(void) const
		{
			TRACE(TRACE_ENABLE);

			return (m_flags & eF_INITIALISED) ? &system::CConsole::Get() : NULL;
		}

		//==========================================================================

		const engine::time::CFPSCalculator* CEngine::GetFPS(void) const
		{
			TRACE(TRACE_ENABLE);

			return (m_flags & eF_INITIALISED) ? &m_fps : NULL;
		}

		//==========================================================================
	} // End [namespace base]

	//============================================================================
} // End [namespace engine]

//==============================================================================
// EOF


