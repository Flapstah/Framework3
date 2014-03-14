#if !defined(__DEBUG_H__)
#define __DEBUG_H__

//==============================================================================

#if (ENABLE_TRACE)

namespace engine
{
	//============================================================================
	// CTrace
	//============================================================================
	class CTrace
	{
	public:
		CTrace(const char* entryPoint);
		~CTrace(void);

		static const char* CreateString(const char* format, ...) __attribute__((format(printf, 1, 2)));

		static void On(void);
		static void Off(void);

	private:
#if DEBUG_TRACE_USE_LOGGER
		static CLog* m_pLog;
#endif // DEBUG_TRACE_USE_LOGGER
		const char* m_entryPoint;
		static bool	s_active;
	}; // End [class CTrace]

	//============================================================================
} // End [namespace engine]

#define TRACE_STRING(_format_, ...) engine::CTrace::CreateString(_format_, ## __VA_ARGS__)
#define TRACE engine::CTrace _functionTracer(TRACE_STRING("%s(%d): %s", __FILE__, __LINE__, __FUNCTION_SIGNATURE__))
#define TRON engine::CTrace::On()
#define TROFF engine::CTrace::Off()

#else

#define TRACE
#define TRON
#define TROFF

#endif // (ENABLE_TRACE)

//==============================================================================

#endif // !defined(__DEBUG_H__)
// EOF
