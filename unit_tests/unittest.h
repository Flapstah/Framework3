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

#define LOG_STAGE_SUBSTAGE(_stage_, _substage_) pThis->Log(eTV_INFORMATION, COLOUR_PROGRESS "[%d:%d]", _stage_, _substage_);
#define LOG_STAGE_NAME(_name_) pThis->Log(eTV_INFORMATION, COLOUR_TEST_INFO _name_);
#define LOG_STAGE_PARAM(_id_, _param_string_, _param_) pThis->Log(eTV_INFORMATION, "\t\tparameter [%d]:\t" #_param_string_ " is [%g]\n", _id_, _param_);
#define LOG_STAGE_STRING_PARAM(_id_, _param_string_, _param_) pThis->Log(eTV_INFORMATION, "\t\tparameter [%d]:\t" #_param_string_ " is [%s]\n", _id_, _param_);
#define LOG_STAGE_RESULT(_result_) pThis->Log((success == true) ? eTV_INFORMATION : eTV_WARNING, "\t\tresult:\t\t" #_result_ " is [%g]\n\t\t%s[%s]", result, ((success == true) ? COLOUR_SUCCESS : COLOUR_WARNING), ((success == true) ? "PASSED" : "FAILED"));
#define LOG_STAGE_STRING_RESULT(_result_) pThis->Log((success == true) ? eTV_INFORMATION : eTV_WARNING, "\t\tresult:\t\t" #_result_ " is [%s]\n\t\t%s[%s]", result, ((success == true) ? COLOUR_SUCCESS : COLOUR_WARNING), ((success == true) ? "PASSED" : "FAILED"));

// Single parameter named test
#define TEST1_NAMED(_name_, _test_, _param1_, _result_) \
	{ \
		bool success = (_test_); \
		double param1 = static_cast<double>(_param1_); \
		double result = static_cast<double>(_result_); \
		pThis->SupressNewline(true); \
		LOG_STAGE_SUBSTAGE(pThis->GetStage(), pThis->NextSubstage()); \
		LOG_STAGE_NAME("\ttest:\t\t" _name_ "\n"); \
		LOG_STAGE_PARAM(1, #_param1_, param1); \
		pThis->SupressNewline(false); \
		LOG_STAGE_RESULT(_result_); \
	}

/*
#define TEST1_NAMED_STRING(_name_, _test_, _param1_, _result_) \
	{ \
		bool success = (_test_); \
		double param1 = static_cast<double>(_param1_); \
		double result = static_cast<double>(_result_); \
		pThis->SupressNewline(true); \
		LOG_STAGE_SUBSTAGE(pThis->GetStage(), pThis->NextSubstage()); \
		LOG_STAGE_NAME("\ttest:\t\t" _name_ "\n"); \
		LOG_STAGE_STRING_PARAM(1, #_param1_, param1); \
		pThis->SupressNewline(false); \
		LOG_STAGE_STRING_RESULT(_result_); \
	}
*/
#define TEST1_NAMED_STRING(_name_, _test_, _param1_, _result_) \
	{ \
		bool success = (_test_); \
		const char* param1 = (_param1_); \
		const char* result = (_result_); \
		pThis->SupressNewline(true); \
		LOG_STAGE_SUBSTAGE(pThis->GetStage(), pThis->NextSubstage()); \
		LOG_STAGE_NAME("\ttest:\t\t" _name_ "\n"); \
		LOG_STAGE_STRING_PARAM(1, #_param1_, param1); \
		pThis->SupressNewline(false); \
		LOG_STAGE_STRING_RESULT(_result_); \
	}

// Double parameter named test
#define TEST2_NAMED(_name_, _test_, _param1_, _param2_, _result_) \
	{ \
		bool success = (_test_); \
		double param1 = static_cast<double>(_param1_); \
		double param2 = static_cast<double>(_param2_); \
		double result = static_cast<double>(_result_); \
		pThis->SupressNewline(true); \
		LOG_STAGE_SUBSTAGE(pThis->GetStage(), pThis->NextSubstage()); \
		LOG_STAGE_NAME("\ttest:\t\t" _name_ "\n"); \
		LOG_STAGE_PARAM(1, #_param1_, param1); \
		LOG_STAGE_PARAM(2, #_param2_, param2); \
		pThis->SupressNewline(false); \
		LOG_STAGE_RESULT(_result_); \
	}

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
				eSS_SUCCESS			= 0,
				eSS_WARNING			= 1 << 0,	// Set if a warning occured
				eSS_ERROR				= 1 << 1, // Set if an error occured
				eSS_RESULT_MASK = eSS_WARNING | eSS_ERROR,
				eSS_COMPLETE		= 1 << 2	// Set when this stage is complete
			}; // End [enum eStageStatus]

			//========================================================================
			// enum eTestVerbosity
			//========================================================================
			enum eTestVerbosity
			{
				eTV_RESULT			= 0,
				eTV_ERROR,
				eTV_WARNING,
				eTV_INFORMATION
			}; // End [enum eTestVerbosity]

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

										void				AddStage(const char* name, TestFn function, eTestVerbosity verbosity = eTV_RESULT);
										void				Log(eTestVerbosity targetLevel, const char* format, ...) __attribute__((format(printf, 3, 4)));
										
			//========================================================================

		protected:
										uint32			GetStage(void);
										uint32			NextStage(void);
										uint32			GetSubstage(void);
										uint32			NextSubstage(void);

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
			struct STest
			{
				STest(const char* name, TestFn function, eTestVerbosity verbosity) : m_name(name), m_function(function), m_verbosity(verbosity) {}

				string									m_name;
				TestFn									m_function;
				eTestVerbosity					m_verbosity;
			};

			vector<STest>							m_tests;
			vector<STest>::iterator		m_testIterator;
			CTimeValue								m_timeStarted;
			CTimeValue								m_timeEnded;
			const char*								m_name;
			uint32										m_stageWarnings;
			uint32										m_stageErrors;
			uint32										m_totalWarnings;
			uint32										m_totalErrors;
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

