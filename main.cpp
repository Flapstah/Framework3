#include "common/stdafx.h"

#if !USE_OPENGL_SUPERBIBLE

#include "common/log.h"

//==============================================================================

int main(int argc, char* argv[])
{
	IGNORE_PARAMETER(argc);
	IGNORE_PARAMETER(argv);

	LOG_ALWAYS(GAME_LOGGER, "All done.");

	return 0;
}

//==============================================================================

#endif // !USE_OPENGL_SUPERBIBLE

// [EOF]
