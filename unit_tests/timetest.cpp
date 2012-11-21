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

	const engine::time::CTimeValue& CTimeTest::Start(void)
	{
		CUnitTest::Start();
	}

	//============================================================================

	CUnitTest::eTestStatus CTimeTest::Update(void)
	{
		Log(eTV_STAGE_DETAILS, "Test getting time interface...");
		engine::time::ITime* pTime = engine::time::GetITime();
		Log(eTV_STAGE_DETAILS, "[%p]\n");

		Log(eTV_STAGE_DETAILS, "Test CTimeValue...\n");
		engine::time::CTimeValue tv1;
		engine::time::CTimeValue tv2(2.0);
		engine::time::CTimeValue tv3(3.0);
		engine::time::CTimeValue tv4(tv2+tv3);
		Log(eTV_STAGE_DETAILS, "tv1 = %fs\ntv2 = %fs\ntv3 = %fs\ntv4 = %fs\n", tv1.GetSeconds(), tv2.GetSeconds(), tv3.GetSeconds(), tv4.GetSeconds());

		return eTS_SUCCESS;
	}

	//============================================================================

	const engine::time::CTimeValue& CTimeTest::End(void)
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

