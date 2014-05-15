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

		CConfiguration::COption::COption(uint32 id, uint32 index, uint32 argc, const char* const* argv)
			: m_ID(id)
			, m_argc(argc)
		{
			for (uint32 argi = 0; argi < CConfiguration::CSyntax::eF_MAX_NUMBER_OF_ARGS; ++argi)
			{
				m_arg[argi] = (argi < argc) ? argv[index+argi] : NULL;
			}
		}

		//==========================================================================

		const char* CConfiguration::COption::GetArg(uint32 index)
		{
			const char* pArg = NULL;
			
			if (index < m_argc)
			{
				pArg = m_arg[index];
			}

			return pArg;
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

			/*
			// Skip the executable name
			for (uint32 argi = 1; argi < argc; ++argi)
			{
				if (argv[argi][0] == '-')
				{
					if (argv[argi][1] == '-')
					{
						// process long arg name
						for (uint32 syntaxIndex = 1; syntaxIndex < syntaxCount; ++syntaxIndex)
						{
							if (strcmp(&argv[argi][2], pSyntax[syntaxIndex].GetName()) == 0)
							{

							}
						}
					}
					else
					{
						// process abbreviated name(s)
					}
				}
				else
				{
					// print help?
					TODO(print syntax help here)
				}
			}
		*/
		}

		bool CConfiguration::Parse(uint32 argc, const char* const* argv)
		{
			IGNORE_PARAMETER(argc);
			IGNORE_PARAMETER(argv);
			TODO(fix command line parsing)
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

		void CConfiguration::Help(void)
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


