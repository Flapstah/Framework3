#include "common/stdafx.h"

#if !USE_OPENGL_SUPERBIBLE

#include "base/engine.h"
#include "system/console.h"
#include "system/configuration.h"

//==============================================================================

bool g_run = true;

//==============================================================================

bool timerCallback(engine::time::CTimer* pTimer, void* pData)
{
	IGNORE_PARAMETER(pData);

	double elapsed = pTimer->GetElapsedTime().GetSeconds();
	LOG_ALWAYS(GAME_LOGGER, "timer callback %.2f (%.2ffps)", (float)(elapsed), engine::base::CEngine::Get().GetAverageFPS());
	if (elapsed >= 5.0)
	{
		g_run = false;
	}

	return g_run;
}

//==============================================================================

int main(int argc, char* argv[])
{
	/*
	enum eSyntaxID
	{
		eSID_LOG = engine::system::CConfiguration::eSID_FIRST_USERID,
		eSID_ROOT,
	};
	*/

	engine::system::CConfiguration config;
	config.Parse(argc, argv);
	config.Parse("system.cfg");

	engine::base::CEngine& myEngine = engine::base::CEngine::Get();
	myEngine.Initialise(config);

	LOG_ALWAYS(GAME_LOGGER, "Start...");

	engine::video::CDisplay* pDisplay = myEngine.GetDisplay();
	pDisplay->Initialise(1024,576,"Test",false);
	engine::time::CTime::TTimerPtr myTimer = engine::time::CTime::Get().CreateTimer(engine::time::CTimeValue(0.1), 1.0f, engine::time::CTimeValue(1.0), timerCallback, NULL);
	while (g_run)
	{
		myEngine.Update();
		g_run &= pDisplay->Update();
		engine::time::CTime::Sleep(10000);
	}
	engine::time::CTime::Get().DestroyTimer(myTimer);

	/*
	engine::system::CConsole::TIVariablePtr plog_level = myEngine.GetConsole()->FindVariable("log_level");
	if (plog_level != NULL)
	{
		LOG_ALWAYS(GAME_LOGGER, "log_level = %" PRId64, plog_level->GetInteger());
	}
	*/

	pDisplay->Uninitialise();
	LOG_ALWAYS(GAME_LOGGER, "All done.");

	myEngine.Uninitialise(); // Not strictly needed as will be called when engine destructed
	return 0;
}

//==============================================================================

#endif // !USE_OPENGL_SUPERBIBLE

// [EOF]
