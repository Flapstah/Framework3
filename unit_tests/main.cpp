#include "common/stdafx.h"

#include "cvartest.h"
#include "logtest.h"
#include "timetest.h"
#include "typetest.h"

//==============================================================================

int main(int argc, char* argv[])
{
	IGNORE_PARAMETER(argc);
	IGNORE_PARAMETER(argv);

	{
		test::CTypeTest test;
		UNIT_TEST(test);
	}

	{
		test::CTimeTest test;
		UNIT_TEST(test);
	}

	{
		test::CCVarTest test;
		UNIT_TEST(test);
	}

	{
		test::CLogTest test;
		UNIT_TEST(test);
	}
}

//==============================================================================
// [EOF]

