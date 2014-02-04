#include "common/stdafx.h"

#if !USE_OPENGL_SUPERBIBLE

#include "common/itime.h"
#include "common/commandline.h"
#include "unit_tests/cvartest.h"
#include "unit_tests/typetest.h"
#include "unit_tests/timetest.h"
#include "common/console.h"
#include "common/version.h"

#include <cmath>


#include <boost/thread/thread.hpp>

class CLog
{
	public:
		enum eLogLevel
		{
			eLL_ALWAYS = 1,
			eLL_FATAL,
			eLL_ERROR,
			eLL_WARNING,
			eLL_INFO,
			eLL_DEBUG
		};

		enum eBehaviour
		{
			// Additional info
			eBAI_LOCATION = 1 << 0,
			eBAI_NAME = 1 << 1,
			eBAI_TIMESTAMP = 1 << 2,
			eBAI_THREADID = 1 << 3,

			// Targets
			eBT_FILE = 1 << 4,
			eBT_CONSOLE = 1 << 5,
			eBT_STANDARD = 1 << 6,
		};

	public:
		CLog(CLog& parent, const char* name)
			: m_pParent(&parent)
			, m_name(name)
			, m_flags(parent.m_flags)
			, m_active(true)
		{
		}

		CLog(CLog& parent, const char* name, uint32 flags)
			: m_pParent(&parent)
			, m_name(name)
			, m_flags(flags)
			, m_active(true)
		{
		}

		inline bool IsActive(void) const
		{
			return (m_active && ((m_pParent != NULL) ? m_pParent->IsActive() : m_active));
		}

		inline bool SetActive(bool set)
		{
			bool old = m_active;
			m_active = set;
			return old;
		}

		inline uint32 GetFlags(void) const
		{
			return m_flags;
		}

		inline uint32 SetFlags(uint32 flags)
		{
			uint32 old = m_flags;
			m_flags = flags;
			return old;
		}

#define LOG_BUFFER_SIZE (1024)
		bool Log(const char* file, uint32 line, const char* format, ...)
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

	private:

#define LOG_ROOT_NAME "Main"

	CLog(void)
		: m_pParent(NULL)
		, m_name(LOG_ROOT_NAME)
		, m_flags(eBAI_LOCATION | eBAI_NAME | eBAI_TIMESTAMP | eBAI_THREADID | eBT_FILE | eBT_CONSOLE | eBT_STANDARD)
		, m_active(true)
	{
	}

	private:
	CLog* m_pParent;
	const char* m_name;
	uint32 m_flags;
	bool m_active;

	public:
	static CLog s_logRoot;
#if defined(_DEBUG)
	static eLogLevel s_logLevel;
#else
	static const eLogLevel s_logLevel;
#endif // defined(_DEBUG)
};

CLog CLog::s_logRoot;
#if defined(_DEBUG)
CLog::eLogLevel CLog::s_logLevel = CLog::eLL_FATAL;
#else
const CLog::eLogLevel CLog::s_logLevel = CLog::eLL_DEBUG;
#endif // defined(_DEBUG)

#define LOG(_log_, _level_, _format_, ...) if ((CLog::s_logLevel >= _level_) && (_log_.IsActive())) { _log_.Log(__FILE__, __LINE__, _format_, ## __VA_ARGS__); }

#define LOG_DEBUG(_log_, _format_, ...) LOG(_log_, CLog::eLL_DEBUG, _format_, ## __VA_ARGS__)
#define LOG_INFO(_log_, _format_, ...) LOG(_log_, CLog::eLL_INFO, _format_, ## __VA_ARGS__)
#define LOG_WARNING(_log_, _format_, ...) LOG(_log_, CLog::eLL_WARNING, _format_, ## __VA_ARGS__)
#define LOG_ERROR(_log_, _format_, ...) LOG(_log_, CLog::eLL_ERROR, _format_, ## __VA_ARGS__)
#define LOG_FATAL(_log_, _format_, ...) LOG(_log_, CLog::eLL_FATAL, _format_, ## __VA_ARGS__)
#define LOG_ALWAYS(_log_, _format_, ...) LOG(_log_, CLog::eLL_ALWAYS, _format_, ## __VA_ARGS__)

//==============================================================================

int main(int argc, char* argv[])
{
	//	IGNORE_PARAMETER(argc);
	//	IGNORE_PARAMETER(argv);

	CLog test(CLog::s_logRoot, "test");

	printf("log level = %d\n", CLog::s_logLevel);
	printf("log level eLL_DEBUG %s\n", (CLog::s_logLevel >= CLog::eLL_DEBUG) ? "PRINTED" : "NOT PRINTED");
	printf("log level eLL_INFO %s\n", (CLog::s_logLevel >= CLog::eLL_INFO) ? "PRINTED" : "NOT PRINTED");
	printf("log level eLL_WARNING %s\n", (CLog::s_logLevel >= CLog::eLL_WARNING) ? "PRINTED" : "NOT PRINTED");
	printf("log level eLL_ERROR %s\n", (CLog::s_logLevel >= CLog::eLL_ERROR) ? "PRINTED" : "NOT PRINTED");
	printf("log level eLL_FATAL %s\n", (CLog::s_logLevel >= CLog::eLL_FATAL) ? "PRINTED" : "NOT PRINTED");
	printf("log level eLL_ALWAYS %s\n", (CLog::s_logLevel >= CLog::eLL_ALWAYS) ? "PRINTED" : "NOT PRINTED");

//	LOG(test, CLog::eLL_DEBUG, "Test with a number: %d", 3);
	LOG_DEBUG(test, "Debug log test\n");
	LOG_WARNING(test, "Info log test\n");
	LOG_WARNING(test, "Warning log test\n");
	LOG_ERROR(test, "Error log test\n");
	LOG_FATAL(test, "Fatal log test\n");
	LOG_ALWAYS(test, "Always log test\n");

	/*
		{
			test::CTypeTest test;
			test.Start();
			while (test.Update() == test::CUnitTest::eTS_RUNNING);
			test.End();
		}

		{
			test::CTimeTest test;
			test.Start();
			while (test.Update() == test::CUnitTest::eTS_RUNNING);
			test.End();
		}

		{
			test::CCVarTest test;
			test.Start();
			while (test.Update() == test::CUnitTest::eTS_RUNNING);
			test.End();
		}
		*/

		/*
			 uint32 x = engine::CompileTimeStringHash("a nice long string to hash");
			 printf("x %08x\n", x);
			 uint32 y = engine::CRunTimeStringHash::Calculate("a nice long string to hash");
			 printf("y %08x\n", y);
			 */

	printf("All done.\n");

	return 0;
}

//==============================================================================

#endif // !USE_OPENGL_SUPERBIBLE

// [EOF]
