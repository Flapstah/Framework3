#include "common/stdafx.h"

#include <boost/thread/thread.hpp>
#include "common/itime.h"
#include "common/console.h"
#include "common/log.h"

//==============================================================================

namespace engine
{

	CLog CLog::s_logRoot;

#if defined(NDEBUG)
	const CLog::eLogLevel CLog::s_logLevel = CLog::eLL_ERROR;
#else
	int64 CLog::s_logLevel = CLog::eLL_INFO;
#endif // defined(NDEBUG)

	//==============================================================================

	CLog::CLog(CLog& parent, const char* name)
		: m_pParent(&parent)
			, m_name(name)
			 , m_flags(parent.m_flags)
			 , m_active(true)
	{
#if !defined(NDEBUG)
		REGISTER_NAMED_VARIABLE("log_level", CLog::s_logLevel, static_cast<int64>(CLog::eLL_INFO), 0, NULL, "Set the debug logging level (0=NONE, 1=ALWAYS, 2=FATAL, 3=ERROR, 4=WARNING, 5=INFO, 6=DEBUG)");
#endif // !defined(NDEBUG)
	}

	//==============================================================================

	CLog::CLog(CLog& parent, const char* name, uint32 flags)
		: m_pParent(&parent)
			, m_name(name)
			 , m_flags(flags)
			 , m_active(true)
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

		bool done = (written >= 0) && (written < LOG_BUFFER_SIZE);
		printf(buffer);
		return done;
	}

	//==============================================================================

	CLog::CLog(void)
		: m_pParent(NULL)
			, m_name(LOG_ROOT_NAME)
			 , m_flags(eBAI_LOCATION | eBAI_NAME | eBAI_TIMESTAMP | eBAI_THREADID | eBT_FILE | eBT_CONSOLE | eBT_STANDARD)
			 , m_active(true)
	{
	}

	//============================================================================

} // End [namespace engine]

//==============================================================================
// EOF


