#include "common/stdafx.h"

#include "base/engine.h"
#include "base/thread.h"
#include "system/console.h"
#include "system/configuration.h"

//==============================================================================

bool g_run = true;

//==============================================================================

class CGame
{
	public:
	CGame(void)
	{
		m_callback = engine::utility::MakeUnaryCallback<CGame, engine::time::CTimer>(*this, &CGame::TimerCallback);
		m_timer = engine::time::CTime::Get().CreateTimer(engine::time::CTimeValue(0.1), 1.0f, engine::time::CTimeValue(1.0), m_callback);
	}

	~CGame(void)
	{
		engine::time::CTime::Get().DestroyTimer(m_timer);
	}

	private:
	engine::utility::CUnaryCallback<CGame, engine::time::CTimer> m_callback;
	engine::time::CTime::TTimerPtr m_timer;

	void TimerCallback(engine::time::CTimer* pTimer)
	{
		double elapsed = pTimer->GetElapsedTime().GetSeconds();
		double frame = pTimer->GetFrameTime().GetSeconds();
		const engine::time::CFPSCalculator* pEngineFPS = engine::base::CEngine::Get().GetFPS();
		const engine::time::CFPSCalculator* pGLFWFPS = engine::base::CEngine::Get().GetGLFW()->GetFPS();
		LOG_ALWAYS(GAME_LOGGER, "timer callback (elapsed %.2f, interval %.2f), engine fps (%.2f fps), display fps (%.2f fps)", elapsed, frame, pEngineFPS->GetAverageFPS(), pGLFWFPS->GetAverageFPS());
		if (elapsed >= 20.0)
		{
			g_run = false;
		}
	}
};

//==============================================================================

int main(int argc, char* argv[])
{
	/*
	enum eSyntaxID
	{
		eSID_LOG = engine::system::CConfiguration::eSID_FIRST_USERID,
	};
	*/

	engine::system::CConfiguration config;
	config.Parse(argc, argv);
	config.Parse("system.cfg");

	engine::base::CEngine& myEngine = engine::base::CEngine::Get();
	myEngine.Initialise(config);

	LOG_ALWAYS(GAME_LOGGER, "Start...");

	engine::glfw::SConfiguration glfwConfiguration;

	uint32 display_width = config.GetValue("display_width", DEFAULT_WINDOW_WIDTH);
	uint32 display_height = config.GetValue("display_height", DEFAULT_WINDOW_HEIGHT);
	bool display_fullScreen = config.GetValue("display_fullscreen", DEFAULT_FULL_SCREEN);
	glfwConfiguration.m_desiredFrameRate = config.GetValue("display_framerate", DEFAULT_FRAMERATE);
	glfwConfiguration.m_realtime = config.GetValue("application_realtime", DEFAULT_APPLICATION_REALTIME);
	glfwConfiguration.m_vsync = config.GetValue("display_vsync", DEFAULT_DISPLAY_VSYNC);

	engine::glfw::CGLFW* pGLFW = myEngine.GetGLFW();
	pGLFW->Initialise(glfwConfiguration);
	pGLFW->OpenDisplay(display_width, display_height, DEFAULT_WINDOW_TITLE, display_fullScreen);

	CGame* pGame = new CGame();
	engine::base::CThread t;
	while (g_run)
	{
		engine::time::CTimeValue tick = myEngine.Update();
		g_run &= (tick != engine::time::INVALID_TIME);
	}
	delete pGame;

	/*
	engine::system::CConsole::TIVariablePtr plog_level = myEngine.GetConsole()->FindVariable("log_level");
	if (plog_level != NULL)
	{
		LOG_ALWAYS(GAME_LOGGER, "log_level = %" PRId64, plog_level->GetInteger());
	}
	*/

	LOG_ALWAYS(GAME_LOGGER, "All done.");

	myEngine.Uninitialise(); // Not strictly needed as will be called when engine destructed
	return 0;
}

//==============================================================================
// [EOF]


