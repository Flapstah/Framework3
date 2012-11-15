#include "common/stdafx.h"

#include "common/itime.h"

//==============================================================================

void DumpArgs(int argc, char* argv[])
{
	printf("\n*** Passed %d arguments:\n", argc);
	for (int i = 0; i < argc; ++i)
	{
		printf("[%d]: [%s]\n", i, argv[i]);
	}
	printf("*** End argument list\n\n");
}

//==============================================================================

void DumpVariableSizes(void)
{
	printf("\n*** Variable sizes ");
#if defined(ENVIRONMENT32)
	printf("(32 bit environment)\n");
#endif // [defined(ENVIRONMENT32)]
#if defined(ENVIRONMENT64)
	printf("(64 bit environment)\n");
#endif // [defined(ENVIRONMENT64)]
#define PRINT_SIZE(_type_) printf(#_type_ "\t: %u\n", static_cast<uint32>(sizeof(_type_)))
	PRINT_SIZE(int8);
	PRINT_SIZE(int16);
	PRINT_SIZE(int32);
	PRINT_SIZE(int64);
	PRINT_SIZE(uint8);
	PRINT_SIZE(uint16);
	PRINT_SIZE(uint32);
	PRINT_SIZE(uint64);
	PRINT_SIZE(bool);
	PRINT_SIZE(float);
	PRINT_SIZE(double);
	PRINT_SIZE(size_t);
#undef PRINT_SIZE
	printf("*** End variable sizes\n\n");
}

//==============================================================================

int main(int argc, char* argv[])
{
//	IGNORE_PARAMETER(argc);
//	IGNORE_PARAMETER(argv);
	DumpArgs(argc, argv);
	DumpVariableSizes();

	printf("Test getting time interface...");
	engine::time::ITime* pTime = engine::time::GetITime();
	printf("[%p]\n");

	printf("Test CTimeValue...\n");
	engine::time::CTimeValue tv1;
	engine::time::CTimeValue tv2(2.0);
	engine::time::CTimeValue tv3(3.0);
	engine::time::CTimeValue tv4(tv2+tv3);
	printf("tv1 = %fs\ntv2 = %fs\ntv3 = %fs\ntv4 = %fs\n", tv1.GetSeconds(), tv2.GetSeconds(), tv3.GetSeconds(), tv4.GetSeconds());

	printf("All done.\n");

	return 0;
}

//==============================================================================

// [EOF]
