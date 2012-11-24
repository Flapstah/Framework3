#include "common/stdafx.h"

#include "timetest.h"

//==============================================================================

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
						if ((zeroTest.GetSeconds() >= 0.0) && (zeroTest.GetSeconds() <= 0.0))
						{
							pThis->Log(eTV_INFORMATION, "Default constructor initialised test value to 0.0s");
						}
						else
						{
							pThis->Log(eTV_WARNING, "CTimeValue zeroTest; failed to initialise test value to 0.0s (%g)!", zeroTest.GetSeconds());
						}

						// Test value constructor
						CTimeValue oneTest(1.0);
						if ((oneTest.GetSeconds() >= 1.0) && (oneTest.GetSeconds() <= 1.0))
						{
							pThis->Log(eTV_INFORMATION, "CTimeValue oneTest(1.0) initialised test value to 1.0s");
						}
						else
						{
							pThis->Log(eTV_WARNING, "CTimeValue oneTest(1.0) failed to initialise test value to 1.0s (%g)!", oneTest.GetSeconds());
						}

						// Test copy constructor
						CTimeValue copyTest(oneTest);
						if ((copyTest.GetSeconds() >= 1.0) && (copyTest.GetSeconds() <= 1.0))
						{
							pThis->Log(eTV_INFORMATION, "CTimeValue copyTest(oneTest) initialised test value to 1.0s");
						}
						else
						{
							pThis->Log(eTV_WARNING, "CTimeValue copyTest(oneTest) failed to initialise test value to 1.0s (%g)!", copyTest.GetSeconds());
						}

						++pThis->m_stage;
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
								pThis->Log(eTV_INFORMATION, "operator=(const CTimeValue& other) set test value to 1.0s");
							}
							else
							{
								pThis->Log(eTV_WARNING, "operator=(const CTimeValue& other) did not set test value to 1.0s (%g)!", testValue.GetSeconds());
							}
						}
						else
						{
							pThis->Log(eTV_WARNING, "CTimeValue testValue; failed to initialise test value to 0.0s (%g)!", testValue.GetSeconds());
						}

						// operator=(double seconds)
						testValue = 2.0;
						if ((testValue.GetSeconds() >= 2.0) && (testValue.GetSeconds() <= 2.0))
						{
							pThis->Log(eTV_INFORMATION, "operator=(2.0) set test value to 2.0s");
						}
						else
						{
							pThis->Log(eTV_WARNING, "operator=(2.0) did not set test value to 2.0s (%g)!", testValue.GetSeconds());
						}

						// operator=(double seconds)
						testValue = -2.0;
						if ((testValue.GetSeconds() >= -2.0) && (testValue.GetSeconds() <= -2.0))
						{
							pThis->Log(eTV_INFORMATION, "operator=(-2.0) set test value to -2.0s");
						}
						else
						{
							pThis->Log(eTV_WARNING, "operator=(-2.0) did not set test value to -2.0s (%g)!", testValue.GetSeconds());
						}

						// operator=(int64 ticks)
						testValue = int64(0);
						if (testValue.GetTicks() == 0)
						{
							pThis->Log(eTV_INFORMATION, "operator=(int64(0)) set test value to 0");
						}
						else
						{
							pThis->Log(eTV_WARNING, "operator=(int64(0)) did not set test value to 0 (%" PRId64 ")!", testValue.GetTicks());
						}

						++pThis->m_stage;
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
								pThis->Log(eTV_INFORMATION, "operator+=(const CTimeValue& other) set test value to 3.0s");
							}
							else
							{
								pThis->Log(eTV_WARNING, "operator+=(const CTimeValue& other) did not set test value to 3.0s (%g)!", testValue.GetSeconds());
							}
						}
						else
						{
							pThis->Log(eTV_WARNING, "CTimeValue testValue(1.0) failed to initialise test value to 1.0s (%g)!", testValue.GetSeconds());
						}

						// operator+=(double seconds)
						testValue += 2.0;
						if ((testValue.GetSeconds() >= 5.0) && (testValue.GetSeconds() <= 5.0))
						{
							pThis->Log(eTV_INFORMATION, "operator+=(2.0) set test value to 5.0s");
						}
						else
						{
							pThis->Log(eTV_WARNING, "operator+=(2.0) did not set test value to 5.0s (%g)!", testValue.GetSeconds());
						}

						// operator+=(double seconds)
						testValue += -3.0;
						if ((testValue.GetSeconds() >= 2.0) && (testValue.GetSeconds() <= 2.0))
						{
							pThis->Log(eTV_INFORMATION, "operator+=(-3.0) set test value to 2.0s");
						}
						else
						{
							pThis->Log(eTV_WARNING, "operator+=(-3.0) did not set test value to 2.0s (%g)!", testValue.GetSeconds());
						}

						// operator+=(int64 ticks)
						testValue += twoTest.GetTicks();
						if ((testValue.GetSeconds() >= 4.0) && (testValue.GetSeconds() <= 4.0))
						{
							pThis->Log(eTV_INFORMATION, "operator+=(twoTest.GetTicks()) set test value to 4.0s");
						}
						else
						{
							pThis->Log(eTV_WARNING, "operator+=(twoTest.GetTicks()) did not set test value to 4.0s (%g)!", testValue.GetSeconds());
						}

						++pThis->m_stage;
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
								pThis->Log(eTV_INFORMATION, "operator-=(const CTimeValue& other) set test value to -1.0s");
							}
							else
							{
								pThis->Log(eTV_WARNING, "operator-=(const CTimeValue& other) did not set test value to -1.0s (%g)!", testValue.GetSeconds());
							}
						}
						else
						{
							pThis->Log(eTV_WARNING, "Value constructor failed to initialise test value to 1.0s (%g)!", testValue.GetSeconds());
						}

						// operator-=(double seconds)
						testValue -= 2.0;
						if ((testValue.GetSeconds() >= -3.0) && (testValue.GetSeconds() <= -3.0))
						{
							pThis->Log(eTV_INFORMATION, "operator-=(2.0) set test value to -3.0s");
						}
						else
						{
							pThis->Log(eTV_WARNING, "operator-=(2.0) did not set test value to -3.0s (%g)!", testValue.GetSeconds());
						}

						// operator-=(double seconds)
						testValue -= -5.0;
						if ((testValue.GetSeconds() >= 2.0) && (testValue.GetSeconds() <= 2.0))
						{
							pThis->Log(eTV_INFORMATION, "operator-=(-5.0) set test value to 2.0s");
						}
						else
						{
							pThis->Log(eTV_WARNING, "operator-=(-5.0) did not set test value to 2.0s (%g)!", testValue.GetSeconds());
						}

						// operator-=(int64 ticks)
						testValue -= twoTest.GetTicks();
						if ((testValue.GetSeconds() >= 0.0) && (testValue.GetSeconds() <= 0.0))
						{
							pThis->Log(eTV_INFORMATION, "operator-=(twoTest.GetTicks()) set test value to 0.0s");
						}
						else
						{
							pThis->Log(eTV_WARNING, "operator-=(twoTest.GetTicks()) did not set test value to 0.0s (%g)!", testValue.GetSeconds());
						}

						++pThis->m_stage;
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

