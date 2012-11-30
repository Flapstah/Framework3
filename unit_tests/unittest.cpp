#include "common/stdafx.h"

#include "unittest.h"

//==============================================================================

namespace test
{
	//============================================================================

	CUnitTest::CUnitTest(const char* name)
		:	m_name(name)
		, m_stageWarnings(0)
		, m_stageErrors(0)
		, m_totalWarnings(0)
		, m_totalErrors(0)
		,	m_pTime(GetITime())
		, m_stage(0)
		, m_subStage(0)
		,	m_testStatus(eTS_UNINITIALISED)
		,	m_stageStatus(eSS_SUCCESS)
		,	m_verbosity(eTV_WARNING)
	{
	}

	//============================================================================

	CUnitTest::~CUnitTest(void)
	{
		engine::time::CTimeValue elapsed = m_timeEnded-m_timeStarted;
		
		int32 days, hours, minutes;
		float seconds;
		elapsed.GetTime(days, hours, minutes, seconds);

		Log(eTV_RESULT, "[%s] completed in %s%d days, %02u:%02u:%06.3fs, with %d warnings and %d errors\n", m_name, (elapsed.GetTicks() < 0) ? "-" : "",  days, hours, minutes, seconds, m_totalWarnings, m_totalErrors);
	}

	//============================================================================

	bool CUnitTest::Initialise(eTestVerbosity verbosity)
	{
		m_verbosity = verbosity;
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
		if (m_testStatus == eTS_RUNNING)
		{
			if (m_testIterator != m_tests.end())
			{
				STest& test = *m_testIterator;
				if (m_stage == 0)
				{
					Log(eTV_RESULT, "[%s:%s] started", m_name, test.m_name.c_str());
				}

				uint32 status = test.m_function(this);
				if (status & eSS_COMPLETE)
				{
					const char* colour = ANSI_1SEQUENCE(ANSI_FOREGROUND(ANSI_GREEN));
					if (m_stageWarnings != 0)
					{
						colour = ANSI_1SEQUENCE(ANSI_FOREGROUND(ANSI_YELLOW));
					}
					if (m_stageErrors != 0)
					{
						colour = ANSI_1SEQUENCE(ANSI_FOREGROUND(ANSI_RED));
					}

					Log(eTV_RESULT, "%s[%s:%s] complete; %d warnings, %d errors\n", colour, m_name, test.m_name.c_str(), m_stageWarnings, m_stageErrors);

					m_totalWarnings += m_stageWarnings;
					m_totalErrors += m_stageErrors;

					m_stageWarnings = 0;
					m_stageErrors = 0;

					m_stage = 0;
					m_subStage = 0;

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

	void CUnitTest::Log(eTestVerbosity targetLevel, const char* format, ...)
	{
		va_list args;
		va_start(args, format);

		if (m_verbosity >= targetLevel)
		{
			switch (targetLevel)
			{
				case eTV_RESULT:
				case eTV_INFORMATION:
					printf(ANSI_1SEQUENCE(ANSI_FOREGROUND(ANSI_GREEN)));
					break;

				case eTV_WARNING:
					++m_stageWarnings;
					printf(ANSI_1SEQUENCE(ANSI_FOREGROUND(ANSI_YELLOW)) "[WARNING] ");
					break;

				case eTV_ERROR:
					++m_stageErrors;
					printf(ANSI_1SEQUENCE(ANSI_FOREGROUND(ANSI_RED)) "[ERROR] ");
					break;

				default:
					printf(ANSI_1SEQUENCE(ANSI_FOREGROUND(ANSI_CYAN)) "[UNKNOWN] ");
					break;
			}

			vprintf(format, args);
			printf(ANSI_1SEQUENCE(ANSI_RESET_ALL) "\n");
		}

		va_end(args);
	}

	//============================================================================

	void CUnitTest::AddStage(const char* name, TestFn function)
	{
		if (m_testStatus == eTS_UNINITIALISED)
		{
			m_tests.push_back(STest(name, function));
		}
	}

	//============================================================================
} // End [namespace test]

//==============================================================================
// [EOF]

