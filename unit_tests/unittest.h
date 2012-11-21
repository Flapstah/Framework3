#if !defined(__UNITTEST_H__)
#define __UNITTEST_H__

//==============================================================================

#include "common/itime.h"

//==============================================================================

namespace test
{
	//============================================================================
	// CUnitTest
	//============================================================================
	class CUnitTest
	{
		public:
			enum eTestStatus
			{
				eTS_SUCCESS = 0,
				eTS_FAIL_CONTINUE = 1,
				eTS_FAIL_ABORT = 2
			}; // End [enum eTestStatus]

			enum eTestVerbosity
			{
				eTV_SILENT = 0,
				eTV_OVERALL_RESULT_ONLY = 1,
				eTV_STAGE_RESULTS_ONLY = 2,
				eTV_STAGE_DETAILS = 3
			}; // End [enum eTestVerbosity]

			CUnitTest(const char* name);
			virtual ~CUnitTest(void);

			virtual bool Initialise(eTestVerbosity verbosity) = 0;
			virtual const engine::time::CTimeValue& Start(void) = 0;
			virtual eTestStatus Update(void) = 0;
			virtual const engine::time::CTimeValue& End(void) = 0;
			virtual void Uninitialise(void) = 0;

			void Log(eTestVerbosity targetLevel, const char* format, ...);

		protected:
			engine::time::CTimeValue m_timeStarted;
			engine::time::CTimeValue m_timeEnded;
			const char* m_name;
			eTestStatus m_status;
			eTestVerbosity m_verbosity;
	}; // End [class CUnitTest]

	//============================================================================
} // End [namespace test]

//==============================================================================
#endif // !defined(__UNITTEST_H__)
// [EOF]

