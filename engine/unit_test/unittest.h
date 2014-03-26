#if !defined(__UNITTEST_H__)
#define __UNITTEST_H__

//==============================================================================

#include <string>
#include <vector>

#include "time/itime.h"

using namespace std;
using namespace engine;
using namespace engine::time;

//==============================================================================
// Helper macros for ANSI colours
//==============================================================================

#define COLOUR_SUCCESS ANSI_2SEQUENCE(ANSI_BRIGHT, ANSI_FOREGROUND(ANSI_GREEN))
#define COLOUR_WARNING ANSI_2SEQUENCE(ANSI_BRIGHT, ANSI_FOREGROUND(ANSI_YELLOW))
#define COLOUR_ERROR ANSI_2SEQUENCE(ANSI_BRIGHT, ANSI_FOREGROUND(ANSI_RED))
#define COLOUR_INFO ANSI_2SEQUENCE(ANSI_BRIGHT, ANSI_FOREGROUND(ANSI_DEFAULT_COLOUR))
#define COLOUR_PROGRESS ANSI_2SEQUENCE(ANSI_BRIGHT, ANSI_FOREGROUND(ANSI_CYAN))
#define COLOUR_TEST_INFO ANSI_2SEQUENCE(ANSI_BRIGHT, ANSI_FOREGROUND(ANSI_MAGENTA))
#define COLOUR_DEFAULT ANSI_2SEQUENCE(ANSI_BRIGHT, ANSI_FOREGROUND(ANSI_DEFAULT_COLOUR))
#define COLOUR_RESET ANSI_1SEQUENCE(ANSI_RESET_ALL)

//==============================================================================
// Helper macros
//==============================================================================
#define UNIT_TEST(_test_) _test_.Start(); while (_test_.Update() == test::CUnitTest::eTS_RUNNING); _test_.End();

namespace test
{
	//============================================================================
	// CUnitTest
	//============================================================================
	class CUnitTest
	{
		public:
			//========================================================================
			// enum eTestStatus
			//========================================================================
			enum eTestStatus
			{
				eTS_UNINITIALISED	= 0,
				eTS_INITIALISED,
				eTS_RUNNING,
				eTS_FINISHED,
				eTS_ABORTED
			}; // End [enum eTestStatus]

			//========================================================================
			// enum eStageStatus
			//========================================================================
			enum eStageStatus
			{
				eSS_PASS			= 0,			// Default stage status
				eSS_FAIL			= BIT(0),	// Set if any test in a stage fails
				eSS_COMPLETE	= BIT(1)	// Set when this stage is complete
			}; // End [enum eStageStatus]

			//========================================================================
			// enum eTestType
			//========================================================================
			enum eTestType
			{
				eTT_Stage,
				eTT_SubStage,
				eTT_Information
			}; // End [enum eTestType]

			//========================================================================

			typedef uint32 (*TestFn)(CUnitTest* pParent);

			//========================================================================

																CUnitTest(const char* name);
			virtual										~CUnitTest(void);

			virtual				bool				Initialise(void) = 0;
			virtual	const	CTimeValue&	Start(void);
			virtual				eTestStatus	Update(void);
			virtual	const	CTimeValue&	End(void);
			virtual				void				Uninitialise(void);

										void				AddStage(const char* name, TestFn function);
										void				Test(const char* description, bool test, const char* failureMessage, int32 testType = eTT_Stage);
										
			//========================================================================

		protected:
										uint32			GetStage(void);
										uint32			GetSubstage(void);

										bool				IsEqual(double param1, double param2, double epsilon = 0.0);

			//========================================================================

		private:
										void				ResetStage(void);
										void				ResetSubstage(void);

			//========================================================================

		protected:
			ITime*										m_pTime;
			engine::system::CLog			m_log;
			eTestStatus								m_testStatus;
			eStageStatus							m_stageStatus;

			//========================================================================

		private:
			//========================================================================
			// STest should be a function containing one or more test stages
			//========================================================================
			struct STest
			{
				STest(const char* name, TestFn function) : m_name(name), m_function(function) {}

				string									m_name;
				TestFn									m_function;
			};

			//========================================================================

			vector<STest>							m_tests;
			vector<STest>::iterator		m_testIterator;
			CTimeValue								m_timeStarted;
			CTimeValue								m_timeEnded;
			const char*								m_name;
			uint32										m_errors;
			uint32										m_errorTotal;
			uint32										m_totalTests;
			uint32										m_stage;
			uint32										m_subStage;
	}; // End [class CUnitTest]

	//============================================================================
} // End [namespace test]

//==============================================================================
#endif // !defined(__UNITTEST_H__)
// [EOF]

