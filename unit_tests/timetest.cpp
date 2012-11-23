#include "common/stdafx.h"

#include "timetest.h"

//==============================================================================

namespace test
{
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
		AddStage("Construction", TimeValueConstruction);

		return CUnitTest::Initialise(verbosity);
	}

	//============================================================================

	void CTimeTest::Uninitialise(void)
	{
		CUnitTest::Uninitialise();
	}

	//============================================================================

	uint32 CTimeTest::TimeValueConstruction(CUnitTest* pParent)
	{
		CTimeTest* pThis = static_cast<CTimeTest*>(pParent);
		uint32 status = eSS_SUCCESS;

		if (pThis->m_testStatus == eTS_RUNNING)
		{
			switch (pThis->m_stage)
			{
				case 0: // Test getting interface pointer
					{
						ITime* pTime = GetITime();
						if (pTime == pThis->m_pTime)
						{
							pThis->Log(eTV_INFORMATION, "Time interface obtained correctly (behaving as a singleton)\n");
						}
						else
						{
							pThis->Log(eTV_ERROR, "Time interface different! (Not behaving as a singleton)\n");
						}

						++pThis->m_stage;
					}
					break;

				case 1: // Test default constructor
					{
						CTimeValue zeroTest;
						if (zeroTest.GetSeconds() == 0.0)
						{
							pThis->Log(eTV_INFORMATION, "Default constructor initialised time value to 0.0s\n");
						}
						else
						{
							pThis->Log(eTV_WARNING, "Default constructor failed to initialise time value to 0.0s (%g)!\n", zeroTest.GetSeconds());
						}

						++pThis->m_stage;
					}
					break;

				case 2: // Test value constructor
					{
						CTimeValue oneTest(1.0);
						if (oneTest.GetSeconds() == 1.0)
						{
							pThis->Log(eTV_INFORMATION, "Value constructor initialised time value to 1.0s\n");
						}
						else
						{
							pThis->Log(eTV_WARNING, "Value constructor failed to initialise time value to 1.0s (%g)!\n", oneTest.GetSeconds());
						}

						++pThis->m_stage;
					}
					break;

				case 3: // Test copy constructor
					{
						CTimeValue oneTest(1.0);
						CTimeValue copyTest(oneTest);

						if (copyTest.GetSeconds() == 1.0)
						{
							pThis->Log(eTV_INFORMATION, "Copy constructor initialised time value to 1.0s\n");
						}
						else
						{
							pThis->Log(eTV_WARNING, "Copy constructor failed to initialise time value to 1.0s (%g)!\n", copyTest.GetSeconds());
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

	uint32 CTimeTest::TimeValueOperations(CUnitTest* pParent)
	{
		CTimeTest* pThis = static_cast<CTimeTest*>(pParent);
		return eSS_SUCCESS | eSS_COMPLETE;
	}

	//============================================================================
} // End [namespace test]

//==============================================================================
// [EOF]

