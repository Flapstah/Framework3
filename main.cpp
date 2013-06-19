#include "common/stdafx.h"

#if !USE_OPENGL_SUPERBIBLE

#include "common/itime.h"
#include "common/commandargs.h"
#include "unit_tests/typetest.h"
#include "unit_tests/timetest.h"
#include "common/console.h"

#include <cmath>

//==============================================================================

int main(int argc, char* argv[])
{
	//	IGNORE_PARAMETER(argc);
	//	IGNORE_PARAMETER(argv);

	if (engine::CCommandArgs::Parse(argc, argv) == engine::CCommandArgs::ePS_SUCCESS)
	{

		//	DumpArgs(argc, argv);
		/*
			 {
			 test::CTypeTest test;
			 test.Start();
			 while (test.Update() == test::CUnitTest::eTS_RUNNING);
			 test.End();
			 }

			 {
			 test::CTimeTest test;
			 test.Start();
			 while (test.Update() == test::CUnitTest::eTS_RUNNING);
			 test.End();
			 }
			 */

		/*
			 uint32 x = engine::CompileTimeStringHash("a nice long string to hash");
			 printf("x %08x\n", x);
			 uint32 y = engine::CRunTimeStringHash::Calculate("a nice long string to hash");
			 printf("y %08x\n", y);
			 */

		/*
			 int32 variable = 0;
			 uint32 flags = engine::CConsole::IVariable::eF_CLAMP_TO_RANGE;
			 engine::CConsole::IVariable::TOnChangeCallback pCallback;
			 pCallback.m_pOnChangeI32 = NULL;
			 engine::CConsole::CI32Variable cvar(variable, int32 123, int32 100, int32 200, uint32 engine::CConsole::CI32Variable::eF_CLAMP_TO_RANGE, "variable", "test console variable", NULL);
			 */

	}

	printf("All done.\n");

	return 0;
}

//==============================================================================

#endif // !USE_OPENGL_SUPERBIBLE

// [EOF]
