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

		CThread::CThread(void)
			: m_threadStatus(eTS_Indeterminate)
			, m_terminationReason(eTR_None)
		{
			LOG_ALWAYS(ENGINE_LOGGER, "[CThread::CThread()]");
			if (Initialise() == true)
			{
				LOG_ALWAYS(ENGINE_LOGGER, "[CThread::CThread()] initialised...starting thread");
				m_threadStatus = eTS_Running;
				m_thread = boost::thread(&CThread::Run, this);
			}
		}

		//==========================================================================

		CThread::~CThread(void)
		{
			Uninitialise();
			LOG_ALWAYS(ENGINE_LOGGER, "[CThread::~CThread()]");
		}

		//==========================================================================

		void CThread::Run(void)
		{
			static uint32 counter = 0;
			while (m_threadStatus == eTS_Running)
			{
				try
				{
					InterruptionPoint();

					LOG_ALWAYS(ENGINE_LOGGER, "[CThread::Run()]: Running...%d", counter);

					if (counter++ < 10)
					{
						boost::this_thread::sleep_for(boost::chrono::milliseconds(1000));
					}
					else
					{
						m_threadStatus = eTS_Terminated;
						m_terminationReason = eTR_Finished;
					}
				}

				catch (boost::thread_interrupted& e)
				{
					LOG_ALWAYS(ENGINE_LOGGER, "[CThread::Run()]: thread interrupted");
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
			LOG_ALWAYS(ENGINE_LOGGER, "[CThread::Run()]: thread terminated [%s]", reason);
			Uninitialise();
		}

		//==========================================================================

		void CThread::Terminate(bool immediate /* = false */)
		{
			LOG_ALWAYS(ENGINE_LOGGER, "[CThread::Terminate()]");
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
	} // End [namespace base]

	//==========================================================================
} // End [namespace engine]

//==============================================================================
// EOF

