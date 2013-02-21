#include "common/stdafx.h"

#define USE_OPENGL_SUPERBIBLE (1)

enum eExample
{
	eE_Block
};

#define EXAMPLE (eE_Block)

#if USE_OPENGL_SUPERBIBLE

#include "GLTools/src/openglsuperbible_uber.cpp"

#if (EXAMPLE == eE_Block)
#include "GLSB/Block/Block.cpp"
#endif // (EXAMPLE == eE_Block)

#pragma message "GLAPI = [" STRINGIZE(GLAPI) "]"

#else

#include "common/itime.h"
#include "unit_tests/typetest.h"
#include "unit_tests/timetest.h"

//==============================================================================

void DumpArgs(int argc, char* argv[])
{
	printf("\n*** Passed %d arguments:\n", argc);
	for (int i = 0; i < argc; ++i)
	{
		printf("[%d]: [%s]\n", i, argv[i]);
	}
	printf("*** End argument list\n\n");
}

//==============================================================================

int main(int argc, char* argv[])
{
//	IGNORE_PARAMETER(argc);
//	IGNORE_PARAMETER(argv);
	DumpArgs(argc, argv);
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
	printf("All done.\n");

	return 0;
}

//==============================================================================

#endif // USE_OPENGL_SUPERBIBLE

// [EOF]
