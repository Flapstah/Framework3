#include "common/stdafx.h"

#include "common/commandargs.h"

//==============================================================================

namespace engine
{
	//============================================================================

	CCommandArgs* CCommandArgs::m_pThis = NULL;

	//============================================================================

	CCommandArgs::SOption::SOption(const char* pOption, char flag, const char* pHelp, TOptionFn pOptionFuntion)
		: m_pOption(pOption)
		, m_pHelp(pHelp)
		, m_pOptionFuntion(pOptionFuntion)
		, m_flag(flag)
	{
	}

	//============================================================================

	CCommandArgs::SOptionMap::SOptionMap(SOptionMap*& pParent, SOption* pOptions, uint32 count)
		: m_pOptions(pOptions)
		, m_count(count)
	{
		if (pParent == NULL)
		{
			// We're the head of the list
			pParent = this;
		}
		else
		{
			// Add ourself to the option map list
			while (pParent->m_pNext != NULL)
			{
				pParent = pParent->m_pNext;
			}
			pParent->m_pNext = this;
		}
	}

	//============================================================================

	CCommandArgs::CCommandArgs(int argc, const char* const* argv)
		: m_pOptionMap(NULL)
		, m_argv(argv)
		, m_argc(argc)
		, m_state(ePS_UNPARSED)
	{
	}

	//============================================================================

	CCommandArgs::~CCommandArgs(void)
	{
	}

	//============================================================================

	CCommandArgs::EParseState CCommandArgs::Parse(int argc, const char* const* argv)
	{
		static CCommandArgs instance(argc, argv);
		m_pThis = &instance;

		uint32 skipCount = 0;

		if (m_pThis->m_state == ePS_UNPARSED)
		{
			m_pThis->RegisterOptionMap();

			for (uint32 index = 1; index < m_pThis->m_argc; ++index)
			{
				skipCount = 0;

				if (m_pThis->m_argv[index][0] == '-')
				{
					if (m_pThis->m_argv[index][1] == '-')
					{
						index += m_pThis->ParseArgument(m_pThis->m_argv[index]+2, eAT_Option);
					}
					else
					{
						uint32 numFlags = strlen(m_pThis->m_argv[index]);
						for (uint32 flag = 1; flag < numFlags; ++flag)
						{
							index += m_pThis->ParseArgument(m_pThis->m_argv[index]+flag, eAT_Flag);
						}
					}
				}
				else
				{
					m_pThis->UpdateState(m_pThis->ProcessArgument(m_pThis->m_argv[index], skipCount));
					index += skipCount;
				}
			}

			m_pThis->UpdateState(ePS_SUCCESS);
		}

		return m_pThis->m_state;
	}

	//============================================================================

	CCommandArgs::EParseState CCommandArgs::UpdateState(CCommandArgs::EParseState state)
	{
		if ((m_state == ePS_UNPARSED) || (m_state == ePS_SUCCESS))
		{
			m_state = state;
		}

		return m_state;
	}

	//============================================================================

	void CCommandArgs::RegisterOptionMap(void)
	{
		static SOption options[] = {
			SOption("help", 'h', "Displays help", ProcessHelp),
			SOption("config", 'c', "Displays build configuration", ProcessConfig),
			SOption("version", 'v', "Displays version information", ProcessVersion)
		};
		uint32 count = sizeof(options)/sizeof(SOption);
		static SOptionMap optionMap(m_pOptionMap, options, count);
	}

	//============================================================================

	uint32 CCommandArgs::ParseArgument(const char* pArgument, CCommandArgs::EArgumentType type)
	{
		SOptionMap* pOptionMap = m_pOptionMap;
		uint32 skipCount = 0;
		uint32 index = 0;
		bool parsed = false;

		while ((!parsed) && (pOptionMap != NULL))
		{
			const SOption& option = pOptionMap->m_pOptions[index];

			switch (type)
			{
				case eAT_Option:
					if (memcmp(option.m_pOption, pArgument, strlen(option.m_pOption)+1) == 0)
					{
						UpdateState(option.m_pOptionFuntion(skipCount));
						parsed = true;
					}
					break;

				case eAT_Flag:
					if (option.m_flag == *pArgument)
					{
						UpdateState(option.m_pOptionFuntion(skipCount));
						parsed = true;
					}
					break;

				default:
					UpdateState(ePS_UNKNOWN_TYPE);
					parsed = true;
					break;
			}

			if (++index >= pOptionMap->m_count)
			{
				pOptionMap = pOptionMap->m_pNext;
				index = 0;
			}
		}

		return skipCount;
	}

	//============================================================================

	CCommandArgs::EParseState	CCommandArgs::ProcessArgument(const char* pArgument, uint32& skipCount)
	{
		IGNORE_PARAMETER(pArgument);
		IGNORE_PARAMETER(skipCount);
		printf("argument [%s]\n", pArgument);
		return ePS_SUCCESS;
	}

	//============================================================================

	CCommandArgs::EParseState CCommandArgs::ProcessHelp(uint32& skipCount)
	{
		IGNORE_PARAMETER(skipCount);

		SOptionMap* pOptionMap = m_pThis->m_pOptionMap;
		uint32 index = 0;

		printf("Help:\n");

		while (pOptionMap != NULL)
		{
			const SOption& option = pOptionMap->m_pOptions[index];

			if (option.m_pHelp != NULL)
			{
				if ((option.m_pOption != NULL) && (option.m_flag != 0))
				{
					printf("  --%s, -%c\t\t%s\n", pOptionMap->m_pOptions[index].m_pOption, pOptionMap->m_pOptions[index].m_flag, pOptionMap->m_pOptions[index].m_pHelp);
				}
				else if ((option.m_pOption != NULL) && (option.m_flag == 0))
				{
					printf("  --%s\t\t%s\n", pOptionMap->m_pOptions[index].m_pOption, pOptionMap->m_pOptions[index].m_pHelp);
				}
				else if ((option.m_pOption == NULL) && (option.m_flag != 0))
				{
					printf("  -%c\t\t%s\n", pOptionMap->m_pOptions[index].m_flag, pOptionMap->m_pOptions[index].m_pHelp);
				}
			}

			if (++index >= pOptionMap->m_count)
			{
				pOptionMap = pOptionMap->m_pNext;
				index = 0;
			}
		}

		return ePS_REQUEST_EXIT;
	}

	//============================================================================

	CCommandArgs::EParseState CCommandArgs::ProcessConfig(uint32& skipCount)
	{
		IGNORE_PARAMETER(skipCount);
		return ePS_REQUEST_EXIT;
	}

	//============================================================================

	CCommandArgs::EParseState CCommandArgs::ProcessVersion(uint32& skipCount)
	{
		IGNORE_PARAMETER(skipCount);
		printf(__BUILD_SIGNATURE__ "\n");
		return ePS_REQUEST_EXIT;
	}

	//============================================================================
} // End [namespace engine]

//==============================================================================
// EOF


