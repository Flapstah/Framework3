#include "common/stdafx.h"

#include "timetest.h"

//==============================================================================
// Helper macros
//==============================================================================

// Essentially checks (_value1_) == (_value2_) in a safe way for floating point numbers
#define IS_FP_EQUIVALENT(_value1_, _value2_) (((_value1_) >= (_value2_)) && ((_value1_) <= (_value2_)))

#define TEST1_NAMED(_name_, _test_, _param1_) \
	{ \
		bool success = (_test_); \
		double param1 = static_cast<double>(_param1_); \
		pThis->Log((success == true) ? eTV_INFORMATION : eTV_WARNING, "[%d:%d] " _name_ ", parameters: (%s [%g]) [%s]", pThis->m_stage, pThis->m_subStage, #_param1_, param1, ((success == true) ? "PASSED" : "FAILED")); \
	}

#define TEST1_RESULT_NAMED(_name_, _test_, _param1_, _result_) \
	{ \
		bool success = (_test_); \
		double param1 = static_cast<double>(_param1_); \
		double result = static_cast<double>(_result_); \
		pThis->Log((success == true) ? eTV_INFORMATION : eTV_WARNING, "[%d:%d]\t" _name_ "\n\tparameters: (%s [%g])\n\tresult: (%s [%g])\n\t[%s]", pThis->m_stage, pThis->m_subStage, #_param1_, param1, #_result_, result, ((success == true) ? "PASSED" : "FAILED")); \
	}

#define TEST2_NAMED(_name_, _test_, _param1_, _param2_) \
	{ \
		bool success = (_test_); \
		double param1 = static_cast<double>(_param1_); \
		double param2 = static_cast<double>(_param2_); \
		pThis->Log((success == true) ? eTV_INFORMATION : eTV_WARNING, "[%d:%d] " _name_ ", parameters: (%s [%g], %s [%g]) [%s]", pThis->m_stage, pThis->m_subStage,  #_param1_, param1, #_param2_, param2, ((success == true) ? "PASSED" : "FAILED")); \
	}

#define TEST2_RESULT_NAMED(_name_, _test_, _param1_, _param2_, _result_) \
	{ \
		bool success = (_test_); \
		double param1 = static_cast<double>(_param1_); \
		double param2 = static_cast<double>(_param2_); \
		double result = static_cast<double>(_result_); \
		pThis->Log((success == true) ? eTV_INFORMATION : eTV_WARNING, "[%d:%d]\t" _name_ "\n\tparameters: (%s [%g], %s [%g])\n\tresult: (%s [%g])\n\t[%s]", pThis->m_stage, pThis->m_subStage,  #_param1_, param1, #_param2_, param2, #_result_, result, ((success == true) ? "PASSED" : "FAILED")); \
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
						TEST1_RESULT_NAMED("CTimeValue zeroTest", IS_FP_EQUIVALENT(zeroTest.GetSeconds(), 0.0), 0, zeroTest.GetSeconds());
						++(pThis->m_subStage);

						// Test value constructor
						CTimeValue oneTest(1.0);
						TEST1_RESULT_NAMED("CTimeValue oneTest", IS_FP_EQUIVALENT(oneTest.GetSeconds(), 1.0), 1.0, oneTest.GetSeconds());
						++(pThis->m_subStage);

						// Test copy constructor
						CTimeValue copyTest(oneTest);
						TEST1_RESULT_NAMED("CTimeValue copyTest(oneTest)", IS_FP_EQUIVALENT(copyTest.GetSeconds(), oneTest.GetSeconds()), oneTest.GetSeconds(), copyTest.GetSeconds());

						++(pThis->m_stage);
					}
					break;

				case 1: // operator=
					{
						CTimeValue testValue(99.0);
						CTimeValue oneTest(1.0);

						// operator=(const CTimeValue& other)
						testValue = oneTest;
						TEST1_RESULT_NAMED("testValue.GetSeconds() == 1.0", (testValue.GetSeconds() >= 1.0) && (testValue.GetSeconds() <= 1.0), 1.0, testValue.GetSeconds());
						++(pThis->m_subStage);

						// operator=(double seconds)
						testValue = 2.0;
						TEST1_RESULT_NAMED("testValue.GetSeconds() == 2.0", (testValue.GetSeconds() >= 2.0) && (testValue.GetSeconds() <= 2.0), 2.0, testValue.GetSeconds());
						++(pThis->m_subStage);

						// operator=(double seconds)
						testValue = -2.0;
						TEST1_RESULT_NAMED("testValue.GetSeconds() == -2.0", (testValue.GetSeconds() >= -2.0) && (testValue.GetSeconds() <= -2.0), -2.0, testValue.GetSeconds());
						++(pThis->m_subStage);

						// operator=(int64 ticks)
						testValue = int64(0);
						TEST1_RESULT_NAMED("testValue.GetTicks() == 0", testValue.GetTicks() == 0, 0, testValue.GetTicks());

						++(pThis->m_stage);
					}
					break;

				case 2: // operator+=
					{
						CTimeValue testValue(1.0);
						CTimeValue twoTest(2.0);

						// operator+=(const CTimeValue& other)
						CTimeValue oldValue(testValue);
						testValue += twoTest;
						TEST2_NAMED("(testValue += twoTest) == 3.0", (testValue.GetSeconds() >= 3.0) && (testValue.GetSeconds() <= 3.0), oldValue.GetSeconds(), twoTest.GetSeconds());
						++(pThis->m_subStage);

						// operator+=(double seconds)
						oldValue = testValue;
						testValue += 2.0;
						TEST2_NAMED("(testValue += 2.0) == 5.0", (testValue.GetSeconds() >= 5.0) && (testValue.GetSeconds() <= 5.0), oldValue.GetSeconds(), 2.0);
						++(pThis->m_subStage);

						// operator+=(double seconds)
						testValue += -3.0;
						TEST2_NAMED("(testValue += -3.0) == 2.0", (testValue.GetSeconds() >= 2.0) && (testValue.GetSeconds() <= 2.0), oldValue.GetSeconds(), -3.0);
						++(pThis->m_subStage);

						// operator+=(int64 ticks)
						testValue += twoTest.GetTicks();
						TEST2_NAMED("(testValue += twoTest.GetTicks()) == 4.0s", (testValue.GetSeconds() >= 4.0) && (testValue.GetSeconds() <= 4.0), oldValue.GetTicks(), twoTest.GetTicks());

						++(pThis->m_stage);
					}
					break;

				case 3: // operator-=
					{
						CTimeValue testValue(1.0);
						CTimeValue twoTest(2.0);

						// operator-=(const CTimeValue& other)
						CTimeValue oldValue(testValue);
						testValue -= twoTest;
						TEST2_NAMED("(testValue -= twoTest) == -1.0", (testValue.GetSeconds() >= -1.0) && (testValue.GetSeconds() <= -1.0), oldValue.GetSeconds(), twoTest.GetSeconds());
						++(pThis->m_subStage);

						// operator-=(double seconds)
						testValue -= 2.0;
						TEST2_NAMED("(testValue -= 2.0) == -3.0", (testValue.GetSeconds() >= -3.0) && (testValue.GetSeconds() <= -3.0), oldValue.GetSeconds(), -2.0);
						++(pThis->m_subStage);

						// operator-=(double seconds)
						testValue -= -5.0;
						TEST2_NAMED("(testValue -= -5.0) == 2.0", (testValue.GetSeconds() >= 2.0) && (testValue.GetSeconds() <= 2.0), oldValue.GetSeconds(), -5.0);
						++(pThis->m_subStage);

						// operator-=(int64 ticks)
						testValue -= twoTest.GetTicks();
						TEST2_NAMED("(testValue -= twoTest.GetTicks()) == 0.0s", (testValue.GetSeconds() >= 0.0) && (testValue.GetSeconds() <= 0.0), oldValue.GetSeconds(), 0.0);

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
						TEST2_RESULT_NAMED("(testValue = oneTest+twoTest) == 3.0", (testValue.GetSeconds() >= 3.0) && (testValue.GetSeconds() <= 3.0), oneTest.GetSeconds(), twoTest.GetSeconds(), testValue.GetSeconds());
						++(pThis->m_subStage);

						// operator+(const CTimeValue& other)
						testValue = oneTest+minusTwoTest;
						TEST2_RESULT_NAMED("(testValue = oneTest+minusTwoTest) == -1.0", (testValue.GetSeconds() >= -1.0) && (testValue.GetSeconds() -1.0), oneTest.GetSeconds(), minusTwoTest.GetSeconds(), testValue.GetSeconds());
						++(pThis->m_subStage);

						// operator+(double seconds)
						testValue = twoTest+3.0;
						TEST2_RESULT_NAMED("(testValue = twoTest+3.0) == 5.0", (testValue.GetSeconds() >= 5.0) && (testValue.GetSeconds() <= 5.0), twoTest.GetSeconds(), 3.0, testValue.GetSeconds());
						++(pThis->m_subStage);

						// operator+(double seconds)
						testValue = twoTest+(-3.0);
						TEST2_RESULT_NAMED("(testValue = twoTest+(-3.0)) == -1.0", (testValue.GetSeconds() >= -1.0) && (testValue.GetSeconds() <= -1.0), twoTest.GetSeconds(), -3.0, testValue.GetSeconds());
						++(pThis->m_subStage);

						// operator+(int64 ticks)
						testValue = oneTest.GetTicks()+twoTest.GetTicks();
						TEST2_RESULT_NAMED("(testValue = oneTest.GetTicks()+TwoTest.GetTicks()) == 3.0s", (testValue.GetSeconds() >= 3.0) && (testValue.GetSeconds() <= 3.0), oneTest.GetTicks(), twoTest.GetTicks(), testValue.GetSeconds());
						++(pThis->m_subStage);

						// operator+(int64 ticks)
						testValue = oneTest.GetTicks()+minusTwoTest.GetTicks();
						TEST2_RESULT_NAMED("(testValue = oneTest.GetTicks()+minusTwoTest.GetTicks()) == -1.0s", (testValue.GetSeconds() >= -1.0) && (testValue.GetSeconds() <= -1.0), oneTest.GetTicks(), minusTwoTest.GetTicks(), testValue.GetSeconds());
						++(pThis->m_subStage);

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
						TEST2_NAMED("(testValue = oneTest-twoTest) == -1.0", (testValue.GetSeconds() >= -1.0) && (testValue.GetSeconds() <= -1.0), oneTest.GetSeconds(), twoTest.GetSeconds());
						++(pThis->m_subStage);

						// operator-(const CTimeValue& other)
						testValue = oneTest-minusTwoTest;
						TEST2_NAMED("(testValue = oneTest-minusTwoTest) == 3.0", (testValue.GetSeconds() >= 3.0) && (testValue.GetSeconds() <= 3.0), oneTest.GetSeconds(), minusTwoTest.GetSeconds());
						++(pThis->m_subStage);

						// operator-(double seconds)
						testValue = twoTest-1.0;
						TEST2_NAMED("(testValue = twoTest-1.0) == 1.0", (testValue.GetSeconds() >= 1.0) && (testValue.GetSeconds() <= 1.0), twoTest.GetSeconds(), 1.0);
						++(pThis->m_subStage);

						// operator-(double seconds)
						testValue = twoTest-(-3.0);
						TEST2_NAMED("(testValue = twoTest-(-3.0)) == 5.0", (testValue.GetSeconds() >= 5.0) && (testValue.GetSeconds() <= 5.0), twoTest.GetSeconds(), 5.0);
						++(pThis->m_subStage);

						// operator-(int64 ticks)
						testValue = oneTest.GetTicks()-twoTest.GetTicks();
						TEST2_NAMED("(oneTest.GetTicks()-twoTest.GetTicks()) == -1.0s", (testValue.GetSeconds() >= -1.0) && (testValue.GetSeconds() <= -1.0), oneTest.GetTicks(), twoTest.GetTicks());
						++(pThis->m_subStage);

						// operator-(int64 ticks)
						testValue = oneTest.GetTicks()-minusTwoTest.GetTicks();
						TEST2_NAMED("(oneTest.GetTicks()-minusTwoTest.GetTicks()) == 3.0s", (testValue.GetSeconds() >= 3.0) && (testValue.GetSeconds() <= 3.0), oneTest.GetTicks(), minusTwoTest.GetTicks());

						++(pThis->m_stage);
					}
					break;

				case 6: // operator==
					{
						CTimeValue oneTest(1.0);
						CTimeValue testValue(1.0);

						TEST1_RESULT_NAMED("testValue == oneTest", testValue == oneTest, oneTest.GetSeconds(), testValue.GetSeconds());
						++(pThis->m_subStage);

						TEST1_RESULT_NAMED("testValue == 1.0", testValue == 1.0, 1.0, testValue.GetSeconds());
						++(pThis->m_subStage);

						TEST1_RESULT_NAMED("testValue == oneTest.GetTicks()", testValue == oneTest.GetTicks(), oneTest.GetTicks(), testValue.GetTicks());

						++(pThis->m_stage);
					}
					break;

				case 7: // operator!=
					{
						CTimeValue oneTest(1.0);
						CTimeValue testValue(2.0);

						TEST1_NAMED("testValue != oneTest", testValue != oneTest, 1.0);
						++(pThis->m_subStage);

						TEST1_NAMED("testValue != 1.0", testValue != 1.0, 1.0);
						++(pThis->m_subStage);

						TEST1_NAMED("testValue != oneTest.GetTicks()", testValue != oneTest.GetTicks(), oneTest.GetTicks());

						++(pThis->m_stage);
					}
					break;

				case 8: // operator<
					{
						CTimeValue oneTest(1.0);
						CTimeValue testValue(2.0);

						TEST1_NAMED("!(testValue < oneTest)", !(testValue < oneTest), testValue.GetSeconds());
						++(pThis->m_subStage);

						testValue = 1.0;
						TEST1_NAMED("!(testValue < oneTest)", !(testValue < oneTest), testValue.GetSeconds());
						++(pThis->m_subStage);

						testValue = 0.5;
						TEST1_NAMED("testValue < oneTest", testValue < oneTest, testValue.GetSeconds());
						++(pThis->m_subStage);

						testValue = 2.0;
						TEST1_NAMED("!(testValue < 1.0)", !(testValue < 1.0), testValue.GetSeconds());
						++(pThis->m_subStage);

						testValue = 1.0;
						TEST1_NAMED("!(testValue < 1.0)", !(testValue < 1.0), testValue.GetSeconds());
						++(pThis->m_subStage);

						testValue = 0.5;
						TEST1_NAMED("testValue < 1.0", testValue < 1.0, testValue.GetSeconds());
						++(pThis->m_subStage);

						testValue = 2.0;
						TEST1_NAMED("!(testValue < oneTest.GetTicks())", !(testValue < oneTest.GetTicks()), testValue.GetTicks());
						++(pThis->m_subStage);

						testValue = 1.0;
						TEST1_NAMED("!(testValue < oneTest.GetTicks())", !(testValue < oneTest.GetTicks()), testValue.GetTicks());
						++(pThis->m_subStage);

						testValue = 0.5;
						TEST1_NAMED("testValue < oneTest.GetTicks()", testValue < oneTest.GetTicks(), testValue.GetTicks());

						++(pThis->m_stage);
					}
					break;

				case 9: // operator<=
					{
						CTimeValue oneTest(1.0);
						CTimeValue testValue(2.0);

						TEST1_NAMED("!(testValue <= oneTest)", !(testValue <= oneTest), testValue.GetSeconds());
						++(pThis->m_subStage);

						testValue = 1.0;
						TEST1_NAMED("testValue <= oneTest", testValue <= oneTest, testValue.GetSeconds());
						++(pThis->m_subStage);

						testValue = 0.5;
						TEST1_NAMED("testValue <= oneTest", testValue <= oneTest, testValue.GetSeconds());
						++(pThis->m_subStage);

						testValue = 2.0;
						TEST1_NAMED("!(testValue <= 1.0)", !(testValue <= 1.0), testValue.GetSeconds());
						++(pThis->m_subStage);

						testValue = 1.0;
						TEST1_NAMED("testValue <= 1.0", testValue <= 1.0, testValue.GetSeconds());
						++(pThis->m_subStage);

						testValue = 0.5;
						TEST1_NAMED("testValue <= 1.0", testValue <= 1.0, testValue.GetSeconds());
						++(pThis->m_subStage);

						testValue = 2.0;
						TEST1_NAMED("!(testValue <= oneTest.GetTicks())", !(testValue <= oneTest.GetTicks()), testValue.GetTicks());
						++(pThis->m_subStage);

						testValue = 1.0;
						TEST1_NAMED("testValue <= oneTest.GetTicks()", testValue <= oneTest.GetTicks(), testValue.GetTicks());
						++(pThis->m_subStage);

						testValue = 0.5;
						TEST1_NAMED("testValue <= oneTest.GetTicks()", testValue <= oneTest.GetTicks(), testValue.GetTicks());

						++(pThis->m_stage);
					}
					break;

				case 10: // operator>
					{
						CTimeValue oneTest(1.0);
						CTimeValue testValue(2.0);

						TEST1_NAMED("testValue > oneTest", testValue > oneTest, testValue.GetSeconds());
						++(pThis->m_subStage);

						testValue = 1.0;
						TEST1_NAMED("!(testValue > oneTest)", !(testValue > oneTest), testValue.GetSeconds());
						++(pThis->m_subStage);

						testValue = 0.5;
						TEST1_NAMED("!(testValue > oneTest)", !(testValue > oneTest), testValue.GetSeconds());
						++(pThis->m_subStage);

						testValue = 2.0;
						TEST1_NAMED("testValue > 1.0", testValue > 1.0, testValue.GetSeconds());
						++(pThis->m_subStage);

						testValue = 1.0;
						TEST1_NAMED("!(testValue > 1.0)", !(testValue > 1.0), testValue.GetSeconds());
						++(pThis->m_subStage);

						testValue = 0.5;
						TEST1_NAMED("!(testValue > 1.0)", !(testValue > 1.0), testValue.GetSeconds());
						++(pThis->m_subStage);

						testValue = 2.0;
						TEST1_NAMED("testValue > oneTest.GetTicks()", testValue > oneTest.GetTicks(), testValue.GetTicks());
						++(pThis->m_subStage);

						testValue = 1.0;
						TEST1_NAMED("!(testValue > oneTest.GetTicks())", !(testValue > oneTest.GetTicks()), testValue.GetTicks());
						++(pThis->m_subStage);

						testValue = 0.5;
						TEST1_NAMED("!(testValue > oneTest.GetTicks())", !(testValue > oneTest.GetTicks()), testValue.GetTicks());

						++(pThis->m_stage);
					}
					break;

				case 11: // operator>=
					{
						CTimeValue oneTest(1.0);
						CTimeValue testValue(2.0);

						TEST1_NAMED("testValue >= oneTest", testValue >= oneTest, testValue.GetSeconds());
						++(pThis->m_subStage);

						testValue = 1.0;
						TEST1_NAMED("testValue >= oneTest", testValue >= oneTest, testValue.GetSeconds());
						++(pThis->m_subStage);

						testValue = 0.5;
						TEST1_NAMED("!(testValue >= oneTest)", !(testValue >= oneTest), testValue.GetSeconds());
						++(pThis->m_subStage);

						testValue = 2.0;
						TEST1_NAMED("testValue >= 1.0", testValue >= 1.0, testValue.GetSeconds());
						++(pThis->m_subStage);

						testValue = 1.0;
						TEST1_NAMED("testValue >= 1.0", testValue >= 1.0, testValue.GetSeconds());
						++(pThis->m_subStage);

						testValue = 0.5;
						TEST1_NAMED("!(testValue >= 1.0)", !(testValue >= 1.0), testValue.GetSeconds());
						++(pThis->m_subStage);

						testValue = 2.0;
						TEST1_NAMED("testValue >= oneTest.GetTicks()", testValue >= oneTest.GetTicks(), testValue.GetTicks());
						++(pThis->m_subStage);

						testValue = 1.0;
						TEST1_NAMED("testValue >= oneTest.GetTicks()", testValue >= oneTest.GetTicks(), testValue.GetTicks());
						++(pThis->m_subStage);

						testValue = 0.5;
						TEST1_NAMED("!(testValue >= oneTest.GetTicks())", !(testValue >= oneTest.GetTicks()), testValue.GetTicks());

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

