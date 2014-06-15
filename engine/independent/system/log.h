#if !defined(__LOG_H__)
#define __LOG_H__

//==============================================================================

namespace engine
{
	//============================================================================

	namespace system
	{
		//==========================================================================
		// CLog
		//==========================================================================
		class CLog
		{
			//------------------------------------------------------------------------

			friend CLog& GetMasterLog(void);
			friend CLog& GetEngineLog(void);
			friend CLog& GetGameLog(void);
			
		public:
			enum eLogLevel
			{
				eLL_ALWAYS,
				eLL_FATAL,
				eLL_ERROR,
				eLL_WARNING,
				eLL_TERSE,
				eLL_INFO,
				eLL_VERBOSE,
				eLL_DEBUG
			}; // End [enum eLogLevel]

			//------------------------------------------------------------------------

			enum eBehaviour
			{
				eB_ACTIVE				= 1 << 0,		// Log is active and will produce output
				eB_NO_STDERR		= 1 << 1,		// Log will NOT use stderr (eBT_STDOUT
																		// target will normally output to stderr for
																		// eLL_FATAL, eLL_ERROR and eLL_WARNING log
																		// levels, with everything else going to
																		// stdout.  Setting this flag will force
																		// *all* output through stdout.)
				eB_AUTO_FLUSH		= 1 << 2,		// Automatically flush every call to Log()
																		// if eBT_FILE target (see below)

				eB_COMMON				= (eB_ACTIVE | eB_AUTO_FLUSH),

				// Additional info
				eBAI_LOCATION		= 1 << 3,		// adds the log location [__FILE__(__LINE__)]
				eBAI_LOG_LEVEL	= 1 << 4,		// adds the named log level, e.g. [WARNING]
				eBAI_NAME				= 1 << 5,		// adds the log name, e.g. [MASTER]
				eBAI_NEWLINE		= 1 << 6,		// auto appends a newline to each log
				eBAI_THREADID		= 1 << 7,		// adds the platform specific thread ID
				eBAI_TIMESTAMP	= 1 << 8,		// adds a timestamp, e.g. [00:00:00.000]

				eBAI_ALL				= (eBAI_LOCATION | eBAI_LOG_LEVEL | eBAI_NAME | eBAI_NEWLINE | eBAI_THREADID | eBAI_TIMESTAMP),
				eBAI_COMMON			= (eBAI_LOG_LEVEL | eBAI_NAME | eBAI_NEWLINE | eBAI_TIMESTAMP),

				// Targets
				eBT_CONSOLE			= 1 << 9,
				eBT_DEBUGGER		= 1 << 10, // N.B. Only on Windows
				eBT_FILE				= 1 << 11,
				eBT_STDOUT			= 1 << 12,

				eBT_ALL					= (eBT_CONSOLE | eBT_DEBUGGER | eBT_FILE | eBT_STDOUT),
			}; // End [enum eBehaviour]

			//------------------------------------------------------------------------

		public:
			CLog(CLog& parent, const char* name);
			CLog(CLog& parent, const char* name, uint32 flags);
			virtual ~CLog(void);

			bool IsActive(void) const;
			bool SetActive(bool set);
			uint32 GetFlags(void) const;
			uint32 SetFlags(uint32 flags);

			// N.B remember hidden 'this' pointer is parameter 1, so 'const char* format' is
			// parameter 5 in __attribute__ specifier in Log() declaration below
			bool Log(const char* file, uint32 line, uint32 level, const char* format, ...) __attribute__((format(printf, 5, 6)));

			static void ForceCrashOnFatalLog(void) { s_crashOnFatalLog = true; }
			static void SuppressCrashOnFatalLog(void) { s_crashOnFatalLog = false; }
			static uint32 GetDefaultLogFlags(void) { return s_defaultLogBehaviour; }
			static void SetDefaultLogFlags(uint32 flags) { s_defaultLogBehaviour = flags; }

			//------------------------------------------------------------------------
			
		private:
			CLog(void);

			//------------------------------------------------------------------------

		private:
			CLog* m_pParent;
			const char* m_name;
			uint32 m_flags;
			static uint32 s_defaultLogBehaviour;
			static bool s_crashOnFatalLog;

		public:
#if defined(RELEASE)
			static const eLogLevel s_logLevel;
#else
			static int64 s_logLevel;
#endif // defined(RELEASE)

			//------------------------------------------------------------------------
		}; // End [class CLog]

		// The master log is the root from which all other logs depend and generally
		// should not be used directly, other than to SetActive() to enable/disable
		// logging globally.
		CLog& GetMasterLog(void);

		// The engine log is used for engine side logging; subsytem logs should
		// depend from this; never try this at global scope though due to the fact
		// that the order of globally constructed objects cannot be guaranteed
		// between compilation units
		CLog& GetEngineLog(void);

		// The game log is used for game side logging; subsytem logs should depend
		// from this; never try this at global scope though due to the fact that
		// the order of globally constructed objects cannot be guaranteed between
		// compilation units
		CLog& GetGameLog(void);

		//==========================================================================
	} // End [namespace system]

	//============================================================================
} // End [namespace engine]

#include "system/log.inl"

//==============================================================================

#if LOG_ELIDE_ALL_LOGS
#define LOG(_log_, _level_, _format_, ...)
#else // LOG_ELIDE_ALL_LOGS
#define LOG(_log_, _level_, _format_, ...) (((engine::system::CLog::s_logLevel >= _level_) && ((_log_).IsActive())) ? (_log_).Log(__FILE__, __LINE__, _level_, _format_, ## __VA_ARGS__) : false)
#endif // LOG_ELIDE_ALL_LOGS

#define LOG_DEBUG(_log_, _format_, ...) LOG(_log_, engine::system::CLog::eLL_DEBUG, _format_, ## __VA_ARGS__)
#define LOG_VERBOSE(_log_, _format_, ...) LOG(_log_, engine::system::CLog::eLL_VERBOSE, _format_, ## __VA_ARGS__)
#define LOG_INFO(_log_, _format_, ...) LOG(_log_, engine::system::CLog::eLL_INFO, _format_, ## __VA_ARGS__)
#define LOG_TERSE(_log_, _format_, ...) LOG(_log_, engine::system::CLog::eLL_TERSE, _format_, ## __VA_ARGS__)
#define LOG_WARNING(_log_, _format_, ...) LOG(_log_, engine::system::CLog::eLL_WARNING, _format_, ## __VA_ARGS__)
#define LOG_ERROR(_log_, _format_, ...) LOG(_log_, engine::system::CLog::eLL_ERROR, _format_, ## __VA_ARGS__)
#define LOG_FATAL(_log_, _format_, ...) LOG(_log_, engine::system::CLog::eLL_FATAL, _format_, ## __VA_ARGS__)
#define LOG_ALWAYS(_log_, _format_, ...) LOG(_log_, engine::system::CLog::eLL_ALWAYS, _format_, ## __VA_ARGS__)

#define ENGINE_LOGGER engine::system::GetEngineLog()
#define GAME_LOGGER engine::system::GetGameLog()

//==============================================================================

#endif // !defined(__LOG_H__)
// EOF

