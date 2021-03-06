// stdafx.h : include file for standard system include files,
// or project specific include files that are used frequently, but
// are changed infrequently
//

#pragma once

//==============================================================================

#include "common/platform_stdafx.h"

//==============================================================================
// DEBUG and RELEASE macros are defined by CMakeLists.txt, depending on build
//==============================================================================

#include <cstdio>
#include <cstdlib>
#include <cstdarg>

//==============================================================================
// TODO: reference additional headers your program requires here
//#include <assert.h>
#include <time.h>
#include <math.h>

#include <boost/static_assert.hpp>

#include "common/config.h"
#include "common/macros.h"
#include "common/types.h"

#include "system/log.h"

#include "utility/ansi.h"
#include "utility/callback.h"
#include "utility/compiletimestringhash.h"
#include "utility/debug.h"
#include "utility/runtimestringhash.h"
#include "utility/stringutils.h"

//==============================================================================
// [EOF]

