#if !defined(__UNITTEST_H__)
#define __UNITTEST_H__

//==============================================================================

#include "common/itime.h"

using namespace engine::time;

//==============================================================================

namespace test
{
	//============================================================================
	// CUnitTest
	//============================================================================
	class CUnitTest
	{
		public:
			//========================================================================
			// enum eTestStatus
			//========================================================================
			enum eTestStatus
			{
				eTS_SUCCESS				= 0,
				eTS_FINISHED			= 1,
				eTS_FAIL_CONTINUE	= 2,
				eTS_FAIL_ABORT		= 3
			}; // End [enum eTestStatus]

			//========================================================================
			// enum eTestVerbosity
			//========================================================================
			enum eTestVerbosity
			{
				eTV_SILENT							= 0,
				eTV_OVERALL_RESULT_ONLY	= 1,
				eTV_STAGE_RESULTS_ONLY	= 2,
				eTV_STAGE_DETAILS				= 3
			}; // End [enum eTestVerbosity]

			//========================================================================

																CUnitTest(const char* name);
			virtual										~CUnitTest(void);

			virtual				bool				Initialise(eTestVerbosity verbosity) = 0;
			virtual	const	CTimeValue&	Start(void) = 0;
			virtual				eTestStatus	Update(void) = 0;
			virtual	const	CTimeValue&	End(void) = 0;
			virtual				void				Uninitialise(void) = 0;

										void				Log(eTestVerbosity targetLevel, const char* format, ...);

			//========================================================================

		protected:
			CTimeValue m_timeStarted;
			CTimeValue m_timeEnded;
			ITime* m_pTime;
			const char* m_name;
			eTestStatus m_status;
			eTestVerbosity m_verbosity;
	}; // End [class CUnitTest]

	//============================================================================
} // End [namespace test]

//==============================================================================
#endif // !defined(__UNITTEST_H__)
// [EOF]

