#include "common/stdafx.h"

#include "timetest.h"

namespace test
{
	//============================================================================

	CTimeTest::CTimeTest(void)
		: CUnitTest("Time")
	{
		Initialise();
	}

	//============================================================================

	CTimeTest::~CTimeTest(void)
	{
		Uninitialise();
	}

	//============================================================================

	bool CTimeTest::Initialise(void)
	{
		AddStage("CTimeValue Limits", TimeValueLimits, eTV_RESULT);
		AddStage("CTimeValue Operations", TimeValueOperations, eTV_RESULT);

		return CUnitTest::Initialise();
	}

	//============================================================================

	uint32 CTimeTest::TimeValueLimits(CUnitTest* pParent)
	{
		CTimeTest* pThis = static_cast<CTimeTest*>(pParent);
		uint32 status = eSS_SUCCESS;

		if (pThis->m_testStatus == eTS_RUNNING)
		{
			int32 days, hours, minutes;
			float seconds;

			switch (pThis->GetStage())
			{
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

				default:
					status |= eSS_COMPLETE;
					break;
			}
		}

		return status;
	}

	//============================================================================

	uint32 CTimeTest::TimeValueOperations(CUnitTest* pParent)
	{
		CTimeTest* pThis = static_cast<CTimeTest*>(pParent);
		uint32 status = eSS_SUCCESS;

		if (pThis->m_testStatus == eTS_RUNNING)
		{
			switch (pThis->GetStage())
			{
				case 1: // Constructors
					{
						// Test default constructor
						CTimeValue zeroTest;
						TEST1_NAMED("CTimeValue zeroTest", pThis->IsEqual(zeroTest.GetSeconds(), 0.0), 0, zeroTest.GetSeconds());

						// Test value constructor
						CTimeValue oneTest(1.0);
						TEST1_NAMED("CTimeValue oneTest", pThis->IsEqual(oneTest.GetSeconds(), 1.0), 1.0, oneTest.GetSeconds());

						// Test copy constructor
						CTimeValue copyTest(oneTest);
						TEST1_NAMED("CTimeValue copyTest(oneTest)", pThis->IsEqual(copyTest.GetSeconds(), oneTest.GetSeconds()), oneTest.GetSeconds(), copyTest.GetSeconds());

						pThis->NextStage();
					}
					break;

				case 2: // operator=
					{
						CTimeValue testValue(99.0);
						CTimeValue oneTest(1.0);

						// operator=(const CTimeValue& other)
						testValue = oneTest;
						TEST1_NAMED("testValue.GetSeconds() == 1.0", pThis->IsEqual(testValue.GetSeconds(), 1.0), 1.0, testValue.GetSeconds());

						// operator=(double seconds)
						testValue = 2.0;
						TEST1_NAMED("testValue.GetSeconds() == 2.0", pThis->IsEqual(testValue.GetSeconds(), 2.0), 2.0, testValue.GetSeconds());

						// operator=(double seconds)
						testValue = -2.0;
						TEST1_NAMED("testValue.GetSeconds() == -2.0", pThis->IsEqual(testValue.GetSeconds(), -2.0), -2.0, testValue.GetSeconds());

						// operator=(int64 ticks)
						testValue = int64(0);
						TEST1_NAMED("testValue.GetTicks() == 0", testValue.GetTicks() == 0, 0, testValue.GetTicks());

						pThis->NextStage();
					}
					break;

				case 3: // operator+=
					{
						CTimeValue testValue(1.0);
						CTimeValue twoTest(2.0);

						// operator+=(const CTimeValue& other)
						CTimeValue oldValue(testValue);
						testValue += twoTest;
						TEST2_NAMED("(testValue += twoTest) == 3.0", pThis->IsEqual(testValue.GetSeconds(), 3.0), oldValue.GetSeconds(), twoTest.GetSeconds(), testValue.GetSeconds());

						// operator+=(double seconds)
						oldValue = testValue;
						testValue += 2.0;
						TEST2_NAMED("(testValue += 2.0) == 5.0", pThis->IsEqual(testValue.GetSeconds(), 5.0), oldValue.GetSeconds(), 2.0, testValue.GetSeconds());

						// operator+=(double seconds)
						oldValue = testValue;
						testValue += -3.0;
						TEST2_NAMED("(testValue += -3.0) == 2.0", pThis->IsEqual(testValue.GetSeconds(), 2.0), oldValue.GetSeconds(), -3.0, testValue.GetSeconds());

						// operator+=(int64 ticks)
						oldValue = testValue;
						testValue += twoTest.GetTicks();
						TEST2_NAMED("(testValue += twoTest.GetTicks()) == 4.0s", pThis->IsEqual(testValue.GetSeconds(), 4.0), oldValue.GetTicks(), twoTest.GetTicks(), testValue.GetTicks());

						pThis->NextStage();
					}
					break;

				case 4: // operator-=
					{
						CTimeValue testValue(1.0);
						CTimeValue twoTest(2.0);

						// operator-=(const CTimeValue& other)
						CTimeValue oldValue(testValue);
						testValue -= twoTest;
						TEST2_NAMED("(testValue -= twoTest) == -1.0", pThis->IsEqual(testValue.GetSeconds(), -1.0), oldValue.GetSeconds(), twoTest.GetSeconds(), testValue.GetSeconds());

						// operator-=(double seconds)
						oldValue = testValue;
						testValue -= 2.0;
						TEST2_NAMED("(testValue -= 2.0) == -3.0", pThis->IsEqual(testValue.GetSeconds(), -3.0), oldValue.GetSeconds(), -2.0, testValue.GetSeconds());

						// operator-=(double seconds)
						oldValue = testValue;
						testValue -= -5.0;
						TEST2_NAMED("(testValue -= -5.0) == 2.0", pThis->IsEqual(testValue.GetSeconds(), 2.0), oldValue.GetSeconds(), -5.0, testValue.GetSeconds());

						// operator-=(int64 ticks)
						oldValue = testValue;
						testValue -= twoTest.GetTicks();
						TEST2_NAMED("(testValue -= twoTest.GetTicks()) == 0.0s", pThis->IsEqual(testValue.GetSeconds(), 0.0), oldValue.GetTicks(), 0.0, testValue.GetTicks());

						pThis->NextStage();
					}
					break;

				case 5: // operator+
					{
						CTimeValue oneTest(1.0);
						CTimeValue twoTest(2.0);
						CTimeValue minusTwoTest(-2.0);

						// operator+(const CTimeValue& other)
						CTimeValue testValue = oneTest+twoTest;
						TEST2_NAMED("(testValue = oneTest+twoTest) == 3.0", pThis->IsEqual(testValue.GetSeconds(), 3.0), oneTest.GetSeconds(), twoTest.GetSeconds(), testValue.GetSeconds());

						// operator+(const CTimeValue& other)
						testValue = oneTest+minusTwoTest;
						TEST2_NAMED("(testValue = oneTest+minusTwoTest) == -1.0", pThis->IsEqual(testValue.GetSeconds(), -1.0), oneTest.GetSeconds(), minusTwoTest.GetSeconds(), testValue.GetSeconds());

						// operator+(double seconds)
						testValue = twoTest+3.0;
						TEST2_NAMED("(testValue = twoTest+3.0) == 5.0", pThis->IsEqual(testValue.GetSeconds(), 5.0), twoTest.GetSeconds(), 3.0, testValue.GetSeconds());

						// operator+(double seconds)
						testValue = twoTest+(-3.0);
						TEST2_NAMED("(testValue = twoTest+(-3.0)) == -1.0", pThis->IsEqual(testValue.GetSeconds(), -1.0), twoTest.GetSeconds(), -3.0, testValue.GetSeconds());

						// operator+(int64 ticks)
						testValue = oneTest.GetTicks()+twoTest.GetTicks();
						TEST2_NAMED("(testValue = oneTest.GetTicks()+twoTest.GetTicks()) == 3.0s", pThis->IsEqual(testValue.GetSeconds(), 3.0), oneTest.GetTicks(), twoTest.GetTicks(), testValue.GetSeconds());

						// operator+(int64 ticks)
						testValue = oneTest.GetTicks()+minusTwoTest.GetTicks();
						TEST2_NAMED("(testValue = oneTest.GetTicks()+minusTwoTest.GetTicks()) == -1.0s", pThis->IsEqual(testValue.GetSeconds(), -1.0), oneTest.GetTicks(), minusTwoTest.GetTicks(), testValue.GetSeconds());

						pThis->NextStage();
					}
					break;

				case 6: // operator-
					{
						CTimeValue oneTest(1.0);
						CTimeValue twoTest(2.0);
						CTimeValue minusTwoTest(-2.0);

						// operator-(const CTimeValue& other)
						CTimeValue testValue = oneTest-twoTest;
						TEST2_NAMED("(testValue = oneTest-twoTest) == -1.0", pThis->IsEqual(testValue.GetSeconds(), -1.0), oneTest.GetSeconds(), twoTest.GetSeconds(), testValue.GetSeconds());

						// operator-(const CTimeValue& other)
						testValue = oneTest-minusTwoTest;
						TEST2_NAMED("(testValue = oneTest-minusTwoTest) == 3.0", pThis->IsEqual(testValue.GetSeconds(), 3.0), oneTest.GetSeconds(), minusTwoTest.GetSeconds(), testValue.GetSeconds());

						// operator-(double seconds)
						testValue = twoTest-1.0;
						TEST2_NAMED("(testValue = twoTest-1.0) == 1.0", pThis->IsEqual(testValue.GetSeconds(), 1.0), twoTest.GetSeconds(), 1.0, testValue.GetSeconds());

						// operator-(double seconds)
						testValue = twoTest-(-3.0);
						TEST2_NAMED("(testValue = twoTest-(-3.0)) == 5.0", pThis->IsEqual(testValue.GetSeconds(), 5.0), twoTest.GetSeconds(), 5.0, testValue.GetSeconds());

						// operator-(int64 ticks)
						testValue = oneTest.GetTicks()-twoTest.GetTicks();
						TEST2_NAMED("(oneTest.GetTicks()-twoTest.GetTicks()) == -1.0s", pThis->IsEqual(testValue.GetSeconds(), -1.0), oneTest.GetTicks(), twoTest.GetTicks(), testValue.GetTicks());

						// operator-(int64 ticks)
						testValue = oneTest.GetTicks()-minusTwoTest.GetTicks();
						TEST2_NAMED("(oneTest.GetTicks()-minusTwoTest.GetTicks()) == 3.0s", pThis->IsEqual(testValue.GetSeconds(), 3.0), oneTest.GetTicks(), minusTwoTest.GetTicks(), testValue.GetTicks());

						pThis->NextStage();
					}
					break;

				case 7: // operator==
					{
						CTimeValue oneTest(1.0);
						CTimeValue testValue(1.0);

						TEST1_NAMED("testValue == oneTest", testValue == oneTest, oneTest.GetSeconds(), testValue.GetSeconds());

						TEST1_NAMED("testValue == 1.0", testValue == 1.0, 1.0, testValue.GetSeconds());

						TEST1_NAMED("testValue == oneTest.GetTicks()", testValue == oneTest.GetTicks(), oneTest.GetTicks(), testValue.GetTicks());

						pThis->NextStage();
					}
					break;

				case 8: // operator!=
					{
						CTimeValue oneTest(1.0);
						CTimeValue testValue(2.0);

						TEST1_NAMED("testValue != oneTest", testValue != oneTest, oneTest.GetSeconds(), testValue.GetSeconds());

						TEST1_NAMED("testValue != 1.0", testValue != 1.0, 1.0, testValue.GetSeconds());

						TEST1_NAMED("testValue != oneTest.GetTicks()", testValue != oneTest.GetTicks(), oneTest.GetTicks(), testValue.GetTicks());

						pThis->NextStage();
					}
					break;

				case 9: // operator<
					{
						CTimeValue oneTest(1.0);
						CTimeValue testValue(2.0);

						TEST1_NAMED("!(testValue < oneTest)", !(testValue < oneTest), oneTest.GetSeconds(), testValue.GetSeconds());

						testValue = 1.0;
						TEST1_NAMED("!(testValue < oneTest)", !(testValue < oneTest), oneTest.GetSeconds(), testValue.GetSeconds());

						testValue = 0.5;
						TEST1_NAMED("testValue < oneTest", testValue < oneTest, oneTest.GetSeconds(), testValue.GetSeconds());

						testValue = 2.0;
						TEST1_NAMED("!(testValue < 1.0)", !(testValue < 1.0), 1.0, testValue.GetSeconds());

						testValue = 1.0;
						TEST1_NAMED("!(testValue < 1.0)", !(testValue < 1.0), 1.0, testValue.GetSeconds());

						testValue = 0.5;
						TEST1_NAMED("testValue < 1.0", testValue < 1.0, 1.0, testValue.GetSeconds());

						testValue = 2.0;
						TEST1_NAMED("!(testValue < oneTest.GetTicks())", !(testValue < oneTest.GetTicks()), oneTest.GetTicks(), testValue.GetTicks());

						testValue = 1.0;
						TEST1_NAMED("!(testValue < oneTest.GetTicks())", !(testValue < oneTest.GetTicks()), oneTest.GetTicks(), testValue.GetTicks());

						testValue = 0.5;
						TEST1_NAMED("testValue < oneTest.GetTicks()", testValue < oneTest.GetTicks(), oneTest.GetTicks(), testValue.GetTicks());

						pThis->NextStage();
					}
					break;

				case 10: // operator<=
					{
						CTimeValue oneTest(1.0);
						CTimeValue testValue(2.0);

						TEST1_NAMED("!(testValue <= oneTest)", !(testValue <= oneTest), oneTest.GetSeconds(), testValue.GetSeconds());

						testValue = 1.0;
						TEST1_NAMED("testValue <= oneTest", testValue <= oneTest, oneTest.GetSeconds(), testValue.GetSeconds());

						testValue = 0.5;
						TEST1_NAMED("testValue <= oneTest", testValue <= oneTest, oneTest.GetSeconds(), testValue.GetSeconds());

						testValue = 2.0;
						TEST1_NAMED("!(testValue <= 1.0)", !(testValue <= 1.0), 1.0, testValue.GetSeconds());

						testValue = 1.0;
						TEST1_NAMED("testValue <= 1.0", testValue <= 1.0, 1.0, testValue.GetSeconds());

						testValue = 0.5;
						TEST1_NAMED("testValue <= 1.0", testValue <= 1.0, 1.0, testValue.GetSeconds());

						testValue = 2.0;
						TEST1_NAMED("!(testValue <= oneTest.GetTicks())", !(testValue <= oneTest.GetTicks()), oneTest.GetTicks(), testValue.GetTicks());

						testValue = 1.0;
						TEST1_NAMED("testValue <= oneTest.GetTicks()", testValue <= oneTest.GetTicks(), oneTest.GetTicks(), testValue.GetTicks());

						testValue = 0.5;
						TEST1_NAMED("testValue <= oneTest.GetTicks()", testValue <= oneTest.GetTicks(), oneTest.GetTicks(), testValue.GetTicks());

						pThis->NextStage();
					}
					break;

				case 11: // operator>
					{
						CTimeValue oneTest(1.0);
						CTimeValue testValue(2.0);

						TEST1_NAMED("testValue > oneTest", testValue > oneTest, oneTest.GetSeconds(), testValue.GetSeconds());

						testValue = 1.0;
						TEST1_NAMED("!(testValue > oneTest)", !(testValue > oneTest), oneTest.GetSeconds(), testValue.GetSeconds());

						testValue = 0.5;
						TEST1_NAMED("!(testValue > oneTest)", !(testValue > oneTest), oneTest.GetSeconds(), testValue.GetSeconds());

						testValue = 2.0;
						TEST1_NAMED("testValue > 1.0", testValue > 1.0, 1.0, testValue.GetSeconds());

						testValue = 1.0;
						TEST1_NAMED("!(testValue > 1.0)", !(testValue > 1.0), 1.0, testValue.GetSeconds());

						testValue = 0.5;
						TEST1_NAMED("!(testValue > 1.0)", !(testValue > 1.0), 1.0, testValue.GetSeconds());

						testValue = 2.0;
						TEST1_NAMED("testValue > oneTest.GetTicks()", testValue > oneTest.GetTicks(), oneTest.GetTicks(), testValue.GetTicks());

						testValue = 1.0;
						TEST1_NAMED("!(testValue > oneTest.GetTicks())", !(testValue > oneTest.GetTicks()), oneTest.GetTicks(), testValue.GetTicks());

						testValue = 0.5;
						TEST1_NAMED("!(testValue > oneTest.GetTicks())", !(testValue > oneTest.GetTicks()), oneTest.GetTicks(), testValue.GetTicks());

						pThis->NextStage();
					}
					break;

				case 12: // operator>=
					{
						CTimeValue oneTest(1.0);
						CTimeValue testValue(2.0);

						TEST1_NAMED("testValue >= oneTest", testValue >= oneTest, oneTest.GetSeconds(), testValue.GetSeconds());

						testValue = 1.0;
						TEST1_NAMED("testValue >= oneTest", testValue >= oneTest, oneTest.GetSeconds(), testValue.GetSeconds());

						testValue = 0.5;
						TEST1_NAMED("!(testValue >= oneTest)", !(testValue >= oneTest), oneTest.GetSeconds(), testValue.GetSeconds());

						testValue = 2.0;
						TEST1_NAMED("testValue >= 1.0", testValue >= 1.0, 1.0, testValue.GetSeconds());

						testValue = 1.0;
						TEST1_NAMED("testValue >= 1.0", testValue >= 1.0, 1.0, testValue.GetSeconds());

						testValue = 0.5;
						TEST1_NAMED("!(testValue >= 1.0)", !(testValue >= 1.0), 1.0, testValue.GetSeconds());

						testValue = 2.0;
						TEST1_NAMED("testValue >= oneTest.GetTicks()", testValue >= oneTest.GetTicks(), oneTest.GetTicks(), testValue.GetTicks());

						testValue = 1.0;
						TEST1_NAMED("testValue >= oneTest.GetTicks()", testValue >= oneTest.GetTicks(), oneTest.GetTicks(), testValue.GetTicks());

						testValue = 0.5;
						TEST1_NAMED("!(testValue >= oneTest.GetTicks())", !(testValue >= oneTest.GetTicks()), oneTest.GetTicks(), testValue.GetTicks());

						pThis->NextStage();
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

