#if USE_OPENGL_SUPERBIBLE

#include "common/stdafx.h"

// 10: Block
// 20: Triangle
// 21: Move
// 22: Bounce
// 30: Primitives
// 31: GeoTest
// 32: Scissor
// 33: Blending
// 34: Smoother
// 40: Move
// 41: Objects
// 42: Orthographic
// 43: Perspective
// 44: ModelViewProjection
// 45: SphereWorld
// 46: SphereWorld2
// 47: SphereWorld3
// 48: SphereWorld4

#define EXAMPLE (40)

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
#else
#error "Unknown example"
#endif // (EXAMPLE == <example id>)

#endif // USE_OPENGL_SUPERBIBLE
