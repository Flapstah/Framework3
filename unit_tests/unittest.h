#if !defined(__UNITTEST_H__)
#define __UNITTEST_H__

//==============================================================================

#include <string>
#include <vector>

#include "common/itime.h"

using namespace std;
using namespace engine::time;

//==============================================================================
// Helper macros for ANSI colours
//==============================================================================

#define COLOUR_SUCCESS ANSI_2SEQUENCE(ANSI_BRIGHT, ANSI_FOREGROUND(ANSI_GREEN))
#define COLOUR_WARNING ANSI_2SEQUENCE(ANSI_BRIGHT, ANSI_FOREGROUND(ANSI_YELLOW))
#define COLOUR_ERROR ANSI_2SEQUENCE(ANSI_BRIGHT, ANSI_FOREGROUND(ANSI_RED))
#define COLOUR_INFO ANSI_1SEQUENCE(ANSI_FOREGROUND(ANSI_DEFAULT_COLOUR))
#define COLOUR_PROGRESS ANSI_2SEQUENCE(ANSI_BRIGHT, ANSI_FOREGROUND(ANSI_CYAN))
#define COLOUR_TEST_INFO ANSI_2SEQUENCE(ANSI_BRIGHT, ANSI_FOREGROUND(ANSI_MAGENTA))
#define COLOUR_DEFAULT ANSI_1SEQUENCE(ANSI_FOREGROUND(ANSI_DEFAULT_COLOUR))
#define COLOUR_RESET ANSI_1SEQUENCE(ANSI_RESET_ALL)

//==============================================================================
// Helper macros (for usage case, see timetest.cpp)
//==============================================================================

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
			// enum eTestVerbosity
			//========================================================================
			enum eTestVerbosity
			{
				eTV_NONE			= 0,
				eTV_ERROR,
				eTV_TERSE,
				eTV_VERBOSE
			}; // End [enum eTestVerbosity]

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

										void				AddStage(const char* name, TestFn function, eTestVerbosity verbosity = eTV_TERSE);
										void				Test(const char* description, bool test, const char* failureMessage, int32 testType = eTT_Stage);
/* need? */					void				Information(const char* description, int32 testType);
										
			//========================================================================

		protected:
																// N.B. A member function has a hidden 1st parameter (the
																// hidden 'this') pointer, so 'format' is actually the 3rd
																// parameter, and the variadic part is the 4th parameter
										void				Log(eTestVerbosity targetLevel, const char* format, ...) __attribute__((format(printf, 3, 4)));
										
										uint32			GetStage(void);
										uint32			GetSubstage(void);

										bool				IsEqual(double param1, double param2, double epsilon = 0.0);

										bool				SupressNewline(bool supress);

			//========================================================================

		private:
							const	char*				TimeStamp(char* const buffer, uint32 size);
										void				ResetStage(void);
										void				ResetSubstage(void);


			//========================================================================

		protected:
			ITime*										m_pTime;
			eTestStatus								m_testStatus;
			eStageStatus							m_stageStatus;
			eTestVerbosity						m_verbosity;

			//========================================================================

		private:
			//========================================================================
			// STest should be a function containing one or more test stages
			//========================================================================
			struct STest
			{
				STest(const char* name, TestFn function, eTestVerbosity verbosity) : m_name(name), m_function(function), m_verbosity(verbosity) {}

				string									m_name;
				TestFn									m_function;
				eTestVerbosity					m_verbosity;
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
			bool											m_supressNewline;
	}; // End [class CUnitTest]

	//============================================================================
} // End [namespace test]

//==============================================================================
#endif // !defined(__UNITTEST_H__)
// [EOF]

