#include "common/stdafx.h"

#include <boost/thread/thread.hpp>
#include "common/itime.h"
#include "common/console.h"
#include "common/log.h"

//==============================================================================

namespace engine
{
	CLog CLog::s_logRoot;
	uint32 CLog::m_refActiveLogs = 0;

#if defined(RELEASE)
	const CLog::eLogLevel CLog::s_logLevel = LOG_DEFAULT_RELEASE_LOG_LEVEL;
#else
	int64 CLog::s_logLevel = LOG_DEFAULT_DEBUG_LOG_LEVEL;
#endif // defined(RELEASE)

	//==============================================================================

	CLog::CLog(CLog& parent, const char* name)
		: m_pParent(&parent)
			, m_name(name)
			 , m_flags(parent.m_flags)
			 , m_active(true)
	{
		++m_refActiveLogs;
	}

	//==============================================================================

	CLog::CLog(CLog& parent, const char* name, uint32 flags)
		: m_pParent(&parent)
			, m_name(name)
			 , m_flags(flags)
			 , m_active(true)
	{
		++m_refActiveLogs;
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
			engine::time::CTimeValue now = engine::time::GetITime()->GetCurrentTime();
			now.GetTime(days, hours, minutes, seconds);
			written = snprintf(buffer+position, LOG_BUFFER_SIZE-position-1, "[%02u:%02u:%02.3f]: ", hours, minutes, seconds);
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
			buffer[sizeof(buffer)-1] = 0;
			va_end(argList);
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
				fputs(buffer, ((s_logLevel == eLL_FATAL) || (s_logLevel == eLL_ERROR) || (s_logLevel == eLL_WARNING)) ? stderr : stdout);
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
			, m_name(LOG_ROOT_NAME)
			 , m_flags(eBAI_LOCATION | eBAI_NAME | eBAI_TIMESTAMP | eBAI_THREADID | eBT_FILE | eBT_CONSOLE | eBT_STANDARD | eBT_DEBUGGER)
			 , m_active(true)
	{
#if defined(DEBUG)
		if (m_refActiveLogs == 0)
		{
			REGISTER_NAMED_VARIABLE("log_level", CLog::s_logLevel, static_cast<int64>(LOG_DEFAULT_DEBUG_LOG_LEVEL), 0, NULL, "Set the debug logging level (0=NONE, 1=ALWAYS, 2=FATAL, 3=ERROR, 4=WARNING, 5=INFO, 6=DEBUG)");
		}
#endif // defined(DEBUG)
		++m_refActiveLogs;
	}

	CLog::~CLog(void)
	{
		if (--m_refActiveLogs == 0)
		{
#if defined(DEBUG)
			UNREGISTER_VARIABLE_BY_NAME("log_level");
#endif // defined(DEBUG)
		}
	}

	//============================================================================

} // End [namespace engine]

//==============================================================================
// EOF


