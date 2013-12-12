#include "common/stdafx.h"

#include "common/commandline.h"
//#include "common/console.h"
#include <vector>

//==============================================================================

namespace engine
{
	//============================================================================

	CCommandLine::CCommandLine(int argc, char* argv[], CConsole& console)
	{
		std::vector<const char*> preArgs;
		std::vector<const char*> args;
		std::vector<const char*> postArgs;

		preArgs.reserve(argc);
		args.reserve(argc);
		postArgs.reserve(argc);

		// Skip the executable name
		for (int32 index = 1; index < argc; ++index)
		{
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

		preArgs.insert(preArgs.end(), args.begin(), args.end());
		preArgs.insert(preArgs.end(), postArgs.begin(), postArgs.end());

		for (std::vector<const char*>::iterator it = preArgs.begin(); it != preArgs.end(); ++ it)
		{
			printf("%s\n", *it);
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


