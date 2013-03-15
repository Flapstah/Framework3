#include "common/stdafx.h"

#include "common/commandargs.h"

//==============================================================================

namespace engine
{
	//============================================================================

	CCommandArgs::CCommandArgs(int argc, const char* const* argv)
		: m_argc(argc)
		, m_argv(argv)
		, m_shouldExit(false)
	{
		for (int index = 0; index < m_argc; ++index)
		{
			if (m_argv[index][0] == '-')
			{
				if (m_argv[index][1] == '-')
				{
					index += ParseArgumentAsCommand(m_argv[index]+2);
				}
				else
				{
					index += ParseArgumentAsFlags(m_argv[index]+1);
				}
			}
		}
	}

	//============================================================================

	CCommandArgs::~CCommandArgs(void)
	{
	}

	//============================================================================

	uint32 CCommandArgs::ParseArgumentAsCommand(const char* argument)
	{
		uint32 skipCount = 0;

		if (strcmp(argument, "help") == 0)
		{
			printf("Help:\n");
			m_shouldExit = ProcessConfig();
		}
		else if (strcmp(argument, "config") == 0)
		{
			printf("Build configuration:\n");
			m_shouldExit = ProcessConfig();
		}
		else if (strcmp(argument, "version") == 0)
		{
			printf("Version:\n");
			m_shouldExit = ProcessVersion();
		}
		else
		{
			printf("Unknown argument [%s]\n", argument);
			m_shouldExit = true;
		}

		return skipCount;
	}

	//============================================================================

	uint32 CCommandArgs::ParseArgumentAsFlags(const char* flags)
	{
		uint32 skipCount = 0;
		uint32 length = strlen(flags);

		for (uint32 flag = 0; flag < length; ++flag)
		{
			switch (flags[flag])
			{
				case 'h':
					printf("Help:\n");
					m_shouldExit = ProcessHelp();
					break;

				case 'c':
					printf("Build configuration:\n");
					m_shouldExit = ProcessConfig();
					break;

				case 'v':
					printf("Version:\n");
					m_shouldExit = ProcessVersion();
					break;

				default:
					printf("Unknown flag [%c]\n", flags[flag]);
					m_shouldExit = true;
					break;
			}
		}

		return skipCount;
	}

	//============================================================================

	bool CCommandArgs::ProcessHelp(void)
	{
		return true;
	}

	//============================================================================

	bool CCommandArgs::ProcessConfig(void)
	{
		return true;
	}

	//============================================================================

	bool CCommandArgs::ProcessVersion(void)
	{
		printf(__BUILD_SIGNATURE__ "\n");
		return true;
	}

	//============================================================================
} // End [namespace engine]

//==============================================================================
// EOF


