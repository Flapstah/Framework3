#include "common/stdafx.h"

// 0: Block
// 1: Triangle
// 2: Move
// 3: Bounce
// 4: Primitives
#define EXAMPLE (4)

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
#endif // (EXAMPLE == <example id>)

