#if USE_OPENGL_SUPERBIBLE

#include "common/stdafx.h"

// 10: Chapter01/Block
// 20: Chapter02/Triangle
// 21: Chapter02/Move
// 22: Chapter02/Bounce
// 30: Chapter03/Primitives
// 31: Chapter03/GeoTest
// 32: Chapter03/Scissor
// 33: Chapter03/Blending
// 34: Chapter03/Smoother
// 40: Chapter04/Move
// 41: Chapter04/Objects
// 42: Chapter04/Orthographic
// 43: Chapter04/Perspective
// 44: Chapter04/ModelViewProjection
// 45: Chapter04/SphereWorld
// 46: Chapter04/SphereWorld2
// 47: Chapter04/SphereWorld3
// 48: Chapter04/SphereWorld4
// 50: Chapter05/SphereWorld

#define EXAMPLE (50)

#include "../GLTools/src/openglsuperbible_uber.cpp"

#if (EXAMPLE == 10)
#include "Chapter01/Block/Block.cpp"
#elif (EXAMPLE == 20)
#include "Chapter02/Triangle/Triangle.cpp"
#elif (EXAMPLE == 21)
#include "Chapter02/Move/Move.cpp"
#elif (EXAMPLE == 22)
#include "Chapter02/Bounce/Bounce.cpp"
#elif (EXAMPLE == 30)
#include "Chapter03/Primitives/Primitives.cpp"
#elif (EXAMPLE == 31)
#include "Chapter03/GeoTest/GeoTest.cpp"
#elif (EXAMPLE == 32)
#include "Chapter03/Scissor/Scissor.cpp"
#elif (EXAMPLE == 33)
#include "Chapter03/Blending/Blending.cpp"
#elif (EXAMPLE == 34)
#include "Chapter03/Smoother/Smoother.cpp"
#elif (EXAMPLE == 40)
#include "Chapter04/Move/Move.cpp"
#elif (EXAMPLE == 41)
#include "Chapter04/Objects/Objects.cpp"
#elif (EXAMPLE == 42)
#include "Chapter04/Orthographic/Orthographic.cpp"
#elif (EXAMPLE == 43)
#include "Chapter04/Perspective/Perspective.cpp"
#elif (EXAMPLE == 44)
#include "Chapter04/ModelViewProjection/ModelViewProjection.cpp"
#elif (EXAMPLE == 45)
#include "Chapter04/SphereWorld/SphereWorld.cpp"
#elif (EXAMPLE == 46)
#include "Chapter04/SphereWorld2/SphereWorld2.cpp"
#elif (EXAMPLE == 47)
#include "Chapter04/SphereWorld3/SphereWorld3.cpp"
#elif (EXAMPLE == 48)
#include "Chapter04/SphereWorld4/SphereWorld4.cpp"
#elif (EXAMPLE == 50)
#include "Chapter05/SphereWorld/SphereWorld.cpp"
#else
#error "Unknown example"
#endif // (EXAMPLE == <example id>)

#endif // USE_OPENGL_SUPERBIBLE
