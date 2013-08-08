#if !defined(__UNITTEST_H__)
#define __UNITTEST_H__

//==============================================================================

#include <string>
#include <vector>

#include "common/itime.h"

using namespace std;
using namespace engine::time;

//==============================================================================
// Helper macros (for usage case, see timetest.cpp)
//==============================================================================

// Single parameter named test
#define TEST1_NAMED(_name_, _test_, _param1_, _result_) \
	{ \
		bool success = (_test_); \
		double param1 = static_cast<double>(_param1_); \
		double result = static_cast<double>(_result_); \
		pThis->Log((success == true) ? eTV_INFORMATION : eTV_WARNING, "[%d:%d]\ttest:\t\t" _name_ "\n\tparameters:\t%s is [%g]\n\tresult:\t\t%s is [%g]\n\t[%s]", pThis->GetStage(), pThis->NextSubstage(), #_param1_, param1, #_result_, result, ((success == true) ? "PASSED" : "FAILED")); \
	}

// Double parameter named test
#define TEST2_NAMED(_name_, _test_, _param1_, _param2_, _result_) \
	{ \
		bool success = (_test_); \
		double param1 = static_cast<double>(_param1_); \
		double param2 = static_cast<double>(_param2_); \
		double result = static_cast<double>(_result_); \
		pThis->Log((success == true) ? eTV_INFORMATION : eTV_WARNING, "[%d:%d]\ttest:\t\t" _name_ "\n\tparameters:\t%s is [%g], %s is [%g]\n\tresult:\t\t%s is [%g]\n\t[%s]", pThis->GetStage(), pThis->NextSubstage(), #_param1_, param1, #_param2_, param2, #_result_, result, ((success == true) ? "PASSED" : "FAILED")); \
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
	}; // End [class CUnitTest]

	//============================================================================
} // End [namespace test]

//==============================================================================
#endif // !defined(__UNITTEST_H__)
// [EOF]

