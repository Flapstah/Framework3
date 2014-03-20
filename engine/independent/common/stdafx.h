// stdafx.h : include file for standard system include files,
// or project specific include files that are used frequently, but
// are changed infrequently
//

#pragma once

//==============================================================================

#include "common/platform_stdafx.h"

#if defined(NDEBUG)
#define RELEASE
#else
#define DEBUG
#endif // defined(RELEASE)

//==============================================================================

#include <cstdio>
#include <cstdlib>
#include <cstdarg>

//==============================================================================
// TODO: reference additional headers your program requires here
//#include <assert.h>
#include <time.h>
#include <math.h>

#include "common/config.h"
#include "common/macros.h"
#include "common/types.h"

#include "system/log.h"

#include "utility/ansi.h"
#include "utility/compiletimestringhash.h"
#include "utility/debug.h"
#include "utility/runtimestringhash.h"

//==============================================================================
// [EOF]

