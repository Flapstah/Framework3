#include "common/stdafx.h"

#include "timetest.h"

//==============================================================================

namespace test
{
	CTimeTest::CTimeTest(void)
		: CUnitTest("Time")
	{
		Initialise(eTV_STAGE_DETAILS);
	}

	//============================================================================

	CTimeTest::~CTimeTest(void)
	{
		Uninitialise();
	}

	//============================================================================

	bool CTimeTest::Initialise(eTestVerbosity verbosity)
	{
		CUnitTest::Initialise(verbosity);
	}

	//============================================================================

	const CTimeValue& CTimeTest::Start(void)
	{
		CUnitTest::Start();
	}

	//============================================================================

	CUnitTest::eTestStatus CTimeTest::Update(void)
	{
		Log(eTV_STAGE_DETAILS, "Test getting time interface...[0x%p]\n", GetITime());

		Log(eTV_STAGE_DETAILS, "Test CTimeValue...\n");
		CTimeValue tv1;
		CTimeValue tv2(2.0);
		CTimeValue tv3(3.0);
		CTimeValue tv4(tv2+tv3);
		Log(eTV_STAGE_DETAILS, "tv1 = %fs\ntv2 = %fs\ntv3 = %fs\ntv4 = %fs\n", tv1.GetSeconds(), tv2.GetSeconds(), tv3.GetSeconds(), tv4.GetSeconds());

		return eTS_SUCCESS;
	}

	//============================================================================

	const CTimeValue& CTimeTest::End(void)
	{
		CUnitTest::End();
	}

	//============================================================================

	void CTimeTest::Uninitialise(void)
	{
		CUnitTest::Uninitialise();
	}

	//============================================================================
} // End [namespace test]

//==============================================================================
// [EOF]

