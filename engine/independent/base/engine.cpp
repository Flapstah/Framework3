#include "common/stdafx.h" // log.h included here

#include "base/engine.h"
#include "system/console.h"

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
		}

		//==========================================================================

		CEngine::~CEngine(void)
		{
			Terminate();
		}

		//==========================================================================

		bool CEngine::Initialise(int argc, char* argv[])
		{
			bool ok = true;

			//------------------------------------------------------------------------
			// Initialise the CTime singleton by accessing it (it will be instanced)
			//------------------------------------------------------------------------
			time::CTime::Get();
			system::CConsole::Get();

			// TODO: Read config here and add contents to CConsole::SetInitialValue()

			if (ok)
			{
				//----------------------------------------------------------------------
				// Register cvars
				//----------------------------------------------------------------------
				REGISTER_DEBUG_NAMED_VARIABLE("log_level", engine::system::CLog::s_logLevel, static_cast<int64>(LOG_DEFAULT_DEBUG_LOG_LEVEL), 0, NULL, "Set the debug logging level (0=NONE, 1=ALWAYS, 2=FATAL, 3=ERROR, 4=WARNING, 5=INFO, 6=DEBUG)");

				m_flags |= eF_INITIALISED;
			}

			return ok;
		}

		//==========================================================================

		engine::time::CTimeValue CEngine::Update(void)	
		{
			engine::time::CTimeValue tickTime;

			if (m_flags & eF_INITIALISED)
			{
				tickTime = time::CTime::Get().Update();
				m_fps.Update(tickTime);
			}

			return tickTime;
		}

		//==========================================================================

		bool CEngine::Uninitialise(void)
		{
			if (m_flags & eF_INITIALISED)
			{
				UNREGISTER_DEBUG_VARIABLE_BY_NAME("log_level");

				m_flags &= ~eF_INITIALISED;
			}

			return true;
		}

		//==========================================================================

		bool CEngine::Terminate(void)
		{
			Uninitialise();

			return true;
		}

		//==========================================================================

		engine::time::CTime* CEngine::GetTime(void)
		{
			return (m_flags & eF_INITIALISED) ? &time::CTime::Get() : NULL;
		}

		//==========================================================================
	} // End [namespace base]

	//============================================================================
} // End [namespace engine]

//==============================================================================
// EOF


