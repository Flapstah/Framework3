#include "common/stdafx.h"

#include "cvartest.h"


namespace test
{
	static int64 testIntegerVariable = 0;
	static double testDoubleVariable = 0.0;
	static std::string testString = "";

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
		AddStage("Lifecycle", ConsoleVariableLifecycle, eTV_TERSE);
		AddStage("Integer console variable operations", IntegerVariableOperations, eTV_TERSE);
		AddStage("Integer constant console variable operations", IntegerConstantVariableOperations, eTV_TERSE);
/*		AddStage("Floating point console variable operations", FloatVariableOperations, eTV_VERBOSE);
		AddStage("Floating point constant console variable operations", FloatVariableOperations, eTV_VERBOSE);
		AddStage("String console variable operations", StringVariableOperations, eTV_VERBOSE);
		AddStage("String constant console variable operations", StringVariableOperations, eTV_VERBOSE);
*/
		return CUnitTest::Initialise();
	}

	//============================================================================

	uint32 CCVarTest::ConsoleVariableLifecycle(CUnitTest* pParent)
	{
		char buffer[64];
		CCVarTest* pThis = static_cast<CCVarTest*>(pParent);
		uint32 status = eSS_PASS;

		if (pThis->m_testStatus == eTS_RUNNING)
		{
			switch (pThis->GetStage())
			{
				case 1:
					m_pCVar = REGISTER_VARIABLE(testIntegerVariable, 1, 0, NULL, "A test variable");
					sprintf(buffer, "%p", m_pCVar.get());
					TEST_INFORMATION("Created console variable at address", buffer);
					pThis->NextStage();

				case 2:
					UNREGISTER_VARIABLE(testIntegerVariable);
					sprintf(buffer, "%p", m_pCVar.get());
					TEST_INFORMATION("Released console variable at address", buffer);
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
		char buffer[64];
		CCVarTest* pThis = static_cast<CCVarTest*>(pParent);
		uint32 status = eSS_PASS;

		if (pThis->m_testStatus == eTS_RUNNING)
		{
			switch (pThis->GetStage())
			{
				case 1:
					{
						int64 initialValue = rand();
						m_pCVar = REGISTER_VARIABLE(testIntegerVariable, initialValue, 0, NULL, "A test variable");
						sprintf(buffer, "%p", m_pCVar.get());
						TEST_INFORMATION("Created console variable at address", buffer);
						TEST1_NAMED("Initial value", m_pCVar->GetInteger() == initialValue, m_pCVar->GetInteger(), initialValue); 
						pThis->NextStage();
					}
					break;

				case 2:
					{
						int64 value = rand();
						m_pCVar->SetInteger(value);
						TEST1_NAMED("Set integer value", m_pCVar->GetInteger() == value, m_pCVar->GetInteger(), value); 
						pThis->NextStage();
					}
					break;

				case 3:
					{
						double value = static_cast<double>(rand())/RAND_MAX;
						m_pCVar->SetDouble(value);
						TEST1_NAMED("Set double value", pThis->IsEqual(m_pCVar->GetDouble(), value), m_pCVar->GetDouble(), value); 
						pThis->NextStage();
					}
					break;

				case 4:
					{
						const char* value = "3.1415926535897932384626433832795";
						m_pCVar->SetString(value);
						TEST1_NAMED_STRING("Set string value", strcmp(m_pCVar->GetString(), "3") == 0, m_pCVar->GetString(), m_pCVar->GetString()); 
						pThis->NextStage();
					}
					break;

				case 5:
					UNREGISTER_VARIABLE(testIntegerVariable);
					sprintf(buffer, "%p", m_pCVar.get());
					TEST_INFORMATION("Released console variable at address", buffer);
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

	uint32 CCVarTest::IntegerConstantVariableOperations(CUnitTest* pParent)
	{
		char buffer[64];
		CCVarTest* pThis = static_cast<CCVarTest*>(pParent);
		uint32 status = eSS_PASS;

		if (pThis->m_testStatus == eTS_RUNNING)
		{
			switch (pThis->GetStage())
			{
				case 1:
					{
						int64 initialValue = rand();
						m_pCVar = REGISTER_VARIABLE(testIntegerVariable, initialValue, engine::CConsole::IVariable::eF_CONST, NULL, "A test variable");
						sprintf(buffer, "%p", m_pCVar.get());
						TEST_INFORMATION("Created console variable at address", buffer);
						TEST1_NAMED("Initial value", m_pCVar->GetInteger() == initialValue, m_pCVar->GetInteger(), initialValue); 
						pThis->NextStage();
					}
					break;

				case 2:
					{
						int64 initialValue = m_pCVar->GetInteger();
						int64 value = rand();
						m_pCVar->SetInteger(value);
						TEST1_NAMED("Set integer value", m_pCVar->GetInteger() == initialValue, m_pCVar->GetInteger(), value); 
						pThis->NextStage();
					}
					break;

				case 3:
					{
						double initialValue = m_pCVar->GetDouble();
						double value = static_cast<double>(rand())/RAND_MAX;
						m_pCVar->SetDouble(value);
						TEST1_NAMED("Set double value", pThis->IsEqual(m_pCVar->GetDouble(), initialValue), m_pCVar->GetDouble(), value); 
						pThis->NextStage();
					}
					break;

				case 4:
					{
						const char* initialValue = m_pCVar->GetString();
						const char* value = "3.1415926535897932384626433832795";
						m_pCVar->SetString(value);
						TEST1_NAMED_STRING("Set string value", strcmp(m_pCVar->GetString(), initialValue) == 0, m_pCVar->GetString(), value); 
						pThis->NextStage();
					}
					break;

				case 5:
					UNREGISTER_VARIABLE(testIntegerVariable);
					sprintf(buffer, "%p", m_pCVar.get());
					TEST_INFORMATION("Released console variable at address", buffer);
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

	uint32 CCVarTest::FloatVariableOperations(CUnitTest* pParent)
	{
		CCVarTest* pThis = static_cast<CCVarTest*>(pParent);
		uint32 status = eSS_PASS;

		if (pThis->m_testStatus == eTS_RUNNING)
		{
			switch (pThis->GetStage())
			{
				default:
					status |= eSS_COMPLETE;
					break;
			}
		}

		return status;
	}

	//============================================================================

	uint32 CCVarTest::FloatConstantVariableOperations(CUnitTest* pParent)
	{
		CCVarTest* pThis = static_cast<CCVarTest*>(pParent);
		uint32 status = eSS_PASS;

		if (pThis->m_testStatus == eTS_RUNNING)
		{
			switch (pThis->GetStage())
			{
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
		uint32 status = eSS_PASS;

		if (pThis->m_testStatus == eTS_RUNNING)
		{
			switch (pThis->GetStage())
			{
				default:
					status |= eSS_COMPLETE;
					break;
			}
		}

		return status;
	}

	//============================================================================

	uint32 CCVarTest::StringConstantVariableOperations(CUnitTest* pParent)
	{
		CCVarTest* pThis = static_cast<CCVarTest*>(pParent);
		uint32 status = eSS_PASS;

		if (pThis->m_testStatus == eTS_RUNNING)
		{
			switch (pThis->GetStage())
			{
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

