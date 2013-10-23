#include "common/stdafx.h"

#include "cvartest.h"


namespace test
{
	static int64 testIntegerVariable = 0;
	static double testDoubleVariable = 0.0;
	static std::string testStringVariable = "";

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
		AddStage("Floating point console variable operations", FloatVariableOperations, eTV_TERSE);
		AddStage("Floating point constant console variable operations", FloatConstantVariableOperations, eTV_TERSE);
		AddStage("String console variable operations", StringVariableOperations, eTV_TERSE);
		AddStage("String constant console variable operations", StringConstantVariableOperations, eTV_TERSE);

		return CUnitTest::Initialise();
	}

	//============================================================================

	uint32 CCVarTest::ConsoleVariableLifecycle(CUnitTest* pParent)
	{
		CCVarTest* pThis = static_cast<CCVarTest*>(pParent);
		uint32 status = eSS_PASS;

		if (pThis->m_testStatus == eTS_RUNNING)
		{
			switch (pThis->GetStage())
			{
				case 1:
					m_pCVar = REGISTER_VARIABLE(testIntegerVariable, 1, 0, NULL, "A test variable");
					pThis->Test("Registering console variable", m_pCVar.get() != NULL, "CVar pointer is NULL");
					break;

				case 2:
					UNREGISTER_VARIABLE_BY_NAME(testIntegerVariable);
					m_pCVar.reset();
					pThis->Test("Unregistering console variable by name", m_pCVar.get() == NULL, "CVar pointer is not NULL");
					break;

				case 3:
					m_pCVar = REGISTER_VARIABLE(testDoubleVariable, 1, 0, NULL, "A test variable");
					pThis->Test("Registering console variable", m_pCVar.get() != NULL, "CVar pointer is NULL");
					break;

				case 4:
					UNREGISTER_VARIABLE_BY_POINTER(m_pCVar);
					pThis->Test("Unregistering console variable by pointer", m_pCVar.get() == NULL, "CVar pointer is not NULL");
					break;
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
		uint32 status = eSS_PASS;

		if (pThis->m_testStatus == eTS_RUNNING)
		{
			switch (pThis->GetStage())
			{
				case 1:
					{
						int64 initialValue = rand();
						m_pCVar = REGISTER_VARIABLE(testIntegerVariable, initialValue, 0, NULL, "A test variable");
						pThis->Test("Setting initial value of integer cvar", m_pCVar->GetInteger() == initialValue, "Initial value is not set correctly");
					}
					break;

				case 2:
					{
						int64 value = rand();
						m_pCVar->SetInteger(value);
						pThis->Test("Setting integer cvar with integer value", m_pCVar->GetInteger() == value, "Value is not set correctly");
					}
					break;

				case 3:
					{
						double value = static_cast<double>(rand());
						m_pCVar->SetDouble(value);
						pThis->Test("Setting integer cvar with double value", pThis->IsEqual(m_pCVar->GetDouble(), value), "Value is not set correctly");
					}
					break;

				case 4:
					{
						const char* value = "3.1415926535897931";
						m_pCVar->SetString(value);
						pThis->Test("Setting integer cvar with string value", strcmp(m_pCVar->GetString(), "3") == 0, "Value is not set correctly");
						UNREGISTER_VARIABLE_BY_POINTER(m_pCVar);
					}
					break;

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
						pThis->Test("Setting initial value of const integer cvar", m_pCVar->GetInteger() == initialValue, "Initial value is not set correctly");
					}
					break;

				case 2:
					{
						int64 initialValue = m_pCVar->GetInteger();
						int64 value = rand();
						m_pCVar->SetInteger(value);
						pThis->Test("Setting const integer cvar with integer value", m_pCVar->GetInteger() == initialValue, "Value has changed");
					}
					break;

				case 3:
					{
						double initialValue = m_pCVar->GetDouble();
						double value = static_cast<double>(rand()) / static_cast<double>(rand()+1);
						m_pCVar->SetDouble(value);
						pThis->Test("Setting const integer cvar with double value", pThis->IsEqual(m_pCVar->GetDouble(), initialValue), "Value has changed");
					}
					break;

				case 4:
					{
						const char* initialValue = m_pCVar->GetString();
						const char* value = "3.1415926535897931";
						m_pCVar->SetString(value);
						pThis->Test("Setting integer cvar with string value", strcmp(m_pCVar->GetString(), initialValue) == 0, "Value has changed");
						UNREGISTER_VARIABLE_BY_POINTER(m_pCVar);
						m_pCVar.reset();
					}
					break;

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
				case 1:
					{
						double initialValue = static_cast<double>(rand()) / static_cast<double>(rand()+1);
						m_pCVar = REGISTER_VARIABLE(testDoubleVariable, initialValue, 0, NULL, "A test variable");
						pThis->Test("Setting initial value of double cvar", pThis->IsEqual(m_pCVar->GetDouble(), initialValue), "Initial value is not set correctly");
					}
					break;

				case 2:
					{
						int64 value = rand();
						m_pCVar->SetInteger(value);
						pThis->Test("Setting double cvar with integer value", m_pCVar->GetInteger() == value, "Value is not set correctly");
					}
					break;

				case 3:
					{
						double value = static_cast<double>(rand()) / static_cast<double>(rand()+1);
						m_pCVar->SetDouble(value);
						pThis->Test("Setting double cvar with double value", pThis->IsEqual(m_pCVar->GetDouble(), value), "Value is not set correctly");
					}
					break;

				case 4:
					{
						const char* value = "3.1415926535897931";
						m_pCVar->SetString(value);
						pThis->Test("Setting double cvar with string value", strcmp(m_pCVar->GetString(), value) == 0, "Value is not set correctly");
						UNREGISTER_VARIABLE_BY_POINTER(m_pCVar);
						m_pCVar.reset();
					}
					break;

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
				case 1:
					{
						double initialValue = static_cast<double>(rand()) / static_cast<double>(rand()+1);
						m_pCVar = REGISTER_VARIABLE(testDoubleVariable, initialValue, engine::CConsole::IVariable::eF_CONST, NULL, "A test variable");
						pThis->Test("Setting initial value of const double cvar", pThis->IsEqual(m_pCVar->GetDouble(), initialValue), "Initial value is not set correctly");
					}
					break;

				case 2:
					{
						int64 initialValue = m_pCVar->GetInteger();
						int64 value = rand();
						m_pCVar->SetInteger(value);
						pThis->Test("Setting const double cvar with integer value", m_pCVar->GetInteger() == initialValue, "Value has changed");
					}
					break;

				case 3:
					{
						double initialValue = m_pCVar->GetDouble();
						double value = static_cast<double>(rand()) / static_cast<double>(rand()+1);
						m_pCVar->SetDouble(value);
						pThis->Test("Setting const double cvar with double value", pThis->IsEqual(m_pCVar->GetDouble(), initialValue), "Value has changed");
					}
					break;

				case 4:
					{
						const char* initialValue = m_pCVar->GetString();
						const char* value = "3.1415926535897931";
						m_pCVar->SetString(value);
						pThis->Test("Setting const double cvar with string value", strcmp(m_pCVar->GetString(), initialValue) == 0, "Value has changed");
						UNREGISTER_VARIABLE_BY_POINTER(m_pCVar);
						m_pCVar.reset();
					}
					break;

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
				case 1:
					{
						const char* initialValue = "A test value";
						m_pCVar = REGISTER_VARIABLE(testStringVariable, initialValue, 0, NULL, "A test variable");
						pThis->Test("Setting initial value of string cvar", strcmp(m_pCVar->GetString(), initialValue) == 0, "Initial value is not set correctly");
					}
					break;

				case 2:
					{
						int64 value = rand();
						m_pCVar->SetInteger(value);
						pThis->Test("Setting string cvar with integer value", m_pCVar->GetInteger() == value, "Value is not set correctly");
					}
					break;

				case 3:
					{
						double value = static_cast<double>(rand()) / static_cast<double>(rand()+1);
						m_pCVar->SetDouble(value);
						pThis->Test("Setting string cvar with double value", pThis->IsEqual(m_pCVar->GetDouble(), value), "Value is not set correctly");
					}
					break;

				case 4:
					{
						const char* value = "3.1415926535897931";
						m_pCVar->SetString(value);
						pThis->Test("Setting string cvar with string value", strcmp(m_pCVar->GetString(), value) == 0, "Value is not set correctly");
						UNREGISTER_VARIABLE_BY_POINTER(m_pCVar);
						m_pCVar.reset();
					}
					break;

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
				case 1:
					{
						const char* initialValue = "A test value";
						m_pCVar = REGISTER_VARIABLE(testStringVariable, initialValue, engine::CConsole::IVariable::eF_CONST, NULL, "A test variable");
						pThis->Test("Setting initial value of constant string cvar", strcmp(m_pCVar->GetString(), initialValue) == 0, "Initial value is not set correctly");
					}
					break;

				case 2:
					{
						int64 initialValue = m_pCVar->GetInteger();
						int64 value = rand();
						m_pCVar->SetInteger(value);
						pThis->Test("Setting const string cvar with integer value", m_pCVar->GetInteger() == initialValue, "Value has changed");
					}
					break;

				case 3:
					{
						double initialValue = m_pCVar->GetDouble();
						double value = static_cast<double>(rand()) / static_cast<double>(rand()+1);
						m_pCVar->SetDouble(value);
						pThis->Test("Setting const string cvar with double value", pThis->IsEqual(m_pCVar->GetDouble(), initialValue), "Value has changed");
					}
					break;

				case 4:
					{
						const char* initialValue = m_pCVar->GetString();
						const char* value = "3.1415926535897931";
						m_pCVar->SetString(value);
						pThis->Test("Setting const string cvar with string value", strcmp(m_pCVar->GetString(), initialValue) == 0, "Value has changed");
						UNREGISTER_VARIABLE_BY_POINTER(m_pCVar);
						m_pCVar.reset();
					}
					break;

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

