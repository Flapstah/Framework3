#include "common/stdafx.h"

#include "unittest.h"

//==============================================================================

#define TRACE_ENABLE false

//==============================================================================

namespace test
{
	//============================================================================

	CUnitTest::CUnitTest(const char* name)
		: m_pTime(GetITime())
		, m_log(engine::system::CLog::GetMasterLog(), "UnitTest", engine::system::CLog::eB_ACTIVE | engine::system::CLog::eB_NO_STDERR | engine::system::CLog::eBT_ALL)
		, m_testStatus(eTS_UNINITIALISED)
		, m_stageStatus(eSS_PASS)
		, m_name(name)
		, m_errors(0)
		, m_errorTotal(0)
		, m_totalTests(0)
		, m_stage(0)
		, m_subStage(0)
	{
		TRACE(TRACE_ENABLE);

		LOG_ALWAYS(m_log, COLOUR_DEFAULT); 
		m_log.SetFlags(m_log.GetFlags() | engine::system::CLog::eBAI_NAME | engine::system::CLog::eBAI_TIMESTAMP);
	}

	//============================================================================

	CUnitTest::~CUnitTest(void)
	{
		TRACE(TRACE_ENABLE);

		CTimeValue elapsed = m_timeEnded-m_timeStarted;
		
		int32 days, hours, minutes;
		float seconds;
		elapsed.GetTime(days, hours, minutes, seconds);

		const char* errorColour = (m_errorTotal != 0) ? COLOUR_ERROR : COLOUR_DEFAULT;
		LOG_ALWAYS(m_log, COLOUR_TEST_INFO "[%s] " COLOUR_DEFAULT "%d tests completed in %s%d days, %02u:%02u:%06.3fs; " COLOUR_DEFAULT "%s%d errors\n\n", m_name, m_totalTests, (elapsed.GetTicks() < 0) ? "-" : "",  days, hours, minutes, seconds, errorColour, m_errorTotal);
	}

	//============================================================================

	bool CUnitTest::Initialise(void)
	{
		TRACE(TRACE_ENABLE);

		ResetStage();
		ResetSubstage();

		m_testStatus = eTS_INITIALISED;
		m_testIterator = m_tests.begin();

		return true;
	}

	//============================================================================

	const CTimeValue& CUnitTest::Start(void)
	{
		TRACE(TRACE_ENABLE);

		m_timeStarted = GetITime()->GetCurrentTime();
		m_testStatus = eTS_RUNNING;

		return m_timeStarted;
	}

	//============================================================================

	CUnitTest::eTestStatus CUnitTest::Update(void)
	{
		TRACE(TRACE_ENABLE);

		if (m_testStatus == eTS_RUNNING)
		{
			if (m_testIterator != m_tests.end())
			{
				STest& test = *m_testIterator;
				if (GetStage() == 1)
				{
					LOG_ALWAYS(m_log, COLOUR_TEST_INFO "[%s:%s] " COLOUR_DEFAULT "started", m_name, test.m_name.c_str());
				}

				uint32 status = test.m_function(this);
				ResetSubstage();

				if (status & eSS_COMPLETE)
				{
					m_log.SetFlags(m_log.GetFlags() & ~(engine::system::CLog::eBAI_NAME | engine::system::CLog::eBAI_TIMESTAMP));
					LOG_ALWAYS(m_log, COLOUR_DEFAULT "complete.\n");
					m_log.SetFlags(m_log.GetFlags() | engine::system::CLog::eBAI_NAME | engine::system::CLog::eBAI_TIMESTAMP);

					m_errorTotal += m_errors;
					ResetStage();

					++m_testIterator;
				}
			}
			else
			{
				m_testStatus = eTS_FINISHED;
			}
		}

		return m_testStatus;
	}

	//============================================================================

	const CTimeValue& CUnitTest::End(void)
	{
		TRACE(TRACE_ENABLE);

		m_timeEnded = GetITime()->GetCurrentTime();
		return m_timeEnded;
	}

	//============================================================================

	void CUnitTest::Uninitialise(void)
	{
		TRACE(TRACE_ENABLE);
	}

	//============================================================================

	void CUnitTest::AddStage(const char* name, TestFn function)
	{
		TRACE(TRACE_ENABLE);

		if (m_testStatus == eTS_UNINITIALISED)
		{
			m_tests.push_back(STest(name, function));
		}
	}

	//============================================================================

	void CUnitTest::Test(const char* description, bool test, const char* failureMessage, int32 testType /* = eTT_Stage */)
	{	
		TRACE(TRACE_ENABLE);

		const char* none = "None";
		uint32 logFlags = m_log.GetFlags();
		m_log.SetFlags(logFlags & ~(engine::system::CLog::eBAI_NAME | engine::system::CLog::eBAI_TIMESTAMP));

		if (test != true)
		{
			LOG_ALWAYS(m_log, COLOUR_PROGRESS "\n\t\t[%d:%d]" COLOUR_INFO "\t[%s]" COLOUR_PROGRESS ":" COLOUR_ERROR "[%s]", GetStage(), GetSubstage(), (description != NULL) ? description : none, (failureMessage != NULL) ? failureMessage : none);
			++m_errors;
		}
		else
		{
			LOG_ALWAYS(m_log, COLOUR_SUCCESS ".");
		}

		switch (testType)
		{
		case eTT_Stage:
			++m_stage;
			break;
		case eTT_SubStage:
			++m_subStage;
			break;
		}

		++m_totalTests;
		m_log.SetFlags(logFlags);
	}

	//============================================================================

	uint32 CUnitTest::GetStage(void)
	{
		TRACE(TRACE_ENABLE);

		return m_stage+1;
	}

	//============================================================================

	uint32 CUnitTest::GetSubstage(void)
	{
		TRACE(TRACE_ENABLE);

		return m_subStage+1;
	}

	//============================================================================

	bool CUnitTest::IsEqual(double param1, double param2, double epsilon /* = 0.0 */)
	{
		TRACE(TRACE_ENABLE);

		return ((param1 >= (param2-epsilon)) && (param1 <= (param2+epsilon)));
	}

	//============================================================================

	void CUnitTest::ResetStage(void)
	{
		TRACE(TRACE_ENABLE);

		m_errors = m_stage = 0;
	}

	//============================================================================

	void CUnitTest::ResetSubstage(void)
	{
		TRACE(TRACE_ENABLE);

		m_subStage = 0;
	}

	//============================================================================
} // End [namespace test]

//==============================================================================
// [EOF]

