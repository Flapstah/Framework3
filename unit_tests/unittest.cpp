#include "common/stdafx.h"

#include "unittest.h"

//==============================================================================

namespace test
{
	//============================================================================

	CUnitTest::CUnitTest(const char* name)
		:	m_pTime(GetITime())
		,	m_name(name)
		,	m_status(eTS_SUCCESS)
		,	m_verbosity(eTV_OVERALL_RESULT_ONLY)
	{
	}

	//============================================================================

	CUnitTest::~CUnitTest(void)
	{
		const char* status = "PASSED";
		switch (m_status)
		{
			case eTS_SUCCESS:
				status = "PASSED";
				break;

			case eTS_FAIL_CONTINUE:
				status = "FAILED";
				break;

			case eTS_FAIL_ABORT:
				status = "ABORTED";
				break;

			default:
				status = "UNKNOWN";
				break;
		}

		engine::time::CTimeValue elapsed = m_timeEnded-m_timeStarted;
		
		int32 days, hours, minutes;
		float seconds;
		elapsed.GetTime(days, hours, minutes, seconds);

		printf("Unit test [%s] %s in %s%d days, %02u:%02u:%06.3fs\n\n", m_name, status, (elapsed.GetTicks() < 0) ? "-" : "",  days, hours, minutes, seconds);
	}

	//============================================================================

	bool CUnitTest::Initialise(eTestVerbosity verbosity)
	{
		m_verbosity = verbosity;
	}

	//============================================================================

	const CTimeValue& CUnitTest::Start(void)
	{
		m_timeStarted = engine::time::GetITime()->GetCurrentTime();
		return m_timeStarted;
	}

	//============================================================================

	CUnitTest::eTestStatus CUnitTest::Update(void)
	{
	}

	//============================================================================

	const CTimeValue& CUnitTest::End(void)
	{
		m_timeEnded = engine::time::GetITime()->GetCurrentTime();
		return m_timeEnded;
	}

	//============================================================================

	void CUnitTest::Uninitialise(void)
	{
	}

	//============================================================================

	void CUnitTest::Log(eTestVerbosity targetLevel, const char* format, ...)
	{
		va_list args;
		va_start(args, format);

		if (m_verbosity >= targetLevel)
		{
			vprintf(format, args);
		}

		va_end(args);
	}

	//============================================================================
} // End [namespace test]

//==============================================================================
// [EOF]

