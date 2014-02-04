#if !defined(__PLATFORM_STDAFX_H__)
#define __PLATFORM_STDAFX_H__

//==============================================================================

#include "common/targetver.h"
#include <windows.h>

//==============================================================================
// Microsoft elected to use macros instead of functions for these... so you
// can't use them in your own code...
//==============================================================================
#if defined(GetCurrentTime)
#undef GetCurrentTime
#endif // defined(GetCurrentTime)

#if defined(min)
#undef min
#endif // defined(min)

#if defined(max)
#undef max
#endif // defined(min)

#if defined (_MSC_VER)
//==============================================================================
// Microsoft are missing 4 functions from stdlib.h, required by C++11 and C11
// standards: strtof, strtold, strtoll, strtoull
// Using #defines as a workaround for strtoll, stroull and strtold
//==============================================================================
#define strtoll _strtoi64
#define strtoull _strtoui64
#define strtold std::stold
//==============================================================================
// Microsoft don't have snprintf (C99 and C++11), but do have a workaround
//==============================================================================
#define snprintf _snprintf
#endif // defined (_MSC_VER)

#define DEBUG_BREAK DebugBreak()

// Check for 32 or 64 bit environment
#if defined(_WIN32) || defined(_WIN64)
#if defined(_WIN64)
#define ENVIRONMENT64
#define __ENVIRONMENT__ "64 bit"
#else
#define ENVIRONMENT32
#define __ENVIRONMENT__ "32 bit"
#endif // [defined(_WIN64)]
#endif // [defined(_WIN32) || defined(_WIN64)]

/* If we're not using GNU C, elide __attribute__ */
#if !defined(__GNUC__)
#define __attribute__(x)  /*NOTHING*/
#endif // !defined(__GNUC__)

//==============================================================================

#endif // End [!defined(__PLATFORM_STDAFX_H__)]
// [EOF]

