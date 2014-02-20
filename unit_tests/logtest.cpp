#include "common/stdafx.h"

#include "logtest.h"
#include "common/log.h"

#define TEST(_level_) pThis->Test(#_level_ " log test", LOG_ ## _level_(engine::CLog::s_logRoot, #_level_ " log test\n") == (engine::CLog::s_logLevel >= engine::CLog::eLL_ ## _level_), "Should not have logged at " #_level_ " log level")

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
		AddStage("Default log", DefaultLog, eTV_TERSE);
		AddStage("Custom log", CustomLog, eTV_TERSE);

		return CUnitTest::Initialise();
	}

	//============================================================================

	uint32 CLogTest::DefaultLog(CUnitTest* pParent)
	{
		CLogTest* pThis = static_cast<CLogTest*>(pParent);
		uint32 status = eSS_PASS;

		if (pThis->m_testStatus == eTS_RUNNING)
		{
			switch (pThis->GetStage())
			{
				case 1:
					TEST(DEBUG);
					break;

				case 2:
					TEST(INFO);
					break;

				case 3:
					TEST(WARNING);
					break;

				case 4:
					TEST(ERROR);
					break;

				case 5:
					TEST(FATAL);
					break;

				case 6:
					TEST(ALWAYS);
					break;

				default:
					status |= eSS_COMPLETE;
					break;
			}
		}

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


