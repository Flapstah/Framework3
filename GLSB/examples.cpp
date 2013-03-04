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
#define EXAMPLE (9)

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
#endif // (EXAMPLE == <example id>)

