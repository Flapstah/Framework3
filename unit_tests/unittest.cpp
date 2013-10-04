#include "common/stdafx.h"

#include "unittest.h"

//==============================================================================

namespace test
{
	//============================================================================

	CUnitTest::CUnitTest(const char* name)
		:	m_pTime(GetITime())
		,	m_testStatus(eTS_UNINITIALISED)
		,	m_stageStatus(eSS_PASS)
		,	m_verbosity(eTV_INFORMATION)
		,	m_name(name)
		, m_stageErrors(0)
		, m_totalErrors(0)
		, m_totalTests(0)
		, m_stage(0)
		, m_subStage(0)
		, m_supressNewline(false)
	{
	}

	//============================================================================

	CUnitTest::~CUnitTest(void)
	{
		char timeBuffer[32];
		TimeStamp(timeBuffer, sizeof(timeBuffer));
		engine::time::CTimeValue elapsed = m_timeEnded-m_timeStarted;
		
		int32 days, hours, minutes;
		float seconds;
		elapsed.GetTime(days, hours, minutes, seconds);

		const char* errorColour = (m_stageErrors != 0) ? COLOUR_ERROR : COLOUR_DEFAULT;

		Log(eTV_RESULT, COLOUR_PROGRESS "[%s] " COLOUR_TEST_INFO "[%s] " COLOUR_DEFAULT "%d tests completed in %s%d days, %02u:%02u:%06.3fs; " COLOUR_DEFAULT ", %s%d errors\n", timeBuffer, m_name, m_totalTests, (elapsed.GetTicks() < 0) ? "-" : "",  days, hours, minutes, seconds, errorColour, m_totalErrors);
	}

	//============================================================================

	bool CUnitTest::Initialise(void)
	{
		ResetStage();
		ResetSubstage();

		m_testStatus = eTS_INITIALISED;
		m_testIterator = m_tests.begin();

		return true;
	}

	//============================================================================

	const CTimeValue& CUnitTest::Start(void)
	{
		m_timeStarted = engine::time::GetITime()->GetCurrentTime();
		m_testStatus = eTS_RUNNING;

		return m_timeStarted;
	}

	//============================================================================

	CUnitTest::eTestStatus CUnitTest::Update(void)
	{
		char timeBuffer[32];
		if (m_testStatus == eTS_RUNNING)
		{
			if (m_testIterator != m_tests.end())
			{
				STest& test = *m_testIterator;
				if (GetStage() == 1)
				{
					m_verbosity = test.m_verbosity;
					TimeStamp(timeBuffer, sizeof(timeBuffer));
					Log(eTV_RESULT, COLOUR_PROGRESS "[%s] " COLOUR_TEST_INFO "[%s:%s] " COLOUR_DEFAULT "started", timeBuffer, m_name, test.m_name.c_str());
				}

				uint32 status = test.m_function(this);
				ResetSubstage();

				if (status & eSS_COMPLETE)
				{
					const char* errorColour = (m_stageErrors != 0) ? COLOUR_ERROR : COLOUR_DEFAULT;

					TimeStamp(timeBuffer, sizeof(timeBuffer));
					Log(eTV_RESULT, COLOUR_PROGRESS "[%s] " COLOUR_TEST_INFO "[%s:%s] " COLOUR_DEFAULT "complete; " COLOUR_DEFAULT ", %s%d errors\n", timeBuffer, m_name, test.m_name.c_str(), errorColour, m_stageErrors);

					m_totalErrors += m_stageErrors;
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
		m_timeEnded = engine::time::GetITime()->GetCurrentTime();
		return m_timeEnded;
	}

	//============================================================================

	void CUnitTest::Uninitialise(void)
	{
	}

	//============================================================================

	void CUnitTest::AddStage(const char* name, TestFn function, eTestVerbosity verbosity /* = eTV_RESULT */)
	{
		if (m_testStatus == eTS_UNINITIALISED)
		{
			m_tests.push_back(STest(name, function, verbosity));
		}
	}

	//============================================================================

	void CUnitTest::Log(eTestVerbosity targetLevel, const char* format, ...)
	{
		va_list args;
		va_start(args, format);

		switch (targetLevel)
		{
		case eTV_ERROR:
			++m_stageErrors;
			break;

		default:
			break;
		}

		if (m_verbosity >= targetLevel)
		{
			switch (targetLevel)
			{
			case eTV_RESULT:
				printf(COLOUR_SUCCESS);
				break;
			case eTV_ERROR:
				printf(COLOUR_ERROR);
				break;
			case eTV_INFORMATION:
				printf(COLOUR_INFO);
				break;
			default:
				printf(COLOUR_DEFAULT);
				break;
			}

			vprintf(format, args);
			printf(COLOUR_RESET);
			if (m_supressNewline == false)
			{
				printf("\n");
			}
		}

		va_end(args);
	}

	//============================================================================

	uint32 CUnitTest::GetStage(void)
	{
		return m_stage+1;
	}

	//============================================================================

	uint32 CUnitTest::NextStage(void)
	{
		m_totalTests += (GetSubstage() == 1) ? 1 : 0; return ++m_stage;
	}

	//============================================================================

	uint32 CUnitTest::GetSubstage(void)
	{
		return m_subStage+1;
	}

	//============================================================================

	uint32 CUnitTest::NextSubstage(void)
	{
		++m_totalTests; return ++m_subStage;
	}

	//============================================================================

	bool CUnitTest::IsEqual(double param1, double param2, double epsilon /* = 0.0 */)
	{
		return ((param1 >= (param2-epsilon)) && (param1 <= (param2+epsilon)));
	}

	//============================================================================

	bool CUnitTest::SupressNewline(bool supress)
	{
		bool oldValue = m_supressNewline;
		m_supressNewline = supress;
		return oldValue;
	}

	//============================================================================

	const char* CUnitTest::TimeStamp(char* const buffer, uint32 size)
	{
		char local_buffer[64];
		CTimeValue now = engine::time::GetITime()->GetCurrentTime();
		int32 days, hours, minutes;
		float seconds;

		now.GetTime(days, hours, minutes, seconds);
		sprintf(local_buffer, "%02u:%02u:%06.3fs", hours, minutes, seconds);
		strncpy(buffer, local_buffer, size);
		buffer[size-1] = 0;

		return buffer;
	}

	//============================================================================

	void CUnitTest::ResetStage(void)
	{
		m_stageErrors = m_stage = 0;
	}

	//============================================================================

	void CUnitTest::ResetSubstage(void)
	{
		m_subStage = 0;
	}

	//============================================================================
} // End [namespace test]

//==============================================================================
// [EOF]

