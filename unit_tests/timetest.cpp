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
		const char* name = "Construction";
		AddStage(name, TimeValueConstruction);
		CUnitTest::Initialise(verbosity);
		return true;
	}

	//============================================================================

	const CTimeValue& CTimeTest::Start(void)
	{
		return CUnitTest::Start();
	}

	//============================================================================

	CUnitTest::eTestStatus CTimeTest::Update(void)
	{
		return eTS_RUNNING;
	}

	//============================================================================

	const CTimeValue& CTimeTest::End(void)
	{
		return CUnitTest::End();
	}

	//============================================================================

	void CTimeTest::Uninitialise(void)
	{
		CUnitTest::Uninitialise();
	}

	//============================================================================

	uint32 CTimeTest::TimeValueConstruction(CUnitTest* pThis)
	{
		/*
		CTimeTest* _this = static_cast<CTimeTest*>(pThis);
		if (m_testStatus == eTS_RUNNING)
		{
			switch (m_stage)
			{
				case 0: // Test getting interface pointer
					{
						ITime* pTime = GetITime();
						if (pTime == m_pTime)
						{
							Log(eTV_INFORMATION, "Time interface obtained correctly (behaving as a singleton)\n");
						}
						else
						{
							Log(eTV_INFORMATION, "Time interface different! (Not behaving as a singleton)\n");
						}

						++m_stage;
					}
					break;

				case 1: // Test default constructor
					{
						CTimeValue zeroTest;
						if (zeroTest.GetSeconds() == 0.0)
						{
							Log(eTV_INFORMATION, "Default constructor initialised time value to 0.0s\n");
						}
						else
						{
							Log(eTV_INFORMATION, "Default constructor failed to initialise time value to 0.0s (%g)!\n", zeroTest.GetSeconds());
						}

						++m_stage;
					}
					break;

				case 2: // Test value constructor
					{
						CTimeValue oneTest(1.0);
						if (oneTest.GetSeconds() == 1.0)
						{
							Log(eTV_INFORMATION, "Value constructor initialised time value to 1.0s\n");
						}
						else
						{
							Log(eTV_INFORMATION, "Value constructor failed to initialise time value to 1.0s (%g)!\n", oneTest.GetSeconds());
						}

						++m_stage;
					}
					break;

				case 3: // Test copy constructor
					{
						CTimeValue oneTest(1.0);
						CTimeValue copyTest(oneTest);

						if (copyTest.GetSeconds() == 1.0)
						{
							Log(eTV_INFORMATION, "Copy constructor initialised time value to 1.0s\n");
						}
						else
						{
							Log(eTV_INFORMATION, "Copy constructor failed to initialise time value to 1.0s (%g)!\n", copyTest.GetSeconds());
						}

						++m_stage;
					}
					break;

				default:
					m_testStatus = eTS_FINISHED;
					break;
			}
		}

		return m_testStatus;
		*/
			return eSS_SUCCESS | eSS_COMPLETE;
	}

	//============================================================================

	uint32 CTimeTest::TimeValueOperations(CUnitTest* pThis)
	{
		return eSS_SUCCESS | eSS_COMPLETE;
	}

	//============================================================================
} // End [namespace test]

//==============================================================================
// [EOF]

