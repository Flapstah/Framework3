#include "common/stdafx.h" // debug.h included here

//==============================================================================

#if (ENABLE_TRACE)

namespace engine
{
	//============================================================================

	namespace utility
	{
		//==========================================================================
#if DEBUG_TRACE_START_ENABLED
		bool CTrace::s_active = true;
#else
		bool CTrace::s_active = false;
#endif // DEBUG_TRACE_START_ENABLED

#if DEBUG_TRACE_USE_LOGGER
#define _TRACE(_format_, ...) LOG_DEBUG(*m_pLog, _format_, ## __VA_ARGS__)
		engine::system::CLog* CTrace::m_pLog = NULL;
#else
#define _TRACE(_format_, ...) printf(_format_, ## __VA_ARGS__)
#endif // DEBUG_TRACE_USE_LOGGER

		//==========================================================================

		CTrace::CTrace(bool enable, const char* entryPoint)
			: m_entryPoint(entryPoint)
			, m_enable(enable)
		{
			if (m_enable)
			{
#if DEBUG_TRACE_USE_LOGGER
				static engine::system::CLog lazyLogConstruction(engine::system::GetMasterLog(), "Trace", engine::system::CLog::eB_ACTIVE | /*engine::system::CLog::eBAI_NEWLINE | */engine::system::CLog::eBAI_NAME | /*engine::system::CLog::eBAI_TIMESTAMP |*/ engine::system::CLog::eBT_ALL);
				m_pLog = &lazyLogConstruction;
#endif // DEBUG_TRACE_USE_LOGGER

				if (s_active)
				{
					_TRACE("[ENTER]: %s\n", m_entryPoint);
				}
			}	
		}

		//==========================================================================

		CTrace::~CTrace(void)
		{
			if (m_enable && s_active)
			{
				_TRACE("[EXIT]: %s\n", m_entryPoint);
			}
		}

		//==========================================================================

		const char* CTrace::CreateString(const char* format, ...)
		{
			va_list argList;
			static char buffer[LOG_BUFFER_SIZE];

			va_start(argList, format);
			vsnprintf(buffer, LOG_BUFFER_SIZE-1, format, argList);
			va_end(argList);

			return buffer;
		}

		//==========================================================================

		void CTrace::On(void)
		{
			s_active = true;
		}

		//==========================================================================

		void CTrace::Off(void)
		{
			s_active = false;
		}

		//==========================================================================
	} // End [namespace utility]

	//============================================================================
} // End [namespace engine]

#endif // (ENABLE_TRACE)

//==============================================================================
// EOF

