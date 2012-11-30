#include "common/stdafx.h"

#include "timetest.h"

//==============================================================================
// Helper macros
//==============================================================================

// Essentially checks (_value1_) == (_value2_) in a safe way for floating point numbers
#define IS_FP_EQUIVALENT(_value1_, _value2_) (((_value1_) >= (_value2_)) && ((_value1_) <= (_value2_)))

#define OPERATION_1_PARAM_NAMED_TEST(_name_, _test_, _param_) \
	{ \
		bool success = (_test_); \
		pThis->Log((success == true) ? eTV_INFORMATION : eTV_WARNING, "[%d:%d] " _name_ " (%" PRId64 ") [%s]", pThis->m_stage, pThis->m_subStage, static_cast<int64>(_param_), ((success == true) ? "PASSED" : "FAILED")); \
	}

#define OPERATION_2_PARAM_TEST(_test_, _param1_, _param2_) \
	{ \
		bool success = (_test_); \
		pThis->Log((success == true) ? eTV_INFORMATION : eTV_WARNING, "[%d:%d] %s (%" PRId64 ", %" PRId64 ") [%s]", pThis->m_stage, pThis->m_subStage, #_test_, static_cast<int64>(_param1_), static_cast<int64>(_param2_), ((success == true) ? "PASSED" : "FAILED")); \
	}

namespace test
{
	//============================================================================

	CTimeTest::CTimeTest(void)
		: CUnitTest("Time")
	{
		Initialise(eTV_INFORMATION);
	}

	//============================================================================

	CTimeTest::~CTimeTest(void)
	{
		Uninitialise();
	}

	//============================================================================

	bool CTimeTest::Initialise(eTestVerbosity verbosity)
	{
		AddStage("CTimeValue Operations", TimeValueOperations);

		return CUnitTest::Initialise(verbosity);
	}

	//============================================================================

	/*
		 case 0: // Test getting interface pointer
		 {
		 ITime* pTime = GetITime();
		 if (pTime == pThis->m_pTime)
		 {
		 pThis->Log(eTV_INFORMATION, "Time interface obtained correctly (behaving as a singleton)");
		 }
		 else
		 {
		 pThis->Log(eTV_ERROR, "Time interface different! (Not behaving as a singleton)");
		 }

		 ++pThis->m_stage;
		 }
		 break;
		 */

	//============================================================================

	uint32 CTimeTest::TimeValueOperations(CUnitTest* pParent)
	{
		CTimeTest* pThis = static_cast<CTimeTest*>(pParent);
		uint32 status = eSS_SUCCESS;

		if (pThis->m_testStatus == eTS_RUNNING)
		{
			switch (pThis->m_stage)
			{
				case 0: // Constructors
					{
						// Test default constructor
						CTimeValue zeroTest;
						OPERATION_1_PARAM_NAMED_TEST("CTimeValue zeroTest", IS_FP_EQUIVALENT(zeroTest.GetSeconds(), 0.0), 0);

						// Test value constructor
						CTimeValue oneTest(1.0);
						OPERATION_1_PARAM_NAMED_TEST("CTimeValue oneTest", IS_FP_EQUIVALENT(oneTest.GetSeconds(), 1.0), oneTest.GetTicks());

						// Test copy constructor
						CTimeValue copyTest(oneTest);
						OPERATION_1_PARAM_NAMED_TEST("CTimeValue copyTest(oneTest)", IS_FP_EQUIVALENT(copyTest.GetSeconds(), oneTest.GetSeconds()), oneTest.GetTicks());

						++(pThis->m_stage);
					}
					break;

				case 1: // operator=
					{
						CTimeValue testValue;
						CTimeValue oneTest(1.0);

						// operator=(const CTimeValue& other)
						if ((testValue.GetSeconds() >= 0.0) && (testValue.GetSeconds() <= 0.0))
						{
							testValue = oneTest;
							if ((testValue.GetSeconds() >= 1.0) && (testValue.GetSeconds() <= 1.0))
							{
								pThis->Log(eTV_INFORMATION, "[1.0] operator=(const CTimeValue& other) set test value to 1.0s");
							}
							else
							{
								pThis->Log(eTV_WARNING, "[1.0] operator=(const CTimeValue& other) did not set test value to 1.0s (%g)!", testValue.GetSeconds());
							}
						}
						else
						{
							pThis->Log(eTV_WARNING, "[1.0] CTimeValue testValue; failed to initialise test value to 0.0s (%g)!", testValue.GetSeconds());
						}

						// operator=(double seconds)
						++(pThis->m_subStage);
						testValue = 2.0;
						if ((testValue.GetSeconds() >= 2.0) && (testValue.GetSeconds() <= 2.0))
						{
							pThis->Log(eTV_INFORMATION, "[1.1] operator=(2.0) set test value to 2.0s");
						}
						else
						{
							pThis->Log(eTV_WARNING, "[1.1] operator=(2.0) did not set test value to 2.0s (%g)!", testValue.GetSeconds());
						}

						// operator=(double seconds)
						++(pThis->m_subStage);
						testValue = -2.0;
						if ((testValue.GetSeconds() >= -2.0) && (testValue.GetSeconds() <= -2.0))
						{
							pThis->Log(eTV_INFORMATION, "[1.2] operator=(-2.0) set test value to -2.0s");
						}
						else
						{
							pThis->Log(eTV_WARNING, "[1.2] operator=(-2.0) did not set test value to -2.0s (%g)!", testValue.GetSeconds());
						}

						// operator=(int64 ticks)
						++(pThis->m_subStage);
						testValue = int64(0);
						if (testValue.GetTicks() == 0)
						{
							pThis->Log(eTV_INFORMATION, "[1.3] operator=(int64(0)) set test value to 0");
						}
						else
						{
							pThis->Log(eTV_WARNING, "[1.3] operator=(int64(0)) did not set test value to 0 (%" PRId64 ")!", testValue.GetTicks());
						}

						++(pThis->m_stage);
					}
					break;

				case 2: // operator+=
					{
						CTimeValue testValue(1.0);
						CTimeValue twoTest(2.0);

						// operator+=(const CTimeValue& other)
						if ((testValue.GetSeconds() >= 1.0) && (testValue.GetSeconds() <= 1.0))
						{
							testValue += twoTest;
							if ((testValue.GetSeconds() >= 3.0) && (testValue.GetSeconds() <= 3.0))
							{
								pThis->Log(eTV_INFORMATION, "[2.0] operator+=(const CTimeValue& other) set test value to 3.0s");
							}
							else
							{
								pThis->Log(eTV_WARNING, "[2.0] operator+=(const CTimeValue& other) did not set test value to 3.0s (%g)!", testValue.GetSeconds());
							}
						}
						else
						{
							pThis->Log(eTV_WARNING, "[2.0] CTimeValue testValue(1.0) failed to initialise test value to 1.0s (%g)!", testValue.GetSeconds());
						}

						// operator+=(double seconds)
						++(pThis->m_subStage);
						testValue += 2.0;
						if ((testValue.GetSeconds() >= 5.0) && (testValue.GetSeconds() <= 5.0))
						{
							pThis->Log(eTV_INFORMATION, "[2.1] operator+=(2.0) set test value to 5.0s");
						}
						else
						{
							pThis->Log(eTV_WARNING, "[2.1] operator+=(2.0) did not set test value to 5.0s (%g)!", testValue.GetSeconds());
						}

						// operator+=(double seconds)
						++(pThis->m_subStage);
						testValue += -3.0;
						if ((testValue.GetSeconds() >= 2.0) && (testValue.GetSeconds() <= 2.0))
						{
							pThis->Log(eTV_INFORMATION, "[2.2] operator+=(-3.0) set test value to 2.0s");
						}
						else
						{
							pThis->Log(eTV_WARNING, "[2.2] operator+=(-3.0) did not set test value to 2.0s (%g)!", testValue.GetSeconds());
						}

						// operator+=(int64 ticks)
						++(pThis->m_subStage);
						testValue += twoTest.GetTicks();
						if ((testValue.GetSeconds() >= 4.0) && (testValue.GetSeconds() <= 4.0))
						{
							pThis->Log(eTV_INFORMATION, "[2.3] operator+=(twoTest.GetTicks()) set test value to 4.0s");
						}
						else
						{
							pThis->Log(eTV_WARNING, "[2.3] operator+=(twoTest.GetTicks()) did not set test value to 4.0s (%g)!", testValue.GetSeconds());
						}

						++(pThis->m_stage);
					}
					break;

				case 3: // operator-=
					{
						CTimeValue testValue(1.0);
						CTimeValue twoTest(2.0);

						// operator-=(const CTimeValue& other)
						if ((testValue.GetSeconds() >= 1.0) && (testValue.GetSeconds() <= 1.0))
						{
							testValue -= twoTest;
							if ((testValue.GetSeconds() >= -1.0) && (testValue.GetSeconds() <= -1.0))
							{
								pThis->Log(eTV_INFORMATION, "[3.0] operator-=(const CTimeValue& other) set test value to -1.0s");
							}
							else
							{
								pThis->Log(eTV_WARNING, "[3.0] operator-=(const CTimeValue& other) did not set test value to -1.0s (%g)!", testValue.GetSeconds());
							}
						}
						else
						{
							pThis->Log(eTV_WARNING, "[3.0] Value constructor failed to initialise test value to 1.0s (%g)!", testValue.GetSeconds());
						}

						// operator-=(double seconds)
						++(pThis->m_subStage);
						testValue -= 2.0;
						if ((testValue.GetSeconds() >= -3.0) && (testValue.GetSeconds() <= -3.0))
						{
							pThis->Log(eTV_INFORMATION, "[3.1] operator-=(2.0) set test value to -3.0s");
						}
						else
						{
							pThis->Log(eTV_WARNING, "[3.1] operator-=(2.0) did not set test value to -3.0s (%g)!", testValue.GetSeconds());
						}

						// operator-=(double seconds)
						++(pThis->m_subStage);
						testValue -= -5.0;
						if ((testValue.GetSeconds() >= 2.0) && (testValue.GetSeconds() <= 2.0))
						{
							pThis->Log(eTV_INFORMATION, "[3.2] operator-=(-5.0) set test value to 2.0s");
						}
						else
						{
							pThis->Log(eTV_WARNING, "[3.2] operator-=(-5.0) did not set test value to 2.0s (%g)!", testValue.GetSeconds());
						}

						// operator-=(int64 ticks)
						++(pThis->m_subStage);
						testValue -= twoTest.GetTicks();
						if ((testValue.GetSeconds() >= 0.0) && (testValue.GetSeconds() <= 0.0))
						{
							pThis->Log(eTV_INFORMATION, "[3.3] operator-=(twoTest.GetTicks()) set test value to 0.0s");
						}
						else
						{
							pThis->Log(eTV_WARNING, "[3.3] operator-=(twoTest.GetTicks()) did not set test value to 0.0s (%g)!", testValue.GetSeconds());
						}

						++(pThis->m_stage);
					}
					break;

				case 4: // operator+
					{
						CTimeValue oneTest(1.0);
						CTimeValue twoTest(2.0);
						CTimeValue minusTwoTest(-2.0);

						// operator+(const CTimeValue& other)
						CTimeValue testValue = oneTest+twoTest;
						if ((testValue.GetSeconds() >= 3.0) && (testValue.GetSeconds() <= 3.0))
						{
							pThis->Log(eTV_INFORMATION, "[4.0] operator+(const CTimeValue& other) set test value to 3.0s");
						}
						else
						{
							pThis->Log(eTV_WARNING, "[4.0] operator+(const CTimeValue& other) did not set test value to 3.0s (%g)!", testValue.GetSeconds());
						}

						// operator+(const CTimeValue& other)
						++(pThis->m_subStage);
						testValue = oneTest+minusTwoTest;
						if ((testValue.GetSeconds() >= -1.0) && (testValue.GetSeconds() <= -1.0))
						{
							pThis->Log(eTV_INFORMATION, "[4.1] operator+(const CTimeValue& other) set test value to -1.0s");
						}
						else
						{
							pThis->Log(eTV_WARNING, "[4.1] operator+(const CTimeValue& other) did not set test value to -1.0s (%g)!", testValue.GetSeconds());
						}

						// operator+(double seconds)
						++(pThis->m_subStage);
						testValue = twoTest+3.0;
						if ((testValue.GetSeconds() >= 5.0) && (testValue.GetSeconds() <= 5.0))
						{
							pThis->Log(eTV_INFORMATION, "[4.2] operator+ set test value to 5.0s");
						}
						else
						{
							pThis->Log(eTV_WARNING, "[4.2] operator+ did not set test value to 5.0s (%g)!", testValue.GetSeconds());
						}

						// operator+(double seconds)
						++(pThis->m_subStage);
						testValue = twoTest+(-3.0);
						if ((testValue.GetSeconds() >= -1.0) && (testValue.GetSeconds() <= -1.0))
						{
							pThis->Log(eTV_INFORMATION, "[4.3] operator+ set test value to -1.0s");
						}
						else
						{
							pThis->Log(eTV_WARNING, "[4.3] operator+ did not set test value to -1.0s (%g)!", testValue.GetSeconds());
						}

						// operator+(int64 ticks)
						++(pThis->m_subStage);
						testValue = oneTest.GetTicks()+twoTest.GetTicks();
						if ((testValue.GetSeconds() >= 3.0) && (testValue.GetSeconds() <= 3.0))
						{
							pThis->Log(eTV_INFORMATION, "[4.4] operator+ set test value to 3.0s");
						}
						else
						{
							pThis->Log(eTV_WARNING, "[4.4] operator+ did not set test value to 3.0s (%g)!", testValue.GetSeconds());
						}

						// operator+(int64 ticks)
						++(pThis->m_subStage);
						testValue = oneTest.GetTicks()+minusTwoTest.GetTicks();
						if ((testValue.GetSeconds() >= -1.0) && (testValue.GetSeconds() <= -1.0))
						{
							pThis->Log(eTV_INFORMATION, "[4.5] operator+ set test value to -1.0s");
						}
						else
						{
							pThis->Log(eTV_WARNING, "[4.5] operator+ did not set test value to -1.0s (%g)!", testValue.GetSeconds());
						}

						++(pThis->m_stage);
					}
					break;

				case 5: // operator-
					{
						CTimeValue oneTest(1.0);
						CTimeValue twoTest(2.0);
						CTimeValue minusTwoTest(-2.0);

						// operator-(const CTimeValue& other)
						CTimeValue testValue = oneTest-twoTest;
						if ((testValue.GetSeconds() >= -1.0) && (testValue.GetSeconds() <= -1.0))
						{
							pThis->Log(eTV_INFORMATION, "[5.0] operator-(const CTimeValue& other) set test value to -1.0s");
						}
						else
						{
							pThis->Log(eTV_WARNING, "[5.0] operator-(const CTimeValue& other) did not set test value to -1.0s (%g)!", testValue.GetSeconds());
						}

						// operator-(const CTimeValue& other)
						++(pThis->m_subStage);
						testValue = oneTest-minusTwoTest;
						if ((testValue.GetSeconds() >= 3.0) && (testValue.GetSeconds() <= 3.0))
						{
							pThis->Log(eTV_INFORMATION, "[5.1] operator-(const CTimeValue& other) set test value to 3.0s");
						}
						else
						{
							pThis->Log(eTV_WARNING, "[5.1] operator-(const CTimeValue& other) did not set test value to 3.0s (%g)!", testValue.GetSeconds());
						}

						// operator-(double seconds)
						++(pThis->m_subStage);
						testValue = twoTest-1.0;
						if ((testValue.GetSeconds() >= 1.0) && (testValue.GetSeconds() <= 1.0))
						{
							pThis->Log(eTV_INFORMATION, "[5.2] operator- set test value to 1.0s");
						}
						else
						{
							pThis->Log(eTV_WARNING, "[5.2] operator- did not set test value to 1.0s (%g)!", testValue.GetSeconds());
						}

						// operator-(double seconds)
						++(pThis->m_subStage);
						testValue = twoTest-(-3.0);
						if ((testValue.GetSeconds() >= 5.0) && (testValue.GetSeconds() <= 5.0))
						{
							pThis->Log(eTV_INFORMATION, "[5.3] operator- set test value to 5.0s");
						}
						else
						{
							pThis->Log(eTV_WARNING, "[5.3] operator- did not set test value to 5.0s (%g)!", testValue.GetSeconds());
						}

						// operator-(int64 ticks)
						++(pThis->m_subStage);
						testValue = oneTest.GetTicks()-twoTest.GetTicks();
						if ((testValue.GetSeconds() >= -1.0) && (testValue.GetSeconds() <= -1.0))
						{
							pThis->Log(eTV_INFORMATION, "[5.4] operator- set test value to -1.0s");
						}
						else
						{
							pThis->Log(eTV_WARNING, "[5.4] operator- did not set test value to -1.0s (%g)!", testValue.GetSeconds());
						}

						// operator-(int64 ticks)
						++(pThis->m_subStage);
						testValue = oneTest.GetTicks()-minusTwoTest.GetTicks();
						if ((testValue.GetSeconds() >= 3.0) && (testValue.GetSeconds() <= 3.0))
						{
							pThis->Log(eTV_INFORMATION, "[5.5] operator- set test value to 3.0s");
						}
						else
						{
							pThis->Log(eTV_WARNING, "[5.5] operator- did not set test value to 3.0s (%g)!", testValue.GetSeconds());
						}

						++(pThis->m_stage);
					}
					break;

				case 6: // operator==
					{
						CTimeValue oneTest(1.0);
						CTimeValue testValue(1.0);

						if (testValue == oneTest)
						{
							pThis->Log(eTV_INFORMATION, "[6.0] operator==(const CTimeValue& other) values are equal");
						}
						else
						{
							pThis->Log(eTV_WARNING, "[6.0] operator==(const CTimeValue& other) values are not equal (%g, %g)", testValue.GetSeconds(), oneTest.GetSeconds());
						}

						++(pThis->m_subStage);
						if (testValue == 1.0)
						{
							pThis->Log(eTV_INFORMATION, "[6.1] operator==(1.0) values are equal");
						}
						else
						{
							pThis->Log(eTV_WARNING, "[6.1] operator==(1.0) values are not equal (%g)", testValue.GetSeconds());
						}

						++(pThis->m_subStage);
						if (testValue == oneTest.GetTicks())
						{
							pThis->Log(eTV_INFORMATION, "[6.2] operator==(oneTest.GetTicks()) values are equal");
						}
						else
						{
							pThis->Log(eTV_WARNING, "[6.2] operator==(oneTest.GetTicks()) values are not equal (%" PRId64 ", %" PRId64 ")", testValue.GetTicks(), oneTest.GetTicks());
						}

						++(pThis->m_stage);
					}
					break;

				case 7: // operator!=
					{
						CTimeValue oneTest(1.0);
						CTimeValue testValue(2.0);

						if (testValue != oneTest)
						{
							pThis->Log(eTV_INFORMATION, "[7.0] operator!=(const CTimeValue& other) values are not equal");
						}
						else
						{
							pThis->Log(eTV_WARNING, "[7.0] operator!=(const CTimeValue& other) values are equal (%g, %g)", testValue.GetSeconds(), oneTest.GetSeconds());
						}

						++(pThis->m_subStage);
						if (testValue != 1.0)
						{
							pThis->Log(eTV_INFORMATION, "[7.1] operator!=(1.0) values are not equal");
						}
						else
						{
							pThis->Log(eTV_WARNING, "[7.1] operator!=(1.0) values are equal (%g)", testValue.GetSeconds());
						}

						++(pThis->m_subStage);
						if (testValue != oneTest.GetTicks())
						{
							pThis->Log(eTV_INFORMATION, "[7.2] operator!=(oneTest.GetTicks()) values are not equal");
						}
						else
						{
							pThis->Log(eTV_WARNING, "[7.2] operator!=(oneTest.GetTicks()) values are equal (%" PRId64 ", %" PRId64 ")", testValue.GetTicks(), oneTest.GetTicks());
						}

						++(pThis->m_stage);
					}
					break;

				case 8: // operator<
					{
						CTimeValue oneTest(1.0);
						CTimeValue testValue(2.0);

						if (testValue < oneTest)
						{
							pThis->Log(eTV_WARNING, "[8.0] operator<(const CTimeValue& other) passed value is less than test value (%g, %g)", testValue.GetSeconds(), oneTest.GetSeconds());
						}
						else
						{
							pThis->Log(eTV_INFORMATION, "[8.0] operator<(const CTimeValue& other) passed value is not less than test value");
						}

						++(pThis->m_subStage);
						testValue = 1.0;
						if (testValue < oneTest)
						{
							pThis->Log(eTV_WARNING, "[8.1] operator<(const CTimeValue& other) passed value is less than test value (%g, %g)", testValue.GetSeconds(), oneTest.GetSeconds());
						}
						else
						{
							pThis->Log(eTV_INFORMATION, "[8.1] operator<(const CTimeValue& other) passed value is not less than test value");
						}

						++(pThis->m_subStage);
						testValue = 0.5;
						if (testValue < oneTest)
						{
							pThis->Log(eTV_INFORMATION, "[8.2] operator<(const CTimeValue& other) test value is less than passed value");
						}
						else
						{
							pThis->Log(eTV_WARNING, "[8.2] operator<(const CTimeValue& other) test value is not less than passed value (%g, %g)", testValue.GetSeconds(), oneTest.GetSeconds());
						}

						++(pThis->m_subStage);
						testValue = 2.0;
						if (testValue < 1.0)
						{
							pThis->Log(eTV_WARNING, "[8.3] operator<(1.0) passed value is less than test value (%g, %g)", testValue.GetSeconds(), oneTest.GetSeconds());
						}
						else
						{
							pThis->Log(eTV_INFORMATION, "[8.3] operator<(1.0) passed value is not less than test value");
						}

						++(pThis->m_subStage);
						testValue = 1.0;
						if (testValue < 1.0)
						{
							pThis->Log(eTV_WARNING, "[8.4] operator<(1.0) passed value is less than test value (%g, %g)", testValue.GetSeconds(), oneTest.GetSeconds());
						}
						else
						{
							pThis->Log(eTV_INFORMATION, "[8.4] operator<(1.0) passed value is not less than test value");
						}

						++(pThis->m_subStage);
						testValue = 0.5;
						if (testValue < 1.0)
						{
							pThis->Log(eTV_INFORMATION, "[8.5] operator<(1.0) test value is less than passed value");
						}
						else
						{
							pThis->Log(eTV_WARNING, "[8.5] operator<(1.0) test value is not less than passed value (%g, %g)", testValue.GetSeconds(), oneTest.GetSeconds());
						}

						++(pThis->m_subStage);
						testValue = 2.0;
						if (testValue < oneTest.GetTicks())
						{
							pThis->Log(eTV_WARNING, "[8.6] operator<(oneTest.GetTicks()) passed value is less than test value (%g, %g)", testValue.GetSeconds(), oneTest.GetSeconds());
						}
						else
						{
							pThis->Log(eTV_INFORMATION, "[8.6] operator<(oneTest.GetTicks()) passed value is not less than test value");
						}

						++(pThis->m_subStage);
						testValue = 1.0;
						if (testValue < oneTest.GetTicks())
						{
							pThis->Log(eTV_WARNING, "[8.7] operator<(oneTest.GetTicks()) passed value is less than test value (%g, %g)", testValue.GetSeconds(), oneTest.GetSeconds());
						}
						else
						{
							pThis->Log(eTV_INFORMATION, "[8.7] operator<(oneTest.GetTicks()) passed value is not less than test value");
						}

						++(pThis->m_subStage);
						testValue = 0.5;
						if (testValue < oneTest.GetTicks())
						{
							pThis->Log(eTV_INFORMATION, "[8.8] operator<(oneTest.GetTicks()) test value is less than passed value");
						}
						else
						{
							pThis->Log(eTV_WARNING, "[8.8] operator<(oneTest.GetTicks()) test value is not less than passed value (%g, %g)", testValue.GetSeconds(), oneTest.GetSeconds());
						}

						++(pThis->m_stage);
					}
					break;

				case 9: // operator<=
					{
						CTimeValue oneTest(1.0);
						CTimeValue testValue(2.0);

						if (testValue <= oneTest)
						{
							pThis->Log(eTV_WARNING, "[9.0] operator<=(const CTimeValue& other) passed value is less than or equal to test value (%g, %g)", testValue.GetSeconds(), oneTest.GetSeconds());
						}
						else
						{
							pThis->Log(eTV_INFORMATION, "[9.0] operator<=(const CTimeValue& other) passed value is not less than or equal to test value");
						}

						++(pThis->m_subStage);
						testValue = 1.0;
						if (testValue <= oneTest)
						{
							pThis->Log(eTV_INFORMATION, "[9.1] operator<=(const CTimeValue& other) passed value is less than or equal to test value");
						}
						else
						{
							pThis->Log(eTV_WARNING, "[9.1] operator<=(const CTimeValue& other) passed value is not less than or equal to test value (%g, %g)", testValue.GetSeconds(), oneTest.GetSeconds());
						}

						++(pThis->m_subStage);
						testValue = 0.5;
						if (testValue <= oneTest)
						{
							pThis->Log(eTV_INFORMATION, "[9.2] operator<=(const CTimeValue& other) test value is less than or equal to passed value");
						}
						else
						{
							pThis->Log(eTV_WARNING, "[9.2] operator<=(const CTimeValue& other) test value is not less than or equal to passed value (%g, %g)", testValue.GetSeconds(), oneTest.GetSeconds());
						}

						++(pThis->m_subStage);
						testValue = 2.0;
						if (testValue <= 1.0)
						{
							pThis->Log(eTV_WARNING, "[9.3] operator<=(1.0) passed value is less than or equal to test value (%g, %g)", testValue.GetSeconds(), oneTest.GetSeconds());
						}
						else
						{
							pThis->Log(eTV_INFORMATION, "[9.3] operator<=(1.0) passed value is not less than or equal to test value");
						}

						++(pThis->m_subStage);
						testValue = 1.0;
						if (testValue <= 1.0)
						{
							pThis->Log(eTV_INFORMATION, "[9.4] operator<=(1.0) passed value is less than or equal to test value");
						}
						else
						{
							pThis->Log(eTV_WARNING, "[9.4] operator<=(1.0) passed value is not less than or equal to test value (%g, %g)", testValue.GetSeconds(), oneTest.GetSeconds());
						}

						++(pThis->m_subStage);
						testValue = 0.5;
						if (testValue <= 1.0)
						{
							pThis->Log(eTV_INFORMATION, "[9.5] operator<=(1.0) test value is less than or equal to passed value");
						}
						else
						{
							pThis->Log(eTV_WARNING, "[9.5] operator<=(1.0) test value is not less than or equal to passed value (%g, %g)", testValue.GetSeconds(), oneTest.GetSeconds());
						}

						++(pThis->m_subStage);
						testValue = 2.0;
						if (testValue <= oneTest.GetTicks())
						{
							pThis->Log(eTV_WARNING, "[9.6] operator<=(oneTest.GetTicks()) passed value is less than or equal to test value (%g, %g)", testValue.GetSeconds(), oneTest.GetSeconds());
						}
						else
						{
							pThis->Log(eTV_INFORMATION, "[9.6] operator<=(oneTest.GetTicks()) passed value is not less than or equal to test value");
						}

						++(pThis->m_subStage);
						testValue = 1.0;
						if (testValue <= oneTest.GetTicks())
						{
							pThis->Log(eTV_INFORMATION, "[9.7] operator<=(oneTest.GetTicks()) passed value is less than or equal to test value");
						}
						else
						{
							pThis->Log(eTV_WARNING, "[9.7] operator<=(oneTest.GetTicks()) passed value is not less than or equal to test value (%g, %g)", testValue.GetSeconds(), oneTest.GetSeconds());
						}

						++(pThis->m_subStage);
						testValue = 0.5;
						if (testValue <= oneTest.GetTicks())
						{
							pThis->Log(eTV_INFORMATION, "[9.8] operator<=(oneTest.GetTicks()) test value is less than or equal to passed value");
						}
						else
						{
							pThis->Log(eTV_WARNING, "[9.8] operator<=(oneTest.GetTicks()) test value is not less than or equal to passed value (%g, %g)", testValue.GetSeconds(), oneTest.GetSeconds());
						}

						++(pThis->m_stage);
					}
					break;

				case 10: // operator>
					{
						CTimeValue oneTest(1.0);
						CTimeValue testValue(2.0);

						if (testValue > oneTest)
						{
							pThis->Log(eTV_INFORMATION, "[10.0] operator>(const CTimeValue& other) passed value is greater than test value");
						}
						else
						{
							pThis->Log(eTV_WARNING, "[10.0] operator>(const CTimeValue& other) passed value is not greater than test value (%g, %g)", testValue.GetSeconds(), oneTest.GetSeconds());
						}

						++(pThis->m_subStage);
						testValue = 1.0;
						if (testValue > oneTest)
						{
							pThis->Log(eTV_WARNING, "[10.1] operator>(const CTimeValue& other) passed value is greater than test value (%g, %g)", testValue.GetSeconds(), oneTest.GetSeconds());
						}
						else
						{
							pThis->Log(eTV_INFORMATION, "[10.1] operator>(const CTimeValue& other) passed value is not greater than test value");
						}

						++(pThis->m_subStage);
						testValue = 0.5;
						if (testValue > oneTest)
						{
							pThis->Log(eTV_WARNING, "[10.2] operator>(const CTimeValue& other) test value is greater than passed value (%g, %g)", testValue.GetSeconds(), oneTest.GetSeconds());
						}
						else
						{
							pThis->Log(eTV_INFORMATION, "[10.2] operator>(const CTimeValue& other) test value is not greater than passed value");
						}

						++(pThis->m_subStage);
						testValue = 2.0;
						if (testValue > 1.0)
						{
							pThis->Log(eTV_INFORMATION, "[10.3] operator>(1.0) passed value is greater than test value");
						}
						else
						{
							pThis->Log(eTV_WARNING, "[10.3] operator>(1.0) passed value is not greater than test value (%g, %g)", testValue.GetSeconds(), oneTest.GetSeconds());
						}

						++(pThis->m_subStage);
						testValue = 1.0;
						if (testValue > 1.0)
						{
							pThis->Log(eTV_WARNING, "[10.4] operator>(1.0) passed value is greater than test value (%g, %g)", testValue.GetSeconds(), oneTest.GetSeconds());
						}
						else
						{
							pThis->Log(eTV_INFORMATION, "[10.4] operator>(1.0) passed value is not greater than test value");
						}

						++(pThis->m_subStage);
						testValue = 0.5;
						if (testValue > 1.0)
						{
							pThis->Log(eTV_WARNING, "[10.5] operator>(1.0) test value is greater than passed value (%g, %g)", testValue.GetSeconds(), oneTest.GetSeconds());
						}
						else
						{
							pThis->Log(eTV_INFORMATION, "[10.5] operator>(1.0) test value is not greater than passed value");
						}

						++(pThis->m_subStage);
						testValue = 2.0;
						if (testValue > oneTest.GetTicks())
						{
							pThis->Log(eTV_INFORMATION, "[10.6] operator>(oneTest.GetTicks()) passed value is greater than test value");
						}
						else
						{
							pThis->Log(eTV_WARNING, "[10.6] operator>(oneTest.GetTicks()) passed value is not greater than test value (%g, %g)", testValue.GetSeconds(), oneTest.GetSeconds());
						}

						++(pThis->m_subStage);
						testValue = 1.0;
						if (testValue > oneTest.GetTicks())
						{
							pThis->Log(eTV_WARNING, "[10.7] operator>(oneTest.GetTicks()) passed value is greater than test value (%g, %g)", testValue.GetSeconds(), oneTest.GetSeconds());
						}
						else
						{
							pThis->Log(eTV_INFORMATION, "[10.7] operator>(oneTest.GetTicks()) passed value is not greater than test value");
						}

						++(pThis->m_subStage);
						testValue = 0.5;
						if (testValue > oneTest.GetTicks())
						{
							pThis->Log(eTV_WARNING, "[10.8] operator>(oneTest.GetTicks()) test value is greater than passed value (%g, %g)", testValue.GetSeconds(), oneTest.GetSeconds());
						}
						else
						{
							pThis->Log(eTV_INFORMATION, "[10.8] operator>(oneTest.GetTicks()) test value is not greater than passed value");
						}

						++(pThis->m_stage);
					}
					break;

				case 11: // operator>=
					{
						CTimeValue oneTest(1.0);
						CTimeValue testValue(2.0);

						if (testValue >= oneTest)
						{
							pThis->Log(eTV_INFORMATION, "[11.0] operator>=(const CTimeValue& other) passed value is greater than or equal to test value");
						}
						else
						{
							pThis->Log(eTV_WARNING, "[11.0] operator>=(const CTimeValue& other) passed value is not greater than or equal to test value (%g, %g)", testValue.GetSeconds(), oneTest.GetSeconds());
						}

						++(pThis->m_subStage);
						testValue = 1.0;
						if (testValue >= oneTest)
						{
							pThis->Log(eTV_INFORMATION, "[11.1] operator>=(const CTimeValue& other) passed value is greater than or equal to test value");
						}
						else
						{
							pThis->Log(eTV_WARNING, "[11.1] operator>=(const CTimeValue& other) passed value is not greater than or equal to test value (%g, %g)", testValue.GetSeconds(), oneTest.GetSeconds());
						}

						++(pThis->m_subStage);
						testValue = 0.5;
						if (testValue >= oneTest)
						{
							pThis->Log(eTV_WARNING, "[11.2] operator>=(const CTimeValue& other) test value is greater than or equal to passed value (%g, %g)", testValue.GetSeconds(), oneTest.GetSeconds());
						}
						else
						{
							pThis->Log(eTV_INFORMATION, "[11.2] operator>=(const CTimeValue& other) test value is not greater than or equal to passed value");
						}

						++(pThis->m_subStage);
						testValue = 2.0;
						if (testValue >= 1.0)
						{
							pThis->Log(eTV_INFORMATION, "[11.3] operator>=(1.0) passed value is greater than or equal to test value");
						}
						else
						{
							pThis->Log(eTV_WARNING, "[11.3] operator>=(1.0) passed value is not greater than or equal to test value (%g, %g)", testValue.GetSeconds(), oneTest.GetSeconds());
						}

						++(pThis->m_subStage);
						testValue = 1.0;
						if (testValue >= 1.0)
						{
							pThis->Log(eTV_INFORMATION, "[11.4] operator>=(1.0) passed value is greater than or equal to test value");
						}
						else
						{
							pThis->Log(eTV_WARNING, "[11.4] operator>=(1.0) passed value is not greater than or equal to test value (%g, %g)", testValue.GetSeconds(), oneTest.GetSeconds());
						}

						++(pThis->m_subStage);
						testValue = 0.5;
						if (testValue >= 1.0)
						{
							pThis->Log(eTV_WARNING, "[11.5] operator>=(1.0) test value is greater than or equal to passed value (%g, %g)", testValue.GetSeconds(), oneTest.GetSeconds());
						}
						else
						{
							pThis->Log(eTV_INFORMATION, "[11.5] operator>=(1.0) test value is not greater than or equal to passed value");
						}

						++(pThis->m_subStage);
						testValue = 2.0;
						if (testValue >= oneTest.GetTicks())
						{
							pThis->Log(eTV_INFORMATION, "[11.6] operator>=(oneTest.GetTicks()) passed value is greater than or equal to test value");
						}
						else
						{
							pThis->Log(eTV_WARNING, "[11.6] operator>=(oneTest.GetTicks()) passed value is not greater than or equal to test value (%g, %g)", testValue.GetSeconds(), oneTest.GetSeconds());
						}

						++(pThis->m_subStage);
						testValue = 1.0;
						if (testValue >= oneTest.GetTicks())
						{
							pThis->Log(eTV_INFORMATION, "[11.7] operator>=(oneTest.GetTicks()) passed value is greater than or equal to test value");
						}
						else
						{
							pThis->Log(eTV_WARNING, "[11.7] operator>=(oneTest.GetTicks()) passed value is not greater than or equal to test value (%g, %g)", testValue.GetSeconds(), oneTest.GetSeconds());
						}

						++(pThis->m_subStage);
						testValue = 0.5;
						if (testValue >= oneTest.GetTicks())
						{
							pThis->Log(eTV_WARNING, "[11.8] operator>=(oneTest.GetTicks()) test value is greater than or equal to passed value (%g, %g)", testValue.GetSeconds(), oneTest.GetSeconds());
						}
						else
						{
							pThis->Log(eTV_INFORMATION, "[11.8] operator>=(oneTest.GetTicks()) test value is not greater than or equal to passed value");
						}

						++(pThis->m_stage);
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

