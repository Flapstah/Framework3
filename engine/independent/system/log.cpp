#include "common/stdafx.h" // log.h included here

#include <boost/filesystem.hpp>
#include <boost/thread/thread.hpp>

#include <time.h>
#include <fstream>

#include "base/engine.h"
#include "common/version.h"
#include "time/time.h"
#include "system/console.h"

//==============================================================================
// N.B. It's not advisable to use TRACE in CLog function, since potentially
// that would cause infinite recursion.  If you really must add them, you'll
// need to #define DEBUG_TRACE_USE_LOGGER (0) - see config.h
//==============================================================================
#if defined(TRACE_ENABLE)
#undef TRACE_ENABLE
#endif // defined(TRACE_ENABLE)
#define TRACE_ENABLE false

namespace engine
{
	//============================================================================

	namespace system
	{
		//==========================================================================

		std::ofstream g_logFile;

		//==========================================================================

#if defined(RELEASE)
		const CLog::eLogLevel CLog::s_logLevel = LOG_DEFAULT_RELEASE_LOG_LEVEL;
#else
		int64 CLog::s_logLevel = LOG_DEFAULT_DEBUG_LOG_LEVEL;
#endif // defined(RELEASE)
		bool CLog::s_crashOnFatalLog = true;
		uint32 CLog::s_defaultLogBehaviour = LOG_DEFAULT_BEHAVIOUR;

		//==========================================================================

		CLog::CLog(CLog& parent, const char* name)
			: m_pParent(&parent)
			, m_name(name)
			, m_flags(parent.m_flags)
		{
			TRACE(TRACE_ENABLE);
		}

		//==========================================================================

		CLog::CLog(CLog& parent, const char* name, uint32 flags)
			: m_pParent(&parent)
			, m_name(name)
			, m_flags(flags)
		{
			TRACE(TRACE_ENABLE);
		}

		//==========================================================================

		CLog::~CLog(void)
		{
			TRACE(TRACE_ENABLE);

			if (m_pParent == NULL)
			{
				// This is the master log destructor
				m_flags &= ~(eBAI_LOCATION | eBAI_THREADID);
				Log(NULL, 0, eLL_ALWAYS, "Log closed");
			}
		}

		//==========================================================================

		bool CLog::Log(const char* file, uint32 line, uint32 level, const char* format, ...)
		{
			TRACE(TRACE_ENABLE);

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
				if ((m_flags & eBT_FILE) && g_logFile.good())
				{
					g_logFile << buffer;

					if (m_flags & eB_AUTO_FLUSH)
					{
						g_logFile.flush();
					}
				}

				if (m_flags & eBT_CONSOLE)
				{
					TODO(console output here)
				}

				if (m_flags & eBT_STDOUT)
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

			if ((level == eLL_FATAL) && (s_crashOnFatalLog))
			{
				INTENTIONAL_CRASH;
			}

			return haveOutput;
		}

		//==========================================================================

		CLog::CLog(void)
			: m_pParent(NULL)
			, m_name(LOG_MASTER_NAME)
			, m_flags(s_defaultLogBehaviour)
		{
			TRACE(TRACE_ENABLE);

			time_t rawTime;
			struct tm* pTimeInfo;
			char buffer[80];
			char zone[32];
			memset(buffer, 0, sizeof(buffer));

			// N.B. The filesystem should normally be obtained through
			// CEngine::GetFileSystem(), as it will be NULL if the engine isn't
			// initialised, but the log system is created as part of the
			// initialisation process and therefore we wouldn't get access here.
			base::CFileSystem& fileSystem = base::CFileSystem::Get();

			::time(&rawTime);
			pTimeInfo = localtime(&rawTime);

			if (fileSystem.Backup(fileSystem.GetLogFilePath(), boost::filesystem::path("log_backup")))
			{
				g_logFile.open(fileSystem.GetLogFilePath().generic_string().c_str(), std::ios_base::out | std::ios_base::binary);

				strftime(buffer, sizeof(buffer), "%x %X", pTimeInfo);
				strftime(zone, sizeof(zone), " %Z", pTimeInfo);
				if (strlen(zone) > 1)
				{
					size_t bufferLen = strlen(buffer);
					size_t zoneLen = strlen(zone);
					size_t maxLen = sizeof(buffer)-bufferLen-1;
					memcpy(buffer+bufferLen, zone, (zoneLen > maxLen) ? maxLen : zoneLen);
				}
				Log(NULL, 0, eLL_ALWAYS, "Log created [%s]", buffer);
				Log(NULL, 0, eLL_ALWAYS, "%s, %s, %s", engine::common::GetVersionString(), engine::common::GetConfigurationString(), engine::common::GetBuildDateString());
			}
		}

		//==========================================================================

		CLog& GetMasterLog(void)
		{
			TRACE(TRACE_ENABLE);

			static CLog logMaster;
			return logMaster;
		}

		//==========================================================================

		CLog& GetEngineLog(void)
		{
			TRACE(TRACE_ENABLE);

			static CLog logEngine(GetMasterLog(), LOG_ENGINE_NAME);
			return logEngine;
		}

		//==========================================================================

		CLog& GetGameLog(void)
		{
			TRACE(TRACE_ENABLE);

			static CLog logGame(GetMasterLog(), LOG_GAME_NAME);
			return logGame;
		}

		//==========================================================================
	} // End [namespace system]

	//============================================================================
} // End [namespace engine]

//==============================================================================
// EOF


