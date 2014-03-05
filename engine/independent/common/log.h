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
				eLL_INFO,
				eLL_DEBUG
			};

		//--------------------------------------------------------------------------

			enum eBehaviour
			{
				// Additional info
				eBAI_LOCATION		= 1 << 0,
				eBAI_NAME				= 1 << 1,
				eBAI_TIMESTAMP	= 1 << 2,
				eBAI_THREADID		= 1 << 3,

				// Targets
				eBT_FILE				= 1 << 4,
				eBT_CONSOLE			= 1 << 5,
				eBT_STANDARD		= 1 << 6,
				eBT_DEBUGGER		= 1 << 7, // N.B. Only on Windows
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
			// parameter 4 in __attribute__ specifier in Log() declaration below
			bool Log(const char* file, uint32 line, const char* format, ...) __attribute__((format(printf, 4, 5)));

		private:
			CLog(void);

		//--------------------------------------------------------------------------

		private:
			CLog* m_pParent;
			const char* m_name;
			uint32 m_flags;
			bool m_active;

		public:
			static CLog s_logRoot;
#if defined(RELEASE)
			static const eLogLevel s_logLevel;
#else
			static int64 s_logLevel;
	private:
			// used to register/unregister log level cvar
			static uint32 m_refActiveLogs;
#endif // defined(RELEASE)

		//--------------------------------------------------------------------------
	}; // End [class CLog]

	//============================================================================
} // End [namespace engine]

#include "common/log.inl"

//==============================================================================

#define LOG(_log_, _level_, _format_, ...) (((engine::CLog::s_logLevel >= _level_) && (_log_.IsActive())) ? _log_.Log(__FILE__, __LINE__, _format_, ## __VA_ARGS__) : false)

#define LOG_DEBUG(_log_, _format_, ...) LOG(_log_, engine::CLog::eLL_DEBUG, _format_, ## __VA_ARGS__)
#define LOG_INFO(_log_, _format_, ...) LOG(_log_, engine::CLog::eLL_INFO, _format_, ## __VA_ARGS__)
#define LOG_WARNING(_log_, _format_, ...) LOG(_log_, engine::CLog::eLL_WARNING, _format_, ## __VA_ARGS__)
#define LOG_ERROR(_log_, _format_, ...) LOG(_log_, engine::CLog::eLL_ERROR, _format_, ## __VA_ARGS__)
#define LOG_FATAL(_log_, _format_, ...) LOG(_log_, engine::CLog::eLL_FATAL, _format_, ## __VA_ARGS__)
#define LOG_ALWAYS(_log_, _format_, ...) LOG(_log_, engine::CLog::eLL_ALWAYS, _format_, ## __VA_ARGS__)

#define DEFAULT_LOGGER engine::CLog::s_logRoot

//==============================================================================

#endif // !defined(__LOG_H__)
// EOF


