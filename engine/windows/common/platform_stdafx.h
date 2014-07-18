#if !defined(__PLATFORM_STDAFX_H__)
#define __PLATFORM_STDAFX_H__

//==============================================================================

#include "common/targetver.h"
#include <windows.h>

//==============================================================================

//==============================================================================
// Check for 32 or 64 bit environment
//==============================================================================
#if defined(_WIN32) || defined(_WIN64)
#if defined(_WIN64)
#define ENVIRONMENT64
#define __ENVIRONMENT__ "64 bit"
#else
#define ENVIRONMENT32
#define __ENVIRONMENT__ "32 bit"
#endif // [defined(_WIN64)]
#endif // [defined(_WIN32) || defined(_WIN64)]

//==============================================================================
// Debug break
//==============================================================================
#define DEBUG_BREAK DebugBreak()

//==============================================================================
// Function signature
//==============================================================================
#if defined(__GNUC__)
#define __FUNCTION_SIGNATURE__ __PRETTY_FUNCTION__
#else
#define __FUNCTION_SIGNATURE__ __FUNCSIG__
#endif // defined(__GNUC__)

//==============================================================================
// Macro to generate #pragma's
//==============================================================================
#if defined(__GNUC__)
#define DO_PRAGMA(_token_string_) _Pragma (#_token_string_)
//------------------------------------------------------------------------------
// This macro prints a TODO message during the build process
//------------------------------------------------------------------------------
#define TODO(_message_) DO_PRAGMA(message ("TODO: " #_message_))
#else
#define DO_PRAGMA(_token_string_) __pragma(_token_string_)
//------------------------------------------------------------------------------
// This macro prints a TODO message during the build process
//------------------------------------------------------------------------------
#define TODO(_message_) DO_PRAGMA(message (__FILE__ "(" STRINGIZE(__LINE__) "): TODO: " _message_))
#endif // defined(__GNUC__)

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

/* If we're not using GNU C, elide __attribute__ */
#if !defined(__GNUC__)
#define __attribute__(x)  /*NOTHING*/
#endif // !defined(__GNUC__)

//==============================================================================

#endif // End [!defined(__PLATFORM_STDAFX_H__)]
// [EOF]

