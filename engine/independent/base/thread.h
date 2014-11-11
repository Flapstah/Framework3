#if !defined(__THREAD_H__)
#define __THREAD_H__

//==============================================================================

#include <boost/thread.hpp>
#include <utility/callback.h>
#include <time/timevalue.h>

//==============================================================================

namespace engine
{
	//============================================================================

	namespace base
	{
		//==========================================================================
		// CThread
		//==========================================================================
		class CThread
		{
			//========================================================================
		public:

			enum eThreadStatus
			{
				eTS_Indeterminate,
				eTS_Running,
				eTS_Terminated
			}; // End [enum eThreadStatus]

			enum eTerminationReason
			{
				eTR_None,				// Not terminated
				eTR_Finished,		// Internal expiration of thread (natural)
				eTR_Break,			// External expiration of thread (requested)
				eTR_Abort				// External expiration of thread (forced)
			}; // End [enum eTerminationReason]

			//------------------------------------------------------------------------

			typedef uint32 THREAD_ID;

			//------------------------------------------------------------------------

			CThread(void);
			virtual ~CThread(void);

			virtual bool Initialise(void) { return true; }
			virtual void Terminate(bool immediate = false);
			virtual void Uninitialise(void) {}

			// Check this thread for interruptions
			inline void InterruptionPoint(void) { boost::this_thread::interruption_point(); }

			//------------------------------------------------------------------------

		protected:
			boost::thread m_thread;
			boost::mutex m_mutex;
			volatile eThreadStatus m_threadStatus;
			eTerminationReason m_terminationReason;

			void Run(void);
			virtual void Tick(void) {};

			//========================================================================
		};	// End [class CThread]

		//==========================================================================
	} // End [namespace base]

	//============================================================================
} // End [namespace engine]

//==============================================================================
#endif // End [!defined(__THREAD_H__)]
// EOF

