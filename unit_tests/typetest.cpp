#include "common/stdafx.h"

#include "typetest.h"

//==============================================================================

namespace test
{
	//============================================================================

	CTypeTest::CTypeTest(void)
		: CUnitTest("Type")
	{
		Initialise();
	}

	//============================================================================

	CTypeTest::~CTypeTest(void)
	{
		Uninitialise();
	}

	//============================================================================

	bool CTypeTest::Initialise(void)
	{
		AddStage("Sizes", SizeTest, eTV_TERSE);

		return CUnitTest::Initialise();
	}

	//============================================================================

	uint32 CTypeTest::SizeTest(CUnitTest* pParent)
	{
		CTypeTest* pThis = static_cast<CTypeTest*>(pParent);

		if (pThis->m_testStatus == eTS_RUNNING)
		{
#if defined(ENVIRONMENT32)
			pThis->Log(eTV_VERBOSE, "(32 bit environment)");
#endif // [defined(ENVIRONMENT32)]
#if defined(ENVIRONMENT64)
			pThis->Log(eTV_VERBOSE, "(64 bit environment)");
#endif // [defined(ENVIRONMENT64)]
#define LOG_SIZE(_type_) pThis->Log(eTV_VERBOSE, #_type_ "\t: %u", static_cast<uint32>(sizeof(_type_)))
			LOG_SIZE(int8);
			LOG_SIZE(int16);
			LOG_SIZE(int32);
			LOG_SIZE(int64);
			LOG_SIZE(uint8);
			LOG_SIZE(uint16);
			LOG_SIZE(uint32);
			LOG_SIZE(uint64);
			LOG_SIZE(bool);
			LOG_SIZE(float);
			LOG_SIZE(double);
			LOG_SIZE(size_t);
			LOG_SIZE(void*);
#undef LOG_SIZE
		}

		return eSS_PASS | eSS_COMPLETE;
	}

	//============================================================================
} // End [namespace test]

//==============================================================================
// [EOF]

