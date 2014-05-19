#include "common/stdafx.h"

#include <algorithm>
#include "system/configuration.h"

//==============================================================================

namespace engine
{
	//============================================================================

	namespace system
	{
		//==========================================================================

		CConfiguration::CSyntax::CSyntax(const char* name, char abbreviation, uint32 id, uint32 flags, const char* help, CustomArgParsing pParseFn /* = NULL */)
			: m_name(name)
			, m_help(help)
			, m_pParseFn(pParseFn)
			, m_ID(id)
			, m_flags(flags)
			, m_abbreviation(abbreviation)
		{
		}

		//==========================================================================

		CConfiguration::COption::COption(uint32 id, uint32 flags, TArgumentVec args)
			: m_args(args)
			, m_ID(id)
			, m_flags(flags)
		{
		}

		//==========================================================================

		uint32 CConfiguration::COption::GetArgCount(void) const
		{
			return m_flags&CSyntax::eF_NUMBER_OF_ARGUMENTS_MASK;
		}

		//==========================================================================

		const char* CConfiguration::COption::GetArg(uint32 index) const
		{
			uint32 argc = GetArgCount();

			return (index < argc) ? m_args[index] : NULL;
		}

		//==========================================================================

		CConfiguration::CConfiguration(uint32 syntaxCount, const CSyntax* pSyntax)
		{
			// Build syntax vector
			m_syntax.reserve(syntaxCount);
			for (uint32 index = 0; index < syntaxCount; ++index)
			{
				m_syntax.push_back(pSyntax[index]);
			}
			
			// Add 'free' commands
			m_syntax.push_back(CSyntax("help", 'h', eSID_HELP, 0, "show this help text", NULL));

			// Sort alphabetically to speed up parsing
			std::sort(m_syntax.begin(), m_syntax.end());

			// Check for duplicate names and abbreviations
			for (TSyntaxVec::iterator sourceIt = m_syntax.begin(), sourceEnd = m_syntax.end(); sourceIt != sourceEnd; ++sourceIt)
			{
				for (TSyntaxVec::iterator compareIt = m_syntax.begin(), compareEnd = m_syntax.end(); compareIt != compareEnd; ++compareIt)
				{
					if ((sourceIt != compareIt) &&																					// If not this one and
							(	(sourceIt->GetID() == compareIt->GetID()) ||											// ID identical or
								(sourceIt->GetAbbreviation() == compareIt->GetAbbreviation()) ||	// abbreviation identical or
								(strcmp(sourceIt->GetName(), compareIt->GetName()) == 0)))				// name identical...
					{
						// ...then we have a duplicate
						LOG_FATAL(ENGINE_LOGGER, "Ambiguous syntax (duplicate):\nSyntax element with ID:[%04d],\tName:[%s],\tabbr.:[%c],\tHelp:[%s] not unique from\n                    ID:[%04d],\tName:[%s],\tabbr.:[%c],\tHelp:[%s]", sourceIt->GetID(), sourceIt->GetName(), sourceIt->GetAbbreviation(), sourceIt->GetHelp(), compareIt->GetID(), compareIt->GetName(), compareIt->GetAbbreviation(), compareIt->GetHelp());
					}
				}
			}
		}

		//==========================================================================

