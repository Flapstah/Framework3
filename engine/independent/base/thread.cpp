#include "common/stdafx.h" // log.h included here

#include "base/thread.h"

//==============================================================================

#if defined(TRACE_ENABLE)
#undef TRACE_ENABLE
#endif // defined(TRACE_ENABLE)
#define TRACE_ENABLE false

//==============================================================================

namespace engine
{
	//============================================================================

	namespace base
	{
		//==========================================================================

		CThread::CThread(const char* name)
			: m_name(name)
			, m_threadStatus(eTS_Indeterminate)
			, m_terminationReason(eTR_None)
		{
			LOG_ALWAYS(ENGINE_LOGGER, "Creating thread [%s]", m_name.c_str());
		}

		//==========================================================================

		CThread::~CThread(void)
		{
			Uninitialise();
			LOG_ALWAYS(ENGINE_LOGGER, "Destroying thread [%s]", m_name.c_str());
		}

		//==========================================================================

		bool CThread::Initialise(void)
		{
			// This will trigger the thread to start running
			LOG_ALWAYS(ENGINE_LOGGER, "Initialising and starting thread [%s]", m_name.c_str());
			m_threadStatus = eTS_Running;
			m_thread = boost::thread(&CThread::Run, this);

			return true;
		}

		//==========================================================================

		void CThread::Terminate(bool immediate /* = false */)
		{
			LOG_ALWAYS(ENGINE_LOGGER, "Thread [%s] terminating", m_name.c_str());
			// Run from any thread
			m_mutex.lock();

			m_threadStatus = eTS_Terminated;

			if (immediate == true)
			{
				// Indicate an immediate exit, and raise an interruption exception to
				// expedite that
				m_terminationReason = eTR_Abort;
				m_thread.interrupt();
			}
			else
			{
				// Indicate that the thread should exit as soon as it can
				m_terminationReason = eTR_Break;
			}

			m_mutex.unlock();
		}

		//==========================================================================

		void CThread::Run(void)
		{
			while (m_threadStatus == eTS_Running)
			{
				try
				{
					InterruptionPoint();
					Tick();
				}

				catch (boost::thread_interrupted& e)
				{
					LOG_ALWAYS(ENGINE_LOGGER, "Thread [%s] interrupted", m_name.c_str());
				}
			}

			const char* reason;
			switch (m_terminationReason)
			{
			case eTR_Finished:
				reason = "eTR_Finished";
				break;
			case eTR_Break:
				reason = "eTR_Break";
				break;
			case eTR_Abort:
				reason = "eTR_Abort";
				break;
			default:
				reason = "Unknown";
				break;
			}
			LOG_ALWAYS(ENGINE_LOGGER, "Thread [%s] terminated, reason [%s]", m_name.c_str(), reason);
			Uninitialise();
		}

		//==========================================================================
	} // End [namespace base]

	//==========================================================================
} // End [namespace engine]

//==============================================================================
// EOF

