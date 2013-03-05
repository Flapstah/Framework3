#include "common/stdafx.h"

// 0: Block
// 1: Triangle
// 2: Move
// 3: Bounce
// 4: Primitives
// 5: GeoTest
// 6: Scissor
// 7: Blending
// 8: Smoother
// 9: Objects
// 10: Orthographic
// 11: Perspective
// 12: ModelViewProjection
// 13: SphereWorld
// 14: SphereWorld2
// 15: SphereWorld3
// 16: SphereWorld4
#define EXAMPLE (16)

#include "../GLTools/src/openglsuperbible_uber.cpp"

#if (EXAMPLE == 0)
#include "Block/Block.cpp"
#elif (EXAMPLE == 1)
#include "Triangle/Triangle.cpp"
#elif (EXAMPLE == 2)
#include "Move/Move.cpp"
#elif (EXAMPLE == 3)
#include "Bounce/Bounce.cpp"
#elif (EXAMPLE == 4)
#include "Primitives/Primitives.cpp"
#elif (EXAMPLE == 5)
#include "GeoTest/GeoTest.cpp"
#elif (EXAMPLE == 6)
#include "Scissor/Scissor.cpp"
#elif (EXAMPLE == 7)
#include "Blending/Blending.cpp"
#elif (EXAMPLE == 8)
#include "Smoother/Smoother.cpp"
#elif (EXAMPLE == 9)
#include "Objects/Objects.cpp"
#elif (EXAMPLE == 10)
#include "Orthographic/Orthographic.cpp"
#elif (EXAMPLE == 11)
#include "Perspective/Perspective.cpp"
#elif (EXAMPLE == 12)
#include "ModelViewProjection/ModelViewProjection.cpp"
#elif (EXAMPLE == 13)
#include "SphereWorld/SphereWorld.cpp"
#elif (EXAMPLE == 14)
#include "SphereWorld2/SphereWorld2.cpp"
#elif (EXAMPLE == 15)
#include "SphereWorld3/SphereWorld3.cpp"
#elif (EXAMPLE == 16)
#include "SphereWorld4/SphereWorld4.cpp"
#endif // (EXAMPLE == <example id>)