		bool CConfiguration::Parse(uint32 argc, const char* const* argv)
		{
			TArgumentVec nonOptionArgs;
			TArgumentVec optionArgs;

			nonOptionArgs.reserve(argc);
			optionArgs.reserve(argc);

			// First, sort the argument list into options and non-options
			for (uint32 argi = 1; argi < argc; ++argi)
			{
				switch (argv[argi][0])
				{
				case '-':
					switch (argv[argi][1])
					{
					case '-':
						{
							// If a valid option, remove '--' prefix and store
							bool valid = false;
							for (TSyntaxVec::iterator it = m_syntax.begin(), end = m_syntax.end(); it != end; ++it)
							{
								if (strcmp(it->GetName(), &argv[argi][2]) == 0)
								{
									optionArgs.push_back(&argv[argi][2]);
									valid = true;
									break;
								}
							}
							
							if (!valid)
							{
								LOG_ERROR(ENGINE_LOGGER, "[%s] is not a valid option", argv[argi]);
								ShowHelp();
								return false;
							}
						}
						break;

					default:
						{
							// separate abbreviated options into individual options
							uint32 optionCount = strlen(argv[argi])-1;
							for (uint32 index = 0; index < optionCount; ++index)
							{
								// If a valid option, remove '-' prefix and store
								bool valid = false;
								for (TSyntaxVec::iterator it = m_syntax.begin(), end = m_syntax.end(); it != end; ++it)
								{
									if (argv[argi][1+index] == it->GetAbbreviation())
									{
										optionArgs.push_back(it->GetName());
										valid = true;
										break;
									}
								}

								if (!valid)
								{
									LOG_ERROR(ENGINE_LOGGER, "[%c] is not a valid option", argv[argi][1+index]);
									ShowHelp();
									return false;
								}
							}
						}
						break;
					}
					break;

				default:
					nonOptionArgs.push_back(argv[argi]);
					break;
				}
			}

			// Now create parsed options from the two lists
			for (TArgumentVec::iterator optionIt = optionArgs.begin(), endOptionIt = optionArgs.end(); optionIt != endOptionIt; ++optionIt)
			{
				for (TSyntaxVec::iterator syntaxIt = m_syntax.begin(), endSyntaxIt = m_syntax.end(); syntaxIt != endSyntaxIt; ++syntaxIt)
				{
					if (strcmp(syntaxIt->GetName(), *optionIt) == 0)
					{
						uint32 expectedArgCount = (syntaxIt->GetFlags() & CSyntax::eF_NUMBER_OF_ARGUMENTS_MASK);
						if (expectedArgCount > nonOptionArgs.size())
						{
							LOG_ERROR(ENGINE_LOGGER, "Not enough arguments supplied for option [%s]", *optionIt);
							ShowHelp();
							return false;
						}

						// Create args vector for this option and remove processed args from nonOptionArgs vector
						TArgumentVec args(nonOptionArgs.begin(), nonOptionArgs.begin()+expectedArgCount);
						TArgumentVec remaining(nonOptionArgs.begin()+expectedArgCount, nonOptionArgs.end());
						nonOptionArgs.swap(remaining);

						m_option.push_back(COption(syntaxIt->GetID(), syntaxIt->GetFlags(), args));
					}
				}
			}

			for (TOptionVec::iterator it = m_option.begin(), end = m_option.end(); it != end; ++it)
			{
				uint32 count = it->GetArgCount();
				LOG_INFO(ENGINE_LOGGER, "ID: [%d]", it->GetID());
				for (uint32 index = 0; index < count; ++index)
				{
					LOG_INFO(ENGINE_LOGGER, "  arg %d: [%s]", index, it->GetArg(index));
				}
			}

			return false;
		}

		//==========================================================================

		bool CConfiguration::Parse(const char* configFile)
		{
			IGNORE_PARAMETER(configFile);
			TODO(fix configuration file parsing)
			return false;
		}

		//==========================================================================

		void CConfiguration::ShowHelp(void)
		{
			size_t maxNameLength = 0;
			for (TSyntaxVec::iterator it = m_syntax.begin(), end = m_syntax.end(); it != end; ++it)
			{
				size_t length = strlen(it->GetName());
				if (length > maxNameLength)
				{
					maxNameLength = length;
				}
			}

			char format[64];
			sprintf(format, "\t--%%-%ds\t-%%c : %%s", maxNameLength);

			LOG_ALWAYS(ENGINE_LOGGER, "Help usage:");
			for (TSyntaxVec::iterator it = m_syntax.begin(), end = m_syntax.end(); it != end; ++it)
			{
				LOG_ALWAYS(ENGINE_LOGGER, format, it->GetName(), it->GetAbbreviation(), it->GetHelp());
			}

			exit(0);
		}

		/* BOLLOX
		//==========================================================================

		CConfiguration::CConfiguration(uint32 argc, const char* const* argv)
		{
			m_parsed.reserve(argc);

			std::vector<SSyntax> preArgs;
			std::vector<SSyntax> args;
			std::vector<SSyntax> postArgs;

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
		END BOLLOX */

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


