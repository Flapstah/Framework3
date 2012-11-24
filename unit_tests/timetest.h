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
			// ~CUnitTest

			//========================================================================

			static	uint32 TimeValueOperations(CUnitTest* pParent);

		protected:
			CTimeValue m_testValue;
	}; // End [struct class CTimeTest : public CUnitTest]

	//============================================================================
} // End [namespace test]

//==============================================================================
#endif // !defined(__TIMETEST_H__)
// [EOF]

