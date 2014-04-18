#include "common/stdafx.h"

#include "base/engine.h"

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

	engine::base::CEngine& myEngine = engine::base::CEngine::Get();
	myEngine.Initialise(argc, argv);

	LOG_ALWAYS(GAME_LOGGER, "Starting unit tests...\n");

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

	myEngine.Uninitialise(); // Not strictly needed as will be called when engine destructed
	return 0;
}

//==============================================================================
// [EOF]

