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
		//==========================================================================
		typedef CUnitTest PARENT;

		public:
																CTimeTest(void);
			virtual										~CTimeTest(void);

			// CUnitTest
			virtual				bool				Initialise(eTestVerbosity verbosity);
			// ~CUnitTest

		//==========================================================================

		protected:
			static	uint32						TimeValueOperations(CUnitTest* pParent);

		private:
			CTimeValue m_testValue;
	}; // End [struct class CTimeTest : public CUnitTest]

	//============================================================================
} // End [namespace test]

//==============================================================================
#endif // !defined(__TIMETEST_H__)
// [EOF]

