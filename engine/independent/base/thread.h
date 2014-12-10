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
				eTR_InitFail,		// Internal expiration of thread (initialisation failure)
				eTR_Break,			// External expiration of thread (requested)
				eTR_Abort				// External expiration of thread (forced)
			}; // End [enum eTerminationReason]

			//------------------------------------------------------------------------

			typedef uint32 THREAD_ID;

			//------------------------------------------------------------------------

			CThread(const char* name);
			virtual ~CThread(void);

			//------------------------------------------------------------------------
			// These are run from the main (or other) thread
			//------------------------------------------------------------------------
			virtual bool Initialise(void);
			virtual void Terminate(bool immediate = false);
			virtual void Uninitialise(void) {}
			//------------------------------------------------------------------------

		protected:
			//------------------------------------------------------------------------
			// These are all run on the encapsulated thread
			//------------------------------------------------------------------------
			void Run(void);
			virtual bool ThreadInitialise(void) { return true; }
			virtual void Tick(void) {}
			virtual void ThreadTerminate(void) {}

			// Check this thread for interruptions
			inline void InterruptionPoint(void) { boost::this_thread::interruption_point(); }
			//------------------------------------------------------------------------

		protected:
			std::string m_name;
			boost::thread m_thread;
			boost::mutex m_mutex;
			volatile eThreadStatus m_threadStatus;
			eTerminationReason m_terminationReason;

			//========================================================================
		};	// End [class CThread]

		//==========================================================================
	} // End [namespace base]

	//============================================================================
} // End [namespace engine]

//==============================================================================
#endif // End [!defined(__THREAD_H__)]
// EOF

