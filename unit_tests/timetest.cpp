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
		AddStage("CTimeValue Limits", TimeValueLimits, eTV_TERSE);
		AddStage("CTimeValue Operations", TimeValueOperations, eTV_TERSE);

		return CUnitTest::Initialise();
	}

	//============================================================================

	uint32 CTimeTest::TimeValueLimits(CUnitTest* pParent)
	{
		char buffer[128];
		CTimeTest* pThis = static_cast<CTimeTest*>(pParent);
		uint32 status = eSS_PASS;

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

						sprintf(buffer, "Minimum negative time value: %s%d days, %02u:%02u:%06.3fs", (testValue.GetTicks() < 0) ? "-" : "+",  days, hours, minutes, seconds);
						pThis->PerformTest(buffer, true, NULL);
					}
					break;

				case 2: // Maximum positive time
					{
						CTimeValue testValue(DECLARE_64BIT(0x7fffffffffffffff));
						testValue.GetTime(days, hours, minutes, seconds);

						sprintf(buffer, "Maximum positive time value: %s%d days, %02u:%02u:%06.3fs", (testValue.GetTicks() < 0) ? "-" : "+",  days, hours, minutes, seconds);
						pThis->PerformTest(buffer, true, NULL);
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
		uint32 status = eSS_PASS;

		if (pThis->m_testStatus == eTS_RUNNING)
		{
			switch (pThis->GetStage())
			{
				case 1: // Constructors
					{
						// Test default constructor
						CTimeValue zeroTest;
						pThis->PerformTest("Default constructor", pThis->IsEqual(zeroTest.GetSeconds(), 0.0), "CTimeValue not zero", eTT_SubStage);

						// Test value constructor
						CTimeValue oneTest(1.0);
						pThis->PerformTest("Construct with value", pThis->IsEqual(oneTest.GetSeconds(), 1.0), "CTimeValue not set to value", eTT_SubStage);

						// Test copy constructor
						CTimeValue copyTest(oneTest);
						pThis->PerformTest("Copy constructor", pThis->IsEqual(copyTest.GetSeconds(), oneTest.GetSeconds()), "CTimeValue copy not equal to original");
					}
					break;

				case 2: // operator=
					{
						CTimeValue testValue(99.0);
						CTimeValue oneTest(1.0);

						// operator=(const CTimeValue& other)
						testValue = oneTest;
						pThis->PerformTest("operator=(const CTimeValue& other)", pThis->IsEqual(testValue.GetSeconds(), oneTest.GetSeconds()), "CTimeValue not set to value", eTT_SubStage);

						// operator=(double seconds)
						testValue = 2.0;
						pThis->PerformTest("operator=(double seconds)", pThis->IsEqual(testValue.GetSeconds(), 2.0), "CTimeValue not set to value", eTT_SubStage);

						// operator=(double seconds)
						testValue = -2.0;
						pThis->PerformTest("operator=(double seconds) (negative)", pThis->IsEqual(testValue.GetSeconds(), -2.0), "CTimeValue not set to value", eTT_SubStage);

						// operator=(int64 ticks)
						testValue = int64(0);
						pThis->PerformTest("operator=(int64 ticks)", testValue.GetTicks() == 0, "CTimeValue not set to value");
					}
					break;

				case 3: // operator+=
					{
						CTimeValue testValue(1.0);
						CTimeValue twoTest(2.0);

						// operator+=(const CTimeValue& other)
						CTimeValue oldValue(testValue);
						testValue += twoTest;
						pThis->PerformTest("operator+=(const CTimeValue& other)", pThis->IsEqual(testValue.GetSeconds(), 3.0), "CTimeValue not set to value", eTT_SubStage);

						// operator+=(double seconds)
						oldValue = testValue;
						testValue += 2.0;
						pThis->PerformTest("operator+=(double seconds)", pThis->IsEqual(testValue.GetSeconds(), 5.0), "CTimeValue not set to value", eTT_SubStage);

						// operator+=(double seconds)
						oldValue = testValue;
						testValue += -3.0;
						pThis->PerformTest("operator+=(double seconds) (negative)", pThis->IsEqual(testValue.GetSeconds(), 2.0), "CTimeValue not set to value", eTT_SubStage);

						// operator+=(int64 ticks)
						oldValue = testValue;
						testValue += twoTest.GetTicks();
						pThis->PerformTest("operator+=(int64 ticks)", pThis->IsEqual(testValue.GetSeconds(), 4.0), "CTimeValue not set to value");
					}
					break;

				case 4: // operator-=
					{
						CTimeValue testValue(1.0);
						CTimeValue twoTest(2.0);

						// operator-=(const CTimeValue& other)
						CTimeValue oldValue(testValue);
						testValue -= twoTest;
						pThis->PerformTest("operator-=(const CTimeValue& other)", pThis->IsEqual(testValue.GetSeconds(), -1.0), "CTimeValue not set to value", eTT_SubStage);

						// operator-=(double seconds)
						oldValue = testValue;
						testValue -= 2.0;
						pThis->PerformTest("operator-=(double seconds)", pThis->IsEqual(testValue.GetSeconds(), -3.0), "CTimeValue not set to value", eTT_SubStage);

						// operator-=(double seconds)
						oldValue = testValue;
						testValue -= -5.0;
						pThis->PerformTest("operator-=(double seconds) (negative)", pThis->IsEqual(testValue.GetSeconds(), 2.0), "CTimeValue not set to value", eTT_SubStage);

						// operator-=(int64 ticks)
						oldValue = testValue;
						testValue -= twoTest.GetTicks();
						pThis->PerformTest("operator-=(int64 ticks)", pThis->IsEqual(testValue.GetSeconds(), 0.0), "CTimeValue not set to value");
					}
					break;

				case 5: // operator+
					{
						CTimeValue oneTest(1.0);
						CTimeValue twoTest(2.0);
						CTimeValue minusTwoTest(-2.0);

						// operator+(const CTimeValue& other)
						CTimeValue testValue = oneTest+twoTest;
						pThis->PerformTest("operator+(const CTimeValue& other)", pThis->IsEqual(testValue.GetSeconds(), 3.0), "CTimeValue not set to value", eTT_SubStage);

						// operator+(const CTimeValue& other)
						testValue = oneTest+minusTwoTest;
						pThis->PerformTest("operator+(const CTimeValue& other) (negative)", pThis->IsEqual(testValue.GetSeconds(), -1.0), "CTimeValue not set to value", eTT_SubStage);

						// operator+(double seconds)
						testValue = twoTest+3.0;
						pThis->PerformTest("operator+(double seconds)", pThis->IsEqual(testValue.GetSeconds(), 5.0), "CTimeValue not set to value", eTT_SubStage);

						// operator+(double seconds)
						testValue = twoTest+(-3.0);
						pThis->PerformTest("operator+(double seconds) (negative)", pThis->IsEqual(testValue.GetSeconds(), -1.0), "CTimeValue not set to value", eTT_SubStage);

						// operator+(int64 ticks)
						testValue = oneTest.GetTicks()+twoTest.GetTicks();
						pThis->PerformTest("operator+(int64 ticks)", pThis->IsEqual(testValue.GetSeconds(), 3.0), "CTimeValue not set to value", eTT_SubStage);

						// operator+(int64 ticks)
						testValue = oneTest.GetTicks()+minusTwoTest.GetTicks();
						pThis->PerformTest("operator+(int64 ticks) (negative)", pThis->IsEqual(testValue.GetSeconds(), -1.0), "CTimeValue not set to value");
					}
					break;

				case 6: // operator-
					{
						CTimeValue oneTest(1.0);
						CTimeValue twoTest(2.0);
						CTimeValue minusTwoTest(-2.0);

						// operator-(const CTimeValue& other)
						CTimeValue testValue = oneTest-twoTest;
						pThis->PerformTest("operator-(const CTimeValue& other)", pThis->IsEqual(testValue.GetSeconds(), -1.0), "CTimeValue not set to value", eTT_SubStage);

						// operator-(const CTimeValue& other)
						testValue = oneTest-minusTwoTest;
						pThis->PerformTest("operator-(const CTimeValue& other) (negative)", pThis->IsEqual(testValue.GetSeconds(), 3.0), "CTimeValue not set to value", eTT_SubStage);

						// operator-(double seconds)
						testValue = twoTest-1.0;
						pThis->PerformTest("operator-(double seconds)", pThis->IsEqual(testValue.GetSeconds(), 1.0), "CTimeValue not set to value", eTT_SubStage);

						// operator-(double seconds)
						testValue = twoTest-(-3.0);
						pThis->PerformTest("operator-(double seconds) (negative)", pThis->IsEqual(testValue.GetSeconds(), 5.0), "CTimeValue not set to value", eTT_SubStage);

						// operator-(int64 ticks)
						testValue = oneTest.GetTicks()-twoTest.GetTicks();
						pThis->PerformTest("operator-(int64 ticks)", pThis->IsEqual(testValue.GetSeconds(), -1.0), "CTimeValue not set to value", eTT_SubStage);

						// operator-(int64 ticks)
						testValue = oneTest.GetTicks()-minusTwoTest.GetTicks();
						pThis->PerformTest("operator-(int64 ticks) (negative)", pThis->IsEqual(testValue.GetSeconds(), 3.0), "CTimeValue not set to value");
					}
					break;

				case 7: // operator==
					{
						CTimeValue oneTest(1.0);
						CTimeValue testValue(1.0);

						// operator==(const CTimeValue& other)
						pThis->PerformTest("operator==(const CTimeValue& other)", testValue == oneTest, "CTimeValue not equal", eTT_SubStage);

						// operator==(double seconds)
						pThis->PerformTest("operator==(double seconds)", testValue == 1.0, "CTimeValue not equal", eTT_SubStage);

						// operator==(int64 ticks)
						pThis->PerformTest("operator==(int64 ticks)", testValue.GetTicks() == oneTest.GetTicks(), "CTimeValue not equal");
					}
					break;

				case 8: // operator!=
					{
						CTimeValue oneTest(1.0);
						CTimeValue testValue(2.0);

						// operator!=(const CTimeValue& other)
						pThis->PerformTest("operator==(const CTimeValue& other)", testValue != oneTest, "CTimeValue not equal", eTT_SubStage);

						// operator!=(double seconds)
						pThis->PerformTest("operator==(double seconds)", testValue != 1.0, "CTimeValue not equal", eTT_SubStage);

						// operator!=(int64 ticks)
						pThis->PerformTest("operator==(int64 ticks)", testValue.GetTicks() != oneTest.GetTicks(), "CTimeValue not equal");
					}
					break;

				case 9: // operator<
					{
						CTimeValue oneTest(1.0);
						CTimeValue testValue(2.0);

						// operator<(const CTimeValue& other)
						pThis->PerformTest("operator<(const CTimeValue& other) (other is less)", !(testValue < oneTest), "CTimeValue greater than or equal", eTT_SubStage);
						testValue = 1.0;
						pThis->PerformTest("operator<(const CTimeValue& other) (other is equal)", !(testValue < oneTest), "CTimeValue greater than or equal", eTT_SubStage);
						testValue = 0.5;
						pThis->PerformTest("operator<(const CTimeValue& other) (other is greater)", testValue < oneTest, "CTimeValue greater than or equal", eTT_SubStage);

						// operator<(double seconds)
						testValue = 2.0;
						pThis->PerformTest("operator<(double seconds) (seconds is less)", !(testValue < 1.0), "CTimeValue greater than or equal", eTT_SubStage);
						testValue = 1.0;
						pThis->PerformTest("operator<(double seconds) (seconds is equal)", !(testValue < 1.0), "CTimeValue greater than or equal", eTT_SubStage);
						testValue = 0.5;
						pThis->PerformTest("operator<(double seconds) (seconds is greater)", testValue < 1.0, "CTimeValue greater than or equal", eTT_SubStage);

						// operator<(int64 ticks)
						testValue = 2.0;
						pThis->PerformTest("operator<(const CTimeValue& other) (other is less)", !(testValue < oneTest.GetTicks()), "CTimeValue greater than or equal", eTT_SubStage);
						testValue = 1.0;
						pThis->PerformTest("operator<(const CTimeValue& other) (other is equal)", !(testValue < oneTest.GetTicks()), "CTimeValue greater than or equal", eTT_SubStage);
						testValue = 0.5;
						pThis->PerformTest("operator<(const CTimeValue& other) (other is greater)", testValue < oneTest.GetTicks(), "CTimeValue greater than or equal");
					}
					break;

				case 10: // operator<=
					{
						CTimeValue oneTest(1.0);
						CTimeValue testValue(2.0);

						// operator<=(const CTimeValue& other)
						pThis->PerformTest("operator<=(const CTimeValue& other) (other is less)", !(testValue <= oneTest), "CTimeValue greater", eTT_SubStage);
						testValue = 1.0;
						pThis->PerformTest("operator<=(const CTimeValue& other) (other is equal)", testValue <= oneTest, "CTimeValue greater", eTT_SubStage);
						testValue = 0.5;
						pThis->PerformTest("operator<=(const CTimeValue& other) (other is greater)", testValue <= oneTest, "CTimeValue greater", eTT_SubStage);

						// operator<=(double seconds)
						testValue = 2.0;
						pThis->PerformTest("operator<=(double seconds) (seconds is less)", !(testValue <= 1.0), "CTimeValue greater", eTT_SubStage);
						testValue = 1.0;
						pThis->PerformTest("operator<=(double seconds) (seconds is equal)", testValue <= 1.0, "CTimeValue greater", eTT_SubStage);
						testValue = 0.5;
						pThis->PerformTest("operator<=(double seconds) (seconds is greater)", testValue <= 1.0, "CTimeValue greater", eTT_SubStage);

						// operator<=(int64 ticks)
						testValue = 2.0;
						pThis->PerformTest("operator<=(const CTimeValue& other) (other is less)", !(testValue <= oneTest.GetTicks()), "CTimeValue greater", eTT_SubStage);
						testValue = 1.0;
						pThis->PerformTest("operator<=(const CTimeValue& other) (other is equal)", testValue <= oneTest.GetTicks(), "CTimeValue greater", eTT_SubStage);
						testValue = 0.5;
						pThis->PerformTest("operator<=(const CTimeValue& other) (other is greater)", testValue <= oneTest.GetTicks(), "CTimeValue greater");
					}
					break;

				case 11: // operator>
					{
						CTimeValue oneTest(1.0);
						CTimeValue testValue(2.0);

						// operator>(const CTimeValue& other)
						pThis->PerformTest("operator>(const CTimeValue& other) (other is less)", testValue > oneTest, "CTimeValue less than or equal", eTT_SubStage);
						testValue = 1.0;
						pThis->PerformTest("operator>(const CTimeValue& other) (other is equal)", !(testValue > oneTest), "CTimeValue less than or equal", eTT_SubStage);
						testValue = 0.5;
						pThis->PerformTest("operator>(const CTimeValue& other) (other is greater)", !(testValue > oneTest), "CTimeValue less than or equal", eTT_SubStage);

						// operator>(double seconds)
						testValue = 2.0;
						pThis->PerformTest("operator>(double seconds) (seconds is less)", testValue > 1.0, "CTimeValue less than or equal", eTT_SubStage);
						testValue = 1.0;
						pThis->PerformTest("operator>(double seconds) (seconds is equal)", !(testValue > 1.0), "CTimeValue less than or equal", eTT_SubStage);
						testValue = 0.5;
						pThis->PerformTest("operator>(double seconds) (seconds is greater)", !(testValue > 1.0), "CTimeValue less than or equal", eTT_SubStage);

						// operator>(int64 ticks)
						testValue = 2.0;
						pThis->PerformTest("operator>(const CTimeValue& other) (other is less)", testValue > oneTest.GetTicks(), "CTimeValue less than or equal", eTT_SubStage);
						testValue = 1.0;
						pThis->PerformTest("operator>(const CTimeValue& other) (other is equal)", !(testValue > oneTest.GetTicks()), "CTimeValue less than or equal", eTT_SubStage);
						testValue = 0.5;
						pThis->PerformTest("operator>(const CTimeValue& other) (other is greater)", !(testValue > oneTest.GetTicks()), "CTimeValue less than or equal");
					}
					break;

				case 12: // operator>=
					{
						CTimeValue oneTest(1.0);
						CTimeValue testValue(2.0);

						// operator>=(const CTimeValue& other)
						pThis->PerformTest("operator>=(const CTimeValue& other) (other is less)", testValue >= oneTest, "CTimeValue less than", eTT_SubStage);
						testValue = 1.0;
						pThis->PerformTest("operator>=(const CTimeValue& other) (other is equal)", testValue >= oneTest, "CTimeValue less than", eTT_SubStage);
						testValue = 0.5;
						pThis->PerformTest("operator>=(const CTimeValue& other) (other is greater)", !(testValue >= oneTest), "CTimeValue less than", eTT_SubStage);

						// operator>(double seconds)
						testValue = 2.0;
						pThis->PerformTest("operator>=(double seconds) (seconds is less)", testValue >= 1.0, "CTimeValue less than", eTT_SubStage);
						testValue = 1.0;
						pThis->PerformTest("operator>=(double seconds) (seconds is equal)", testValue >= 1.0, "CTimeValue less than", eTT_SubStage);
						testValue = 0.5;
						pThis->PerformTest("operator>=(double seconds) (seconds is greater)", !(testValue >= 1.0), "CTimeValue less than", eTT_SubStage);

						// operator>(int64 ticks)
						testValue = 2.0;
						pThis->PerformTest("operator>=(const CTimeValue& other) (other is less)", testValue >= oneTest.GetTicks(), "CTimeValue less than", eTT_SubStage);
						testValue = 1.0;
						pThis->PerformTest("operator>=(const CTimeValue& other) (other is equal)", testValue >= oneTest.GetTicks(), "CTimeValue less than", eTT_SubStage);
						testValue = 0.5;
						pThis->PerformTest("operator>=(const CTimeValue& other) (other is greater)", !(testValue >= oneTest.GetTicks()), "CTimeValue less than");
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

