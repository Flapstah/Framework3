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
			// The passed arguments are scanned for '-root' and '-log' as these must
			// be set very early (preferably before any systems other than filesystem
			// are initialised)
			//------------------------------------------------------------------------
			for (int32 i = 1; i < argc; ++i)
			{
				if ((strcmp("-root", argv[i]) == 0) && (i < argc-1))
				{
					CFileSystem::Get().SetRootPath(argv[++i]);
				}

				if ((strcmp("-log", argv[i]) == 0) && (i < argc-1))
				{
					CFileSystem::Get().SetLogFile(argv[++i]);
				}
			}

			//------------------------------------------------------------------------
			// Initialise the CTime singleton by accessing it (it will be instanced)
			//------------------------------------------------------------------------
			CFileSystem::Get(); // in case -root/-log weren't specified (above)
			time::CTime::Get();
			system::CConsole::Get();

			TODO(Read config here and add contents to CConsole::SetInitialValue())

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
			Uninitialise();

			return true;
		}

		//==========================================================================

		engine::base::CFileSystem* CEngine::GetFileSystem(void) const
		{
			return (m_flags & eF_INITIALISED) ? &base::CFileSystem::Get() : NULL;
		}

		//==========================================================================

		engine::time::CTime* CEngine::GetTime(void) const
		{
			return (m_flags & eF_INITIALISED) ? &time::CTime::Get() : NULL;
		}

		//==========================================================================

		engine::system::CConsole* CEngine::GetConsole(void) const
		{
			return (m_flags & eF_INITIALISED) ? &system::CConsole::Get() : NULL;
		}

		//==========================================================================
	} // End [namespace base]

	//============================================================================
} // End [namespace engine]

//==============================================================================
// EOF

