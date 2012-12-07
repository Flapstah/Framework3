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
		, m_stage(1)
		, m_subStage(1)
		,	m_testStatus(eTS_UNINITIALISED)
		,	m_stageStatus(eSS_SUCCESS)
		,	m_verbosity(eTV_INFORMATION)
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

		const char* colour = ANSI_1SEQUENCE(ANSI_FOREGROUND(ANSI_GREEN));
		if (m_totalWarnings != 0)
		{
			colour = ANSI_1SEQUENCE(ANSI_FOREGROUND(ANSI_YELLOW));
		}
		if (m_totalErrors != 0)
		{
			colour = ANSI_1SEQUENCE(ANSI_FOREGROUND(ANSI_RED));
		}

		Log(eTV_RESULT, "%s[%s] [%s] completed in %s%d days, %02u:%02u:%06.3fs, with %d warnings and %d errors\n", colour, timeBuffer, m_name, (elapsed.GetTicks() < 0) ? "-" : "",  days, hours, minutes, seconds, m_totalWarnings, m_totalErrors);
	}

	//============================================================================

	bool CUnitTest::Initialise(void)
	{
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
				if (m_stage == 1)
				{
					m_verbosity = test.m_verbosity;
					TimeStamp(timeBuffer, sizeof(timeBuffer));
					Log(eTV_RESULT, "[%s] [%s:%s] started", timeBuffer, m_name, test.m_name.c_str());
				}

				uint32 status = test.m_function(this);
				m_subStage = 1;

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

					TimeStamp(timeBuffer, sizeof(timeBuffer));
					Log(eTV_RESULT, "%s[%s] [%s:%s] complete; %d warnings, %d errors\n", colour, timeBuffer, m_name, test.m_name.c_str(), m_stageWarnings, m_stageErrors);

					m_totalWarnings += m_stageWarnings;
					m_totalErrors += m_stageErrors;

					m_stageWarnings = 0;
					m_stageErrors = 0;

					m_stage = 1;

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
} // End [namespace test]

//==============================================================================
// [EOF]

