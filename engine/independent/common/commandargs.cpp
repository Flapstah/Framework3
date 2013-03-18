#include "common/stdafx.h"

#include "common/commandargs.h"

//==============================================================================

namespace engine
{
	//============================================================================

	CCommandArgs::SOption::SOption(const char* pOption, char flag, const char* pHelp, TOptionFn pOptionFuntion)
		: m_pOption(pOption)
		, m_pHelp(pHelp)
		, m_pOptionFuntion(pOptionFuntion)
		, m_flag(flag)
	{
	}

	//============================================================================

	CCommandArgs::SOptionMap::SOptionMap(SOptionMap* pBase, SOption* pOptions, uint32 count)
		: m_pOptions(pOptions)
		, m_count(count)
	{
		if (pBase != NULL)
		{
			SOptionMap* pParent = pBase;
			while (pParent->m_pNext != NULL)
			{
				pParent = pParent->m_pNext;
			}
			pParent->m_pNext = this;
		}
	}

	//============================================================================

	CCommandArgs::CCommandArgs(int argc, const char* const* argv)
		: m_argv(argv)
		, m_argc(argc)
		, m_shouldExit(false)
	{
	}

	//============================================================================

	CCommandArgs::~CCommandArgs(void)
	{
	}

	//============================================================================

	bool CCommandArgs::Parse(int argc, const char* const* argv)
	{
		static CCommandArgs instance(argc, argv);

		// CCommandArgs::SOption("help", "h", "Displays help", instance.ProcessHelp);

		for (int index = 0; index < instance.m_argc; ++index)
		{
			if (instance.m_argv[index][0] == '-')
			{
				if (instance.m_argv[index][1] == '-')
				{
					index += instance.ParseOption(instance.m_argv[index]+2);
				}
				else
				{
					index += instance.ParseFlags(instance.m_argv[index]+1);
				}
			}
		}

		return instance.m_shouldExit;
	}

	//============================================================================

	uint32 CCommandArgs::ParseOption(const char* argument)
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

	uint32 CCommandArgs::ParseFlags(const char* flags)
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


