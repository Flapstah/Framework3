#include "common/stdafx.h"

#if defined(__MINGW32__)
#define WINGDIAPI __declspec(dllimport)
#define GLAPI WINGDIAPI
#define GLAPIENTRY APIENTRY
#endif // defined(__MINGW32__)

#include "glew.c"

#if defined(__MINGW32__)
#define GLAPI WINGDIAPI
#define GLAPIENTRY APIENTRY
#endif // defined(__MINGW32__)

//#pragma message "GLAPI = [" STRINGIZE(GLAPI) "]"
//#pragma message "GLAPIENTRY = [" STRINGIZE(GLAPIENTRY) "]"

#include "math3d.cpp"
#include "GLTools.cpp"
#include "GLBatch.cpp"
#include "GLShaderManager.cpp"
#include "GLTriangleBatch.cpp"

