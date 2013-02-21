#include "common/stdafx.h"

#define USE_OPENGL_SUPERBIBLE (0)

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
#define __STRINGIZE(_thing_) #_thing_
#define _STRINGIZE(_thing_) __STRINGIZE(_thing_)
#define A_TEST cock
#pragma message "A_TEST = " _STRINGIZE(A_TEST)
	printf("All done.\n");

	return 0;
}

//==============================================================================

#endif // USE_OPENGL_SUPERBIBLE

// [EOF]
