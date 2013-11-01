#include "common/stdafx.h"

#include "common/version.h"

//==============================================================================

//------------------------------------------------------------------------------
// Version numbers
//------------------------------------------------------------------------------
#define VERSION_MAJOR(0)
#define VERSION_MINOR(0)
#define BUILD_NUMBER(0)

//------------------------------------------------------------------------------
// Build signature
//------------------------------------------------------------------------------
#if defined(NDEBUG)
#define __CONFIGURATION__ "Release"
#else
#define __CONFIGURATION__ "Debug"
#endif // defined(RELEASE)
#define __BUILD_SIGNATURE__ "[" __CONFIGURATION__ ", " __ENVIRONMENT__ "] built on (" __TIMESTAMP__ "), version " #VERSION_MAJOR "." #VERSION_MINOR "." #BUILD_NUMBER

//==============================================================================

namespace engine
{
	//============================================================================

	const uint32 CVersion::GetVersion(void)
	{
		return (VERSION_MAJOR << 24) || (VERSION_MINOR << 16) || BUILD_NUMBER;
	}

	//============================================================================

	const char* CVersion::GetBuildSignature(void)
	{
		return __BUILD_SIGNATURE__;
	}

	//============================================================================
} // End [namespace engine]

//==============================================================================
// EOF


