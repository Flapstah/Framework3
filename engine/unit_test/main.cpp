#include "common/stdafx.h"

#include "base/engine.h"

#include "tests/cvartest.h"
#include "tests/logtest.h"
#include "tests/timetest.h"
#include "tests/typetest.h"

//==============================================================================

#if defined(TRACE_ENABLE)
#undef TRACE_ENABLE
#endif // defined(TRACE_ENABLE)
#define TRACE_ENABLE false

//==============================================================================

int main(int argc, char* argv[])
{
	TRACE(TRACE_ENABLE);

	/*
	enum eSyntaxID
	{
		eSID_LOG = engine::system::CConfiguration::eSID_FIRST_USERID,
		eSID_ROOT,
	};
	*/
	engine::system::CLog::SetDefaultLogFlags(engine::system::CLog::GetDefaultLogFlags() & ~engine::system::CLog::eBT_STDOUT);
	engine::system::CConfiguration config;
	config.Parse(argc, argv);

	engine::base::CEngine& myEngine = engine::base::CEngine::Get();
	myEngine.Initialise(config);

	LOG_ALWAYS(GAME_LOGGER, "Starting unit tests...\n");

	{
		uint32 errors = 0;
		test::CTypeTest test;
		UNIT_TEST(test, &errors);

		if (errors != 0)
		{
			LOG_ERROR(GAME_LOGGER, "Unit test [CTypeTest] had %d errors", errors);
		}
	}

	{
		uint32 errors = 0;
		test::CTimeTest test;
		UNIT_TEST(test, &errors);

		if (errors != 0)
		{
			LOG_ERROR(GAME_LOGGER, "Unit test [CTimeTest] had %d errors", errors);
		}
	}

	{
		// Turn off the engine logger here because unit tests will trigger error logs
		// when testing for error conditions
		ENGINE_LOGGER.SetActive(false);

		uint32 errors = 0;
		test::CCVarTest test;
		UNIT_TEST(test, &errors);

		if (errors != 0)
		{
			LOG_ERROR(GAME_LOGGER, "Unit test [CVarTest] had %d errors", errors);
		}

		// Turn on the engine logger here
		ENGINE_LOGGER.SetActive(true);
	}

	{
		uint32 errors = 0;
		test::CLogTest test;
		UNIT_TEST(test, &errors);

		if (errors != 0)
		{
			LOG_ERROR(GAME_LOGGER, "Unit test [CVarTest] had %d errors", errors);
		}
	}

	LOG_ALWAYS(GAME_LOGGER, "All done.");

	myEngine.Uninitialise(); // Not strictly needed as will be called when engine destructed
	return 0;
}

//==============================================================================
// [EOF]

