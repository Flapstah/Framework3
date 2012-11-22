#if !defined(__TIMETEST_H__)
#define __TIMETEST_H__

//==============================================================================

#include "unittest.h"

//==============================================================================

namespace test
{
	//============================================================================
	// CTimeTest
	//============================================================================
	class CTimeTest : public CUnitTest
	{
			//========================================================================

		public:
																CTimeTest(void);
			virtual										~CTimeTest(void);

			// CUnitTest

			virtual				bool				Initialise(eTestVerbosity verbosity);
			virtual	const	CTimeValue&	Start(void);
			virtual				eTestStatus	Update(void);
			virtual	const	CTimeValue&	End(void);
			virtual				void				Uninitialise(void);
			// ~CUnitTest

			//========================================================================

		protected:
			CTimeValue m_testValue0;
	}; // End [struct class CTimeTest : public CUnitTest]

	//============================================================================
} // End [namespace test]

//==============================================================================
#endif // !defined(__TIMETEST_H__)
// [EOF]

