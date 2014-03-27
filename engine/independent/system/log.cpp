#include "common/stdafx.h" // log.h included here

#include <boost/thread/thread.hpp>
#include "time/time.h"
#include "system/console.h"

//==============================================================================
// N.B. It's not advisable to use TRACE in CLog function, since potentially
// that would cause infinite recursion.  If you really must add them, you'll
// need to #define DEBUG_TRACE_USE_LOGGER (0) - see config.h
//==============================================================================

namespace engine
{
	//============================================================================

	namespace system
	{
		//==========================================================================
#if defined(RELEASE)
		const CLog::eLogLevel CLog::s_logLevel = LOG_DEFAULT_RELEASE_LOG_LEVEL;
#else
		int64 CLog::s_logLevel = LOG_DEFAULT_DEBUG_LOG_LEVEL;
#endif // defined(RELEASE)

		//==========================================================================

		CLog::CLog(CLog& parent, const char* name)
			: m_pParent(&parent)
			, m_name(name)
			, m_flags(parent.m_flags)
		{
			if (m_pParent->m_name == NULL)
			{
				printf("FUCK\n");
			}
		}

		//==========================================================================

		CLog::CLog(CLog& parent, const char* name, uint32 flags)
			: m_pParent(&parent)
			, m_name(name)
			, m_flags(flags)
		{
		}

		//==========================================================================

		CLog::~CLog(void)
		{
		}

		//==========================================================================

		bool CLog::Log(const char* file, uint32 line, uint32 level, const char* format, ...)
		{
			va_list argList;
			char buffer[LOG_BUFFER_SIZE];
			int32 position = 0;
			int32 written = 0;

			//------------------------------------------------------------------------
			// File/line location
			//------------------------------------------------------------------------
			if ((m_flags & eBAI_LOCATION) && (written >= 0))
			{
				written = snprintf(buffer+position, LOG_BUFFER_SIZE-position-1, "%s(%u): ", file, line);
				position += (written >= 0) ? written : 0;
			}

			//------------------------------------------------------------------------
			// Timestamp
			//------------------------------------------------------------------------
			if ((m_flags & eBAI_TIMESTAMP) && (written >= 0))
			{
				int32 days, hours, minutes;
				float seconds;
				engine::time::CTimeValue now = engine::time::CTime::Get().GetCurrentTime();
				now.GetTime(days, hours, minutes, seconds);
				written = snprintf(buffer+position, LOG_BUFFER_SIZE-position-1, "[%02u:%02u:%06.3f]: ", hours, minutes, seconds);
				position += (written >= 0) ? written : 0;
			}

			//------------------------------------------------------------------------
			// Log name
			//------------------------------------------------------------------------
			if ((m_flags & eBAI_NAME) && (written >= 0))
			{
				written = snprintf(buffer+position, LOG_BUFFER_SIZE-position-1, "[%s]: ", m_name);
				position += (written >= 0) ? written : 0;
			}

			//------------------------------------------------------------------------
			// Log level
			//------------------------------------------------------------------------
			if ((m_flags & eBAI_LOG_LEVEL) && (written >= 0))
			{
				written = 0;

				switch (level)
				{
				case eLL_FATAL:
					written = snprintf(buffer+position, LOG_BUFFER_SIZE-position-1, "[FATAL]: ");
					break;
				case eLL_ERROR:
					written = snprintf(buffer+position, LOG_BUFFER_SIZE-position-1, "[ERROR]: ");
					break;
				case eLL_WARNING:
					written = snprintf(buffer+position, LOG_BUFFER_SIZE-position-1, "[WARNING]: ");
					break;
				case eLL_DEBUG:
					written = snprintf(buffer+position, LOG_BUFFER_SIZE-position-1, "[DEBUG]: ");
					break;
				}

				position += (written >= 0) ? written : 0;
			}

			//------------------------------------------------------------------------
			// Thread ID
			//------------------------------------------------------------------------
			if ((m_flags & eBAI_THREADID) && (written >= 0))
			{
				uint64 threadID = boost::hash<boost::thread::id>()(boost::this_thread::get_id());
				written = snprintf(buffer+position, LOG_BUFFER_SIZE-position-1, "[%" PRIx64 "]: ", threadID);
				position += (written >= 0) ? written : 0;
			}

			//------------------------------------------------------------------------
			// Message body
			//------------------------------------------------------------------------
			if (written >= 0)
			{
				va_start(argList, format);
				written = vsnprintf(buffer+position, LOG_BUFFER_SIZE-position-1, format, argList);
				position += (written >= 0) ? written : 0;
				va_end(argList);
			}

			//------------------------------------------------------------------------
			// Forced newline
			//------------------------------------------------------------------------
			if ((m_flags & eBAI_NEWLINE) && (written >= 0))
			{
				// Force a newline and null termination of the buffer
				if (position >= LOG_BUFFER_SIZE-2)
				{
					position = LOG_BUFFER_SIZE-2;
				}
				buffer[position++] = '\n';
				buffer[position++] = 0;
			}

			//------------------------------------------------------------------------
			// Output to targets
			//------------------------------------------------------------------------
			bool haveOutput = (written >= 0) && (written < LOG_BUFFER_SIZE);
			if (haveOutput)
			{
				if (m_flags & eBT_FILE)
				{
					// TODO: file output here
				}

				if (m_flags & eBT_CONSOLE)
				{
					// TODO: console output here
				}

				if (m_flags & eBT_STANDARD)
				{
					FILE* pDestination = stdout;
					if (!(m_flags & eB_NO_STDERR) && ((s_logLevel == eLL_FATAL) || (s_logLevel == eLL_ERROR) || (s_logLevel == eLL_WARNING)))
					{
						pDestination = stderr;
					}
					fputs(buffer, pDestination);
				}

#if defined(WIN32)
				if (m_flags & eBT_DEBUGGER)
				{
					OutputDebugString(buffer);
				}
#endif // defined(WIN32)
			}

			return haveOutput;
		}

		//==========================================================================

		CLog::CLog(void)
			: m_pParent(NULL)
			, m_name(LOG_MASTER_NAME)
			, m_flags(eB_ACTIVE | eBAI_ALL | eBT_ALL)
		{
		}

		//==========================================================================

		CLog& GetMasterLog(void)
		{
			static CLog logMaster;
			return logMaster;
		}

		//==========================================================================

		CLog& GetEngineLog(void)
		{
			static CLog logEngine(GetMasterLog(), LOG_ENGINE_NAME);
			return logEngine;
		}

		//==========================================================================

		CLog& GetGameLog(void)
		{
			static CLog logGame(GetMasterLog(), LOG_GAME_NAME);
			return logGame;
		}

		//==========================================================================
	} // End [namespace system]

	//============================================================================
} // End [namespace engine]

//==============================================================================
// EOF


