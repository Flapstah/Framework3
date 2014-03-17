#include "common/stdafx.h"

#include "logtest.h"

#define LOG_TEST(_log_, _level_, _stage_type_) pThis->Test(#_level_ " log test", (LOG_ ## _level_(_log_, #_level_ " log test") == (_log_.IsActive() && (engine::CLog::s_logLevel >= engine::CLog::eLL_ ## _level_))), "Should not have logged at " #_level_ " log level", _stage_type_)

namespace test
{
	//============================================================================

	CLogTest::CLogTest(void)
		: CUnitTest("Log Variable")
	{
		Initialise();
	}

	//============================================================================

	CLogTest::~CLogTest(void)
	{
		Uninitialise();
	}

	//============================================================================

	bool CLogTest::Initialise(void)
	{
		AddStage("Default log", DefaultLog);
		AddStage("Custom log", CustomLog);

		return CUnitTest::Initialise();
	}

	//============================================================================

	uint32 CLogTest::DefaultLog(CUnitTest* pParent)
	{
		CLogTest* pThis = static_cast<CLogTest*>(pParent);
		uint32 status = eSS_PASS;
		ENGINE_LOGGER.SetFlags(ENGINE_LOGGER.GetFlags() & ~(engine::CLog::eBT_CONSOLE | engine::CLog::eBT_FILE | engine::CLog::eBT_STANDARD));
#if defined(DEBUG)
		int64 oldLogLevel = engine::CLog::s_logLevel;
#endif // defined(DEBUG)

		if (pThis->m_testStatus == eTS_RUNNING)
		{
			switch (pThis->GetStage())
			{
				case 1:
					LOG_TEST(ENGINE_LOGGER, DEBUG, eTT_SubStage);
					LOG_TEST(ENGINE_LOGGER, INFO, eTT_SubStage);
					LOG_TEST(ENGINE_LOGGER, WARNING, eTT_SubStage);
					LOG_TEST(ENGINE_LOGGER, ERROR, eTT_SubStage);
					LOG_TEST(ENGINE_LOGGER, FATAL, eTT_SubStage);
					LOG_TEST(ENGINE_LOGGER, ALWAYS, eTT_Stage);
					break;

				case 2:
					ENGINE_LOGGER.SetActive(false);
					LOG_TEST(ENGINE_LOGGER, DEBUG, eTT_SubStage);
					LOG_TEST(ENGINE_LOGGER, INFO, eTT_SubStage);
					LOG_TEST(ENGINE_LOGGER, WARNING, eTT_SubStage);
					LOG_TEST(ENGINE_LOGGER, ERROR, eTT_SubStage);
					LOG_TEST(ENGINE_LOGGER, FATAL, eTT_SubStage);
					LOG_TEST(ENGINE_LOGGER, ALWAYS, eTT_Stage);
					ENGINE_LOGGER.SetActive(true);
					break;

#if defined(DEBUG)
				// If we're in debug, we can alter the log level and retest to make sure
				// all log levels are correctly elided
				case 3:
					engine::CLog::s_logLevel = engine::CLog::eLL_DEBUG;
					LOG_TEST(ENGINE_LOGGER, DEBUG, eTT_SubStage);
					LOG_TEST(ENGINE_LOGGER, INFO, eTT_SubStage);
					LOG_TEST(ENGINE_LOGGER, WARNING, eTT_SubStage);
					LOG_TEST(ENGINE_LOGGER, ERROR, eTT_SubStage);
					LOG_TEST(ENGINE_LOGGER, FATAL, eTT_SubStage);
					LOG_TEST(ENGINE_LOGGER, ALWAYS, eTT_Stage);
					engine::CLog::s_logLevel = oldLogLevel;
					break;

				case 4:
					engine::CLog::s_logLevel = engine::CLog::eLL_INFO;
					LOG_TEST(ENGINE_LOGGER, DEBUG, eTT_SubStage);
					LOG_TEST(ENGINE_LOGGER, INFO, eTT_SubStage);
					LOG_TEST(ENGINE_LOGGER, WARNING, eTT_SubStage);
					LOG_TEST(ENGINE_LOGGER, ERROR, eTT_SubStage);
					LOG_TEST(ENGINE_LOGGER, FATAL, eTT_SubStage);
					LOG_TEST(ENGINE_LOGGER, ALWAYS, eTT_Stage);
					engine::CLog::s_logLevel = oldLogLevel;
					break;

				case 5:
					engine::CLog::s_logLevel = engine::CLog::eLL_WARNING;
					LOG_TEST(ENGINE_LOGGER, DEBUG, eTT_SubStage);
					LOG_TEST(ENGINE_LOGGER, INFO, eTT_SubStage);
					LOG_TEST(ENGINE_LOGGER, WARNING, eTT_SubStage);
					LOG_TEST(ENGINE_LOGGER, ERROR, eTT_SubStage);
					LOG_TEST(ENGINE_LOGGER, FATAL, eTT_SubStage);
					LOG_TEST(ENGINE_LOGGER, ALWAYS, eTT_Stage);
					engine::CLog::s_logLevel = oldLogLevel;
					break;

				case 6:
					engine::CLog::s_logLevel = engine::CLog::eLL_ERROR;
					LOG_TEST(ENGINE_LOGGER, DEBUG, eTT_SubStage);
					LOG_TEST(ENGINE_LOGGER, INFO, eTT_SubStage);
					LOG_TEST(ENGINE_LOGGER, WARNING, eTT_SubStage);
					LOG_TEST(ENGINE_LOGGER, ERROR, eTT_SubStage);
					LOG_TEST(ENGINE_LOGGER, FATAL, eTT_SubStage);
					LOG_TEST(ENGINE_LOGGER, ALWAYS, eTT_Stage);
					engine::CLog::s_logLevel = oldLogLevel;
					break;

				case 7:
					engine::CLog::s_logLevel = engine::CLog::eLL_FATAL;
					LOG_TEST(ENGINE_LOGGER, DEBUG, eTT_SubStage);
					LOG_TEST(ENGINE_LOGGER, INFO, eTT_SubStage);
					LOG_TEST(ENGINE_LOGGER, WARNING, eTT_SubStage);
					LOG_TEST(ENGINE_LOGGER, ERROR, eTT_SubStage);
					LOG_TEST(ENGINE_LOGGER, FATAL, eTT_SubStage);
					LOG_TEST(ENGINE_LOGGER, ALWAYS, eTT_Stage);
					engine::CLog::s_logLevel = oldLogLevel;
					break;

				case 8:
					engine::CLog::s_logLevel = engine::CLog::eLL_ALWAYS;
					LOG_TEST(ENGINE_LOGGER, DEBUG, eTT_SubStage);
					LOG_TEST(ENGINE_LOGGER, INFO, eTT_SubStage);
					LOG_TEST(ENGINE_LOGGER, WARNING, eTT_SubStage);
					LOG_TEST(ENGINE_LOGGER, ERROR, eTT_SubStage);
					LOG_TEST(ENGINE_LOGGER, FATAL, eTT_SubStage);
					LOG_TEST(ENGINE_LOGGER, ALWAYS, eTT_Stage);
					engine::CLog::s_logLevel = oldLogLevel;
					break;
#endif // defined(DEBUG)

				default:
					status |= eSS_COMPLETE;
					break;
			}
		}

		ENGINE_LOGGER.SetFlags(ENGINE_LOGGER.GetFlags() | (engine::CLog::eBT_CONSOLE | engine::CLog::eBT_FILE | engine::CLog::eBT_STANDARD));
		return status;
	}

	//============================================================================

	uint32 CLogTest::CustomLog(CUnitTest* pParent)
	{
		CLogTest* pThis = static_cast<CLogTest*>(pParent);
		uint32 status = eSS_PASS;

		if (pThis->m_testStatus == eTS_RUNNING)
		{
			switch (pThis->GetStage())
			{
//				case 1:
//					{
//						int64 initialValue = rand();
//						m_pCVar = REGISTER_VARIABLE(testIntegerVariable, initialValue, 0, NULL, "A test variable");
//						pThis->Test("Setting initial value of integer cvar", m_pCVar->GetInteger() == initialValue, "Initial value is not set correctly");
//					}
//					break;

				default:
//					UNREGISTER_VARIABLE_BY_POINTER(m_pCVar);
					status |= eSS_COMPLETE;
					break;
			}
		}

		return status;
	}

	//============================================================================
} // End [namespace test]

//==============================================================================
// [EOF]


