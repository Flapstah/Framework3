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
		AddStage("Sizes", SizeTest);

		return CUnitTest::Initialise();
	}

	//============================================================================

	uint32 CTypeTest::SizeTest(CUnitTest* pParent)
	{
		char buffer[64];
		CTypeTest* pThis = static_cast<CTypeTest*>(pParent);
		uint32 status = eSS_PASS;

		if (pThis->m_testStatus == eTS_RUNNING)
		{
			switch (pThis->GetStage())
			{
			case 1:
				sprintf(buffer, __ENVIRONMENT__ " environment");
				pThis->Test(buffer, true, NULL, eTT_SubStage);

#define CREATE_SIZE_MESSAGE(_type_) sprintf(buffer, #_type_ "\t: %u", static_cast<uint32>(sizeof(_type_)))
				CREATE_SIZE_MESSAGE(int8);
				pThis->Test(buffer, true, NULL, eTT_SubStage);
				CREATE_SIZE_MESSAGE(int16);
				pThis->Test(buffer, true, NULL, eTT_SubStage);
				CREATE_SIZE_MESSAGE(int32);
				pThis->Test(buffer, true, NULL, eTT_SubStage);
				CREATE_SIZE_MESSAGE(int64);
				pThis->Test(buffer, true, NULL, eTT_SubStage);
				CREATE_SIZE_MESSAGE(uint8);
				pThis->Test(buffer, true, NULL, eTT_SubStage);
				CREATE_SIZE_MESSAGE(uint16);
				pThis->Test(buffer, true, NULL, eTT_SubStage);
				CREATE_SIZE_MESSAGE(uint32);
				pThis->Test(buffer, true, NULL, eTT_SubStage);
				CREATE_SIZE_MESSAGE(uint64);
				pThis->Test(buffer, true, NULL, eTT_SubStage);
				CREATE_SIZE_MESSAGE(bool);
				pThis->Test(buffer, true, NULL, eTT_SubStage);
				CREATE_SIZE_MESSAGE(float);
				pThis->Test(buffer, true, NULL, eTT_SubStage);
				CREATE_SIZE_MESSAGE(double);
				pThis->Test(buffer, true, NULL, eTT_SubStage);
				CREATE_SIZE_MESSAGE(size_t);
				pThis->Test(buffer, true, NULL, eTT_SubStage);
				CREATE_SIZE_MESSAGE(void*);
				pThis->Test(buffer, true, NULL);
				break;

			default:
				status |= eSS_COMPLETE;
				break;
			}
		}

		return status;
	}

	//============================================================================
} // End [namespace test]

//==============================================================================
// [EOF]

