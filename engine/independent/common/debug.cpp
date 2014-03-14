#include "common/stdafx.h"

#include "common/debug.h"

//==============================================================================

namespace engine
{
#if DEBUG_TRACE_START_ENABLED
	bool CTrace::s_active = true;
#else
	bool CTrace::s_active = false;
#endif // DEBUG_TRACE_START_ENABLED

#if DEBUG_TRACE_USE_LOGGER
	CLog& CTrace::m_log = CLog::GetMasterLog();
#endif // DEBUG_TRACE_USE_LOGGER

	//============================================================================

	CTrace::CTrace(const char* entryPoint)
		: m_entryPoint(entryPoint)
	{
#if DEBUG_TRACE_USE_LOGGER
		static CLog lazyLogConstruction(CLog::GetMasterLog(), "Trace");
		m_log = lazyLogConstruction;
#endif // DEBUG_TRACE_USE_LOGGER

		if (s_active)
		{
#if DEBUG_TRACE_USE_LOGGER
			LOG_DEBUG(m_log, "[ENTER]: %s\n", m_entryPoint);
#else
			printf("[ENTER]: %s\n", m_entryPoint);
#endif // DEBUG_TRACE_USE_LOGGER
		}
	}

	//============================================================================

	CTrace::~CTrace(void)
	{
		if (s_active)
		{
#if DEBUG_TRACE_USE_LOGGER
			LOG_DEBUG(m_log, "[EXIT]: %s\n", m_entryPoint);
#else
			printf("[EXIT]: %s\n", m_entryPoint);
#endif // DEBUG_TRACE_USE_LOGGER
		}
	}

	//============================================================================

	void CTrace::On(void)
	{
		s_active = true;
	}

	//============================================================================

	void CTrace::Off(void)
	{
		s_active = false;
	}

	//============================================================================
} // End [namespace engine]

//==============================================================================
// EOF

