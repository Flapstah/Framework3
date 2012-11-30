#if !defined(__UNITTEST_H__)
#define __UNITTEST_H__

//==============================================================================

#include <string>
#include <vector>

#include "common/itime.h"

using namespace std;
using namespace engine::time;

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

			virtual				bool				Initialise(eTestVerbosity verbosity) = 0;
			virtual	const	CTimeValue&	Start(void);
			virtual				eTestStatus	Update(void);
			virtual	const	CTimeValue&	End(void);
			virtual				void				Uninitialise(void);

										void				Log(eTestVerbosity targetLevel, const char* format, ...);

										void				AddStage(const char* name, TestFn function);
										
			//========================================================================

		private:
			struct STest
			{
				STest(const char* name, TestFn function) : m_name(name), m_function(function) {}

				string									m_name;
				TestFn									m_function;
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

		protected:
			ITime*										m_pTime;
			uint32										m_stage;
			uint32										m_subStage;
			eTestStatus								m_testStatus;
			eStageStatus							m_stageStatus;
			eTestVerbosity						m_verbosity;
	}; // End [class CUnitTest]

	//============================================================================
} // End [namespace test]

//==============================================================================
#endif // !defined(__UNITTEST_H__)
// [EOF]

