#if !defined(__DEBUG_H__)
#define __DEBUG_H__

//==============================================================================

#include "common/log.h"

//==============================================================================

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

		static void On(void);
		static void Off(void);

	private:
#if DEBUG_TRACE_USE_LOGGER
		static CLog& m_log;
#endif // DEBUG_TRACE_USE_LOGGER
		const char* m_entryPoint;
		static bool	s_active;
	}; // End [class CTrace]

	//============================================================================
} // End [namespace engine]

//==============================================================================

#endif // !defined(__DEBUG_H__)
// EOF
