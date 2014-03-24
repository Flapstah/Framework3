#if !defined(__LOG_H__)
#define __LOG_H__

//==============================================================================

namespace engine
{
	//============================================================================
	// CLog
	//============================================================================
	class CLog
	{
		//--------------------------------------------------------------------------

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
			};

		//--------------------------------------------------------------------------

			enum eBehaviour
			{
				eB_ACTIVE				= 1 << 0,		// Log is active and will produce output
				eB_NO_STDERR		= 1 << 1,		// Log will NOT use stderr (eBT_STANDARD
																		// target will normally output to stderr for
																		// eLL_FATAL, eLL_ERROR and eLL_WARNING log
																		// levels, with everything else going to
																		// stdout.  Setting this flag will force
																		// *all* output through stdout.)

				// Additional info
				eBAI_LOCATION		= 1 << 2,
				eBAI_LOG_LEVEL	= 1 << 3,
				eBAI_NAME				= 1 << 4,
				eBAI_NEWLINE		= 1 << 5,
				eBAI_THREADID		= 1 << 6,
				eBAI_TIMESTAMP	= 1 << 7,

				eBAI_ALL				= (eBAI_LOCATION | eBAI_LOG_LEVEL | eBAI_NAME | eBAI_NEWLINE | eBAI_THREADID | eBAI_TIMESTAMP),

				// Targets
				eBT_CONSOLE			= 1 << 8,
				eBT_DEBUGGER		= 1 << 9, // N.B. Only on Windows
				eBT_FILE				= 1 << 10,
				eBT_STANDARD		= 1 << 11,

				eBT_ALL					= (eBT_CONSOLE | eBT_DEBUGGER | eBT_FILE | eBT_STANDARD),
			};

		//--------------------------------------------------------------------------

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

			// The master log is the root from which all other logs depend and should
			// not be used directly, other than to SetActive() to enable/disable
			// logging globally.
			static CLog& GetMasterLog(void);

			// The engine log is used for engine side logging; subsytem logs should
			// depend from this; never try this at global scope though due to the fact
			// that the order of globally constructed objects cannot be guaranteed
			// between compilation units
			static CLog& GetEngineLog(void);

			// The game log is used for game side logging; subsytem logs should depend
			// from this; never try this at global scope though due to the fact that
			// the order of globally constructed objects cannot be guaranteed between
			// compilation units
			static CLog& GetGameLog(void);

		private:
			CLog(void);

		//--------------------------------------------------------------------------

		private:
			CLog* m_pParent;
			const char* m_name;
			uint32 m_flags;

		public:
#if defined(RELEASE)
			static const eLogLevel s_logLevel;
#else
			static int64 s_logLevel;
#endif // defined(RELEASE)

		//--------------------------------------------------------------------------
	}; // End [class CLog]

	//============================================================================
} // End [namespace engine]

#include "system/log.inl"

//==============================================================================

#if LOG_ELIDE_ALL_LOGS
#define LOG(_log_, _level_, _format_, ...)
#else // LOG_ELIDE_ALL_LOGS
#define LOG(_log_, _level_, _format_, ...) (((engine::CLog::s_logLevel >= _level_) && ((_log_).IsActive())) ? (_log_).Log(__FILE__, __LINE__, _level_, _format_, ## __VA_ARGS__) : false)
#endif // LOG_ELIDE_ALL_LOGS

#define LOG_DEBUG(_log_, _format_, ...) LOG(_log_, engine::CLog::eLL_DEBUG, _format_, ## __VA_ARGS__)
#define LOG_VERBOSE(_log_, _format_, ...) LOG(_log_, engine::CLog::eLL_VERBOSE, _format_, ## __VA_ARGS__)
#define LOG_INFO(_log_, _format_, ...) LOG(_log_, engine::CLog::eLL_INFO, _format_, ## __VA_ARGS__)
#define LOG_TERSE(_log_, _format_, ...) LOG(_log_, engine::CLog::eLL_TERSE, _format_, ## __VA_ARGS__)
#define LOG_WARNING(_log_, _format_, ...) LOG(_log_, engine::CLog::eLL_WARNING, _format_, ## __VA_ARGS__)
#define LOG_ERROR(_log_, _format_, ...) LOG(_log_, engine::CLog::eLL_ERROR, _format_, ## __VA_ARGS__)
#define LOG_FATAL(_log_, _format_, ...) LOG(_log_, engine::CLog::eLL_FATAL, _format_, ## __VA_ARGS__)
#define LOG_ALWAYS(_log_, _format_, ...) LOG(_log_, engine::CLog::eLL_ALWAYS, _format_, ## __VA_ARGS__)

#define ENGINE_LOGGER engine::CLog::GetEngineLog()
#define GAME_LOGGER engine::CLog::GetGameLog()

//==============================================================================

#endif // !defined(__LOG_H__)
// EOF

