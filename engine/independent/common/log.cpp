#include "common/stdafx.h" // log.h included here

#include <boost/thread/thread.hpp>
#include "common/itime.h"
#include "common/console.h"

//==============================================================================
// N.B. It's not advisable to use TRACE in CLog function, since potentially
// that would cause infinite recursion.  If you really must add them, you'll
// need to #define DEBUG_TRACE_USE_LOGGER (0) - see config.h
//==============================================================================

namespace engine
{
#if defined(DEBUG)
	int64 g_logLevel = LOG_DEFAULT_DEBUG_LOG_LEVEL;
#endif // defined(DEBUG)

	//==============================================================================

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

	//==============================================================================

	CLog::CLog(CLog& parent, const char* name, uint32 flags)
		: m_pParent(&parent)
		, m_name(name)
		, m_flags(flags)
	{
	}

	//==============================================================================

	CLog::~CLog(void)
	{
	}

	//==============================================================================

	bool CLog::Log(const char* file, uint32 line, const char* format, ...)
	{
		va_list argList;
		char buffer[LOG_BUFFER_SIZE];
		int32 position = 0;
		int32 written = 0;

		if ((m_flags & eBAI_LOCATION) && (written >= 0))
		{
			written = snprintf(buffer+position, LOG_BUFFER_SIZE-position-1, "%s(%u): ", file, line);
			position += (written >= 0) ? written : 0;
		}

		if ((m_flags & eBAI_TIMESTAMP) && (written >= 0))
		{
			int32 days, hours, minutes;
			float seconds;
			time::CTimeValue now = time::GetITime()->GetCurrentTime();
			now.GetTime(days, hours, minutes, seconds);
			written = snprintf(buffer+position, LOG_BUFFER_SIZE-position-1, "[%02u:%02u:%06.3f]: ", hours, minutes, seconds);
			position += (written >= 0) ? written : 0;
		}

		if ((m_flags & eBAI_NAME) && (written >= 0))
		{
			written = snprintf(buffer+position, LOG_BUFFER_SIZE-position-1, "[%s]: ", m_name);
			position += (written >= 0) ? written : 0;
		}

		if ((m_flags & eBAI_THREADID) && (written >= 0))
		{
			uint64 threadID = boost::hash<boost::thread::id>()(boost::this_thread::get_id());
			written = snprintf(buffer+position, LOG_BUFFER_SIZE-position-1, "[%" PRIx64 "]: ", threadID);
			position += (written >= 0) ? written : 0;
		}

		if (written >= 0)
		{
			va_start(argList, format);
			written = vsnprintf(buffer+position, LOG_BUFFER_SIZE-position-1, format, argList);
			position += (written >= 0) ? written : 0;
			va_end(argList);
		}

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
				fputs(buffer, ((g_logLevel == eLL_FATAL) || (g_logLevel == eLL_ERROR) || (g_logLevel == eLL_WARNING)) ? stderr : stdout);
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

	//==============================================================================

	CLog::CLog(void)
		: m_pParent(NULL)
		, m_name(LOG_MASTER_NAME)
		, m_flags(eB_ACTIVE | eBAI_NEWLINE | eBAI_LOCATION | eBAI_NAME | eBAI_TIMESTAMP | eBAI_THREADID | eBT_FILE | eBT_CONSOLE | eBT_STANDARD | eBT_DEBUGGER)
	{
	}

	//============================================================================

	CLog& CLog::GetMasterLog(void)
	{
		static CLog logMaster;
		return logMaster;
	}

	//============================================================================

	CLog& CLog::GetEngineLog(void)
	{
		static CLog logEngine(GetMasterLog(), LOG_ENGINE_NAME);
		return logEngine;
	}

	//============================================================================

	CLog& CLog::GetGameLog(void)
	{
		static CLog logGame(GetMasterLog(), LOG_GAME_NAME);
		return logGame;
	}

	//============================================================================
} // End [namespace engine]

//==============================================================================
// EOF


