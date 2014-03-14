#if !defined(__PLATFORM_STDAFX_H__)
#define __PLATFORM_STDAFX_H__

//==============================================================================

#include <signal.h>
// Intentional blank line to facilitate side-by-side comparison with platform_stdafx.h

//==============================================================================

//==============================================================================
// Check for 32 or 64 bit environment
//==============================================================================
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
// Debug break
//==============================================================================
#define DEBUG_BREAK raise(SIGTRAP)

//==============================================================================
// Function signature
//==============================================================================
#if defined(__GNUC__)
#define __FUNCTION_SIGNATURE__ __PRETTY_FUNCTION__
#endif

//==============================================================================

#endif // End [!defined(__PLATFORM_STDAFX_H__)]
// [EOF]
