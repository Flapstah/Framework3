#if !defined(__LOGTEST_H__)
#define __LOGTEST_H__

//==============================================================================

#include "unittest.h"

#include "common/console.h"

//==============================================================================

namespace test
{
	//============================================================================
	// CLogTest
	//============================================================================
	class CLogTest : public CUnitTest
	{
		//==========================================================================
		typedef CUnitTest PARENT;

		public:
																CLogTest(void);
			virtual										~CLogTest(void);

			// CUnitTest
			virtual				bool				Initialise(void);
			// ~CUnitTest

		//==========================================================================

		protected:
			static	uint32						DefaultLog(CUnitTest* pParent);
			static	uint32						CustomLog(CUnitTest* pParent);

		private:
	}; // End [struct class CLogTest : public CUnitTest]

	//============================================================================
} // End [namespace test]

//==============================================================================
#endif // !defined(__LOGTEST_H__)
// [EOF]


