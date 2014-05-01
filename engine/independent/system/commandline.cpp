#include "common/stdafx.h"

#include "system/commandline.h"

//==============================================================================

namespace engine
{
	//============================================================================

	namespace system
	{
		//==========================================================================

		CConfiguration::SSyntax::SSyntax(uint32 id, const char* name, uint32 flags, CConfiguration::SSyntax::CustomArgParsing pParseFn /* = NULL */)
			: m_ID(id)
			, m_flags(flags)
			, m_name(name)
			, m_pParseFn(pParseFn)
		{
		}

		CConfiguration::SParsedItem::SParsedItem(uint32 id, uint32 flags)
			: m_ID(id)
			, m_flags(flags)
		{
		}

		bool CConfiguration::SParsedItem::PushArg(const char* arg)
		{
			m_argv.push_back(arg);
		}

		//==========================================================================

		CConfiguration::CConfiguration(uint32 argc, const char* const* argv)
		{
			m_parsed.reserve(argc);

			std::vector<SItem> preArgs;
			std::vector<SItem> args;
			std::vector<SItem> postArgs;

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
				//LOG_ALWAYS(m_log, "%s", *it);
			}
		}

		//============================================================================

		CConfiguration::~CConfiguration(void)
		{
		}

		//==========================================================================
	} // End [namespace system]

	//============================================================================
} // End [namespace engine]

//==============================================================================
// EOF


