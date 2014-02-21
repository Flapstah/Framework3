#include "common/stdafx.h"

#if !USE_OPENGL_SUPERBIBLE

#include "common/itime.h"
#include "common/commandline.h"
#include "unit_tests/cvartest.h"
#include "unit_tests/typetest.h"
#include "unit_tests/timetest.h"
#include "common/console.h"
#include "common/log.h"
#include "common/version.h"

#include <cmath>

//==============================================================================

int main(int argc, char* argv[])
{
	//	IGNORE_PARAMETER(argc);
	//	IGNORE_PARAMETER(argv);

	/*
	if (!LOG_DEBUG(test, "Debug log test\n")) printf("eLL_DEBUG elided\n");
	if (!LOG_INFO(test, "Info log test\n")) printf("eLL_INFO elided\n");
	if (!LOG_WARNING(test, "Warning log test\n")) printf("eLL_WARNING elided\n");
	if (!LOG_ERROR(test, "Error log test\n")) printf("eLL_ERROR elided\n");
	if (!LOG_FATAL(test, "Fatal log test\n")) printf("eLL_FATAL elided\n");
	if (!LOG_ALWAYS(test, "Always log test\n")) printf("eLL_ALWAYS elided\n");
	*/

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

		{
			test::CCVarTest test;
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

	printf("All done.\n");

	return 0;
}

//==============================================================================

#endif // !USE_OPENGL_SUPERBIBLE

// [EOF]
