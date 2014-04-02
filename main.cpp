#include "common/stdafx.h"

#if !USE_OPENGL_SUPERBIBLE

#include "base/engine.h"

//==============================================================================

bool g_run = true;

//==============================================================================

bool timerCallback(engine::time::CTimer* pTimer, void* pData)
{
	LOG_ALWAYS(GAME_LOGGER, "timer callback %.2f", (float)(pTimer->GetElapsedTime().GetSeconds()));
	if (pTimer->GetElapsedTime().GetSeconds() >= 5.0)
	{
		g_run = false;
	}

	return g_run;
}

//==============================================================================

int main(int argc, char* argv[])
{
	IGNORE_PARAMETER(argc);
	IGNORE_PARAMETER(argv);

	engine::base::CEngine& myEngine = engine::base::CEngine::Get();
	myEngine.Initialise(argc, argv);
	engine::time::CTime::TTimerPtr myTimer = engine::time::CTime::Get().CreateTimer(0.1f, 1.0f, 1.0f, timerCallback, NULL);
	while (g_run)
	{
		myEngine.Update();
	}

	LOG_ALWAYS(GAME_LOGGER, "All done.");

	return 0;
}

//==============================================================================

#endif // !USE_OPENGL_SUPERBIBLE

// [EOF]
