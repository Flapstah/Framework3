#if !defined(__PLATFORM_STDAFX_H__)
#define __PLATFORM_STDAFX_H__

//==============================================================================

#include <signal.h>

//==============================================================================

#define DEBUG_BREAK raise(SIGTRAP)

// Check for 32 or 64 bit environment
// Check GCC
#if defined(__GNUC__)
#if defined(__x86_64__) || defined(__ppc64__)
#define ENVIRONMENT64
#define __ENVIRONMENT__ "64 bit"
#else
#define ENVIRONMENT32
#define __ENVIRONMENT__ "32 bit"
#endif // [defined(__x84_64__) || defined(__ppc64__)]
#endif // [defined(__GNUC__)]

//==============================================================================

#endif // End [!defined(__PLATFORM_STDAFX_H__)]
// [EOF]
