#include "common/stdafx.h"

#include "cvartest.h"
#include "logtest.h"
#include "timetest.h"
#include "typetest.h"

//==============================================================================

int main(int argc, char* argv[])
{
	TRACE;

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

