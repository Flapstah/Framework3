#include "common/stdafx.h"

#include "tests/cvartest.h"
#include "tests/logtest.h"
#include "tests/timetest.h"
#include "tests/typetest.h"

//==============================================================================

#define TRACE_ENABLE false

//==============================================================================

int main(int argc, char* argv[])
{
	TRACE(TRACE_ENABLE);

//	IGNORE_PARAMETER(argc);
//	IGNORE_PARAMETER(argv);

	for (uint32 i = 0; i < argc; ++i)
	{
		printf("[%i] [%s]\n", i, argv[i]);
	}

	LOG_ALWAYS(GAME_LOGGER, "Starting unit tests...");

	{
		test::CTypeTest test;
		UNIT_TEST(test);
	}

	{
		test::CTimeTest test;
		UNIT_TEST(test);
	}

	{
		// Turn off the engine logger here because unit tests will trigger error logs
		// when testing for error conditions
		ENGINE_LOGGER.SetActive(false);

		test::CCVarTest test;
		UNIT_TEST(test);

		// Turn on the engine logger here
		ENGINE_LOGGER.SetActive(true);
	}

	{
		test::CLogTest test;
		UNIT_TEST(test);
	}

	LOG_ALWAYS(GAME_LOGGER, "All done.");
}

//==============================================================================
// [EOF]

