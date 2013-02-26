#include "common/stdafx.h"

// 0: Block
// 1: Triangle
// 2: Move
#define EXAMPLE (2)

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

#if (EXAMPLE == 0)
#include "../../GLSB/Block/Block.cpp"
#elif (EXAMPLE == 1)
#include "../../GLSB/Triangle/Triangle.cpp"
#elif (EXAMPLE == 2)
#include "../../GLSB/Move/Move.cpp"
#endif // (EXAMPLE == <example id>)

