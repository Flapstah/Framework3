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

		int32 x = 0;
		engine::CConsole console;
		console.RegisterVariable(x);
	}

	printf("All done.\n");

	return 0;
}

//==============================================================================

#endif // !USE_OPENGL_SUPERBIBLE

// [EOF]
