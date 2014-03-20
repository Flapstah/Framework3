#if !defined(__CVARTEST_H__)
#define __CVARTEST_H__

//==============================================================================

#include "unittest.h"

#include "system/console.h"

//==============================================================================

namespace test
{
	//============================================================================
	// CCVarTest
	//============================================================================
	class CCVarTest : public CUnitTest
	{
		//==========================================================================
		typedef CUnitTest PARENT;

		public:
																CCVarTest(void);
			virtual										~CCVarTest(void);

			// CUnitTest
			virtual				bool				Initialise(void);
			// ~CUnitTest

		//==========================================================================

		protected:
			static	uint32						ConsoleVariableLifecycle(CUnitTest* pParent);
			static	uint32						IntegerVariableOperations(CUnitTest* pParent);
			static	uint32						IntegerConstantVariableOperations(CUnitTest* pParent);
			static	uint32						FloatVariableOperations(CUnitTest* pParent);
			static	uint32						FloatConstantVariableOperations(CUnitTest* pParent);
			static	uint32						StringVariableOperations(CUnitTest* pParent);
			static	uint32						StringConstantVariableOperations(CUnitTest* pParent);
			static	uint32						ConsoleCommandTest(CUnitTest* pParent);

		private:
			static	engine::CConsole::TIVariablePtr m_pCVar;
	}; // End [struct class CCVarTest : public CUnitTest]

	//============================================================================
} // End [namespace test]

//==============================================================================
#endif // !defined(__CVARTEST_H__)
// [EOF]

