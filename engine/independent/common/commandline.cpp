#include "common/stdafx.h"

#include "common/commandline.h"
//#include "common/console.h"
#include "common/log.h"
#include <vector>

//==============================================================================

namespace engine
{
	//============================================================================
	// Create custom log for the command line
	//============================================================================
	static CLog g_log(ENGINE_LOGGER, "CommandLine");

	//============================================================================

	CCommandLine::CCommandLine(uint32 argc, const char* const* argv, CConsole& console)
	{
		std::vector<const char*> preArgs;
		std::vector<const char*> args;
		std::vector<const char*> postArgs;

		preArgs.reserve(argc);
		args.reserve(argc);
		postArgs.reserve(argc);

		// Skip the executable name
		for (uint32 index = 1; index < argc; ++index)
		{
			// Sort args into pre/normal/post
			switch (argv[index][0])
			{
				case '-':
					preArgs.push_back(argv[index]+1);
					break;

				case '+':
					postArgs.push_back(argv[index]+1);
					break;

				default:
					args.push_back(argv[index]);
					break;
			}
		}

		// Append normal args to pre args array
		preArgs.insert(preArgs.end(), args.begin(), args.end());
		// Append post args to pre/normal args array
		preArgs.insert(preArgs.end(), postArgs.begin(), postArgs.end());

		for (std::vector<const char*>::iterator it = preArgs.begin(); it != preArgs.end(); ++ it)
		{
			LOG_ALWAYS(g_log, "%s", *it);
		}
	}

	//============================================================================

	CCommandLine::~CCommandLine(void)
	{
	}

	//============================================================================

} // End [namespace engine]

//==============================================================================
// EOF


