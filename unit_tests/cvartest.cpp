#include "common/stdafx.h"

#include "cvartest.h"


namespace test
{
	static int64 testIntegerVariable = 0;

	//============================================================================

	engine::CConsole::TIVariablePtr CCVarTest::m_pCVar;

	//============================================================================

	CCVarTest::CCVarTest(void)
		: CUnitTest("Console Variable")
	{
		Initialise();
	}

	//============================================================================

	CCVarTest::~CCVarTest(void)
	{
		Uninitialise();
	}

	//============================================================================

	bool CCVarTest::Initialise(void)
	{
		AddStage("Lifecycle", ConsoleVariableLifecycle, eTV_INFORMATION);
		AddStage("Operations", GenericVariableOperations, eTV_INFORMATION);
/*		AddStage("Integer console variable operations", IntegerVariableOperations);
		AddStage("Floating point console variable operations", FloatVariableOperations);
		AddStage("String console variable operations", StringVariableOperations);
*/
		return CUnitTest::Initialise();
	}

	//============================================================================

	uint32 CCVarTest::ConsoleVariableLifecycle(CUnitTest* pParent)
	{
		CCVarTest* pThis = static_cast<CCVarTest*>(pParent);
		uint32 status = eSS_SUCCESS;

		if (pThis->m_testStatus == eTS_RUNNING)
		{
			switch (pThis->GetStage())
			{
				case 1:
					m_pCVar = REGISTER_VARIABLE(testIntegerVariable, NULL, "A test variable");
					pThis->Log((m_pCVar != NULL) ? eTV_RESULT : eTV_ERROR, "Created console variable at address %p", m_pCVar.get());
					pThis->NextStage();

				case 2:
					UNREGISTER_VARIABLE(testIntegerVariable);
					pThis->Log(eTV_RESULT, "Released console variable at address %p", m_pCVar.get());
					m_pCVar.reset();
					pThis->NextStage();

				default:
					status |= eSS_COMPLETE;
					break;
			}
		}

		return status;
	}

	//============================================================================

	uint32 CCVarTest::GenericVariableOperations(CUnitTest* pParent)
	{
		CCVarTest* pThis = static_cast<CCVarTest*>(pParent);
		uint32 status = eSS_SUCCESS;

		if (pThis->m_testStatus == eTS_RUNNING)
		{
			switch (pThis->GetStage())
			{
				case 1:
					m_pCVar = engine::CConsole::Get().RegisterVariable(engine::CRunTimeStringHash::Calculate("testIntegerVariable"), testIntegerVariable);
					pThis->Log((m_pCVar != NULL) ? eTV_RESULT : eTV_ERROR, "Created console variable at address %p", m_pCVar.get());
					pThis->NextStage();

				case 2:
					engine::CConsole::Get().UnregisterVariable(engine::CRunTimeStringHash::Calculate("testIntegerVariable"));
					pThis->Log(eTV_RESULT, "Released console variable at address %p", m_pCVar.get());
					m_pCVar.reset();
					pThis->NextStage();

				default:
					status |= eSS_COMPLETE;
					break;
			}
		}

		return status;
	}

	//============================================================================

	uint32 CCVarTest::IntegerVariableOperations(CUnitTest* pParent)
	{
		CCVarTest* pThis = static_cast<CCVarTest*>(pParent);
		uint32 status = eSS_SUCCESS;

		if (pThis->m_testStatus == eTS_RUNNING)
		{
			switch (pThis->GetStage())
			{
				/*
				case 1: // Minimum negative time
					{
						CTimeValue testValue(DECLARE_64BIT(0x8000000000000001));
						testValue.GetTime(days, hours, minutes, seconds);

						pThis->Log(eTV_RESULT, "Minimum negative time value is %s%d days, %02u:%02u:%06.3fs", (testValue.GetTicks() < 0) ? "-" : "+",  days, hours, minutes, seconds);

						pThis->NextStage();
					}
					break;

				case 2: // Maximum positive time
					{
						CTimeValue testValue(DECLARE_64BIT(0x7fffffffffffffff));
						testValue.GetTime(days, hours, minutes, seconds);

						pThis->Log(eTV_RESULT, "Maximum positive time value is %s%d days, %02u:%02u:%06.3fs", (testValue.GetTicks() < 0) ? "-" : "+",  days, hours, minutes, seconds);

						pThis->NextStage();
					}
					break;
					*/

				default:
					status |= eSS_COMPLETE;
					break;
			}
		}

		return status;
	}

	//============================================================================

	uint32 CCVarTest::FloatVariableOperations(CUnitTest* pParent)
	{
		CCVarTest* pThis = static_cast<CCVarTest*>(pParent);
		uint32 status = eSS_SUCCESS;

		if (pThis->m_testStatus == eTS_RUNNING)
		{
			switch (pThis->GetStage())
			{
				/*
				case 1: // Minimum negative time
					{
						CTimeValue testValue(DECLARE_64BIT(0x8000000000000001));
						testValue.GetTime(days, hours, minutes, seconds);

						pThis->Log(eTV_RESULT, "Minimum negative time value is %s%d days, %02u:%02u:%06.3fs", (testValue.GetTicks() < 0) ? "-" : "+",  days, hours, minutes, seconds);

						pThis->NextStage();
					}
					break;

				case 2: // Maximum positive time
					{
						CTimeValue testValue(DECLARE_64BIT(0x7fffffffffffffff));
						testValue.GetTime(days, hours, minutes, seconds);

						pThis->Log(eTV_RESULT, "Maximum positive time value is %s%d days, %02u:%02u:%06.3fs", (testValue.GetTicks() < 0) ? "-" : "+",  days, hours, minutes, seconds);

						pThis->NextStage();
					}
					break;
					*/

				default:
					status |= eSS_COMPLETE;
					break;
			}
		}

		return status;
	}

	//============================================================================

	uint32 CCVarTest::StringVariableOperations(CUnitTest* pParent)
	{
		CCVarTest* pThis = static_cast<CCVarTest*>(pParent);
		uint32 status = eSS_SUCCESS;

		if (pThis->m_testStatus == eTS_RUNNING)
		{
			switch (pThis->GetStage())
			{
				/*
				case 1: // Minimum negative time
					{
						CTimeValue testValue(DECLARE_64BIT(0x8000000000000001));
						testValue.GetTime(days, hours, minutes, seconds);

						pThis->Log(eTV_RESULT, "Minimum negative time value is %s%d days, %02u:%02u:%06.3fs", (testValue.GetTicks() < 0) ? "-" : "+",  days, hours, minutes, seconds);

						pThis->NextStage();
					}
					break;

				case 2: // Maximum positive time
					{
						CTimeValue testValue(DECLARE_64BIT(0x7fffffffffffffff));
						testValue.GetTime(days, hours, minutes, seconds);

						pThis->Log(eTV_RESULT, "Maximum positive time value is %s%d days, %02u:%02u:%06.3fs", (testValue.GetTicks() < 0) ? "-" : "+",  days, hours, minutes, seconds);

						pThis->NextStage();
					}
					break;
					*/

				default:
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

