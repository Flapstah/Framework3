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

	LOG_ALWAYS(GAME_LOGGER, "timer callback %.2f (%.2ffps)", (float)(pTimer->GetElapsedTime().GetSeconds()), engine::base::CEngine::Get().GetAverageFPS());
	if (pTimer->GetElapsedTime().GetSeconds() >= 5.0)
	{
		g_run = false;
	}

	return g_run;
}

//==============================================================================

int main(int argc, char* argv[])
{
	LOG_ALWAYS(GAME_LOGGER, "Start...");

	enum eSyntaxID
	{
		eSID_LOG = engine::system::CConfiguration::eSID_FIRST_USERID,
		eSID_ROOT,
	};

	engine::system::CConfiguration::CSyntax syntax[] = {
		engine::system::CConfiguration::CSyntax("root", 'r', eSID_ROOT, 1, "specify the root path", NULL),
		engine::system::CConfiguration::CSyntax("log", 'l', eSID_LOG, 1, "specify the log file", NULL),
//		engine::system::CConfiguration::CSyntax("xxx", 'x', eSID_LOG, 0, "dummy", NULL),
	};

	engine::system::CConfiguration config(sizeof(syntax)/sizeof(engine::system::CConfiguration::CSyntax), syntax);
	config.Parse(argc, argv);

	engine::base::CEngine& myEngine = engine::base::CEngine::Get();
	myEngine.Initialise(argc, argv);

	engine::time::CTime::TTimerPtr myTimer = engine::time::CTime::Get().CreateTimer(engine::time::CTimeValue(0.1), 1.0f, engine::time::CTimeValue(1.0), timerCallback, NULL);
/*	while (g_run)
	{
		myEngine.Update();
		engine::time::CTime::Sleep(10000);
	}
*/	engine::time::CTime::Get().DestroyTimer(myTimer);

	engine::system::CConsole::TIVariablePtr plog_level = myEngine.GetConsole()->FindVariable("log_level");
	if (plog_level != NULL)
	{
		LOG_ALWAYS(GAME_LOGGER, "log_level = %" PRId64, plog_level->GetInteger());
	}

	LOG_ALWAYS(GAME_LOGGER, "All done.");

	myEngine.Uninitialise(); // Not strictly needed as will be called when engine destructed
	return 0;
}

//==============================================================================

#endif // !USE_OPENGL_SUPERBIBLE

// [EOF]
