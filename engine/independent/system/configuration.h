#if !defined(__CONFIGURATION_H__)
#define __CONFIGURATION_H__

//==============================================================================

#include <vector>

//==============================================================================

namespace engine
{
	//============================================================================

	namespace system
	{
		//==========================================================================
		// CConfiguration
		//==========================================================================
		class CConfiguration
		{
			//------------------------------------------------------------------------
//			{ ID_LOG, "log", 'l', flags, "specify the log file", NULL }

		public:
			enum eSyntaxID
			{
				eSID_HELP = 0,
				eSID_FIRST_USERID,
			};

			class CSyntax
			{
			public:
				enum eFlags
				{
					eF_NUMBER_OF_ARGUMENTS_MASK		= 0xff,
					eF_MAX_NUMBER_OF_ARGS					= 8,
					eF_ARG0_IS_PATH								= 1 << 8,
					eF_ARG1_IS_PATH								= 1 << 9,
					eF_ARG2_IS_PATH								= 1 << 10,
					eF_ARG3_IS_PATH								= 1 << 11,
					eF_ARG4_IS_PATH								= 1 << 12,
					eF_ARG5_IS_PATH								= 1 << 13,
					eF_ARG6_IS_PATH								= 1 << 14,
					eF_ARG7_IS_PATH								= 1 << 15,

				};

				// returns success or fail; pass-through argv, argc; index is adjusted by how many args were parsed
				typedef bool (*CustomArgParsing)(uint32 argc, const char* const* argv, uint32& index);

				CSyntax(const char* name, char abbreviation, uint32 id, uint32 flags, const char* help, CustomArgParsing pParseFn = NULL);

				inline const char*	GetName(void)					{ return m_name; }
				inline const char*	GetHelp(void)					{ return m_help; }
				inline uint32				GetID(void)						{ return m_ID; }
				inline uint32				GetFlags(void)				{ return m_flags; }
				inline char					GetAbbreviation(void)	{ return m_abbreviation; }

				// operator< used in sorting
				bool operator<(const CSyntax& rhs) const
				{
					return strcmp(m_name, rhs.m_name) < 0;
				}

			private:
				const char*				m_name;
				const char*				m_help;
				CustomArgParsing	m_pParseFn;
				uint32						m_ID;
				uint32						m_flags;
				char							m_abbreviation;
			};

			//------------------------------------------------------------------------
//			{ ID_LOG, "<arg0>".."<arg7" }

			class COption
			{
				COption(uint32 id, uint32 index, uint32 argc, const char* const* argv);
				const char* GetArg(uint32 index);

			private:
				const char*				m_arg[CSyntax::eF_MAX_NUMBER_OF_ARGS];
				uint32						m_ID;
				uint32						m_argc;
			};

		public:
			CConfiguration(uint32 syntaxCount, const CSyntax* pSyntax);
			~CConfiguration(void);

			bool Parse(uint32 argc, const char* const* argv);
			bool Parse(const char* configFile);
			void Help(void);

		protected:
			typedef std::vector<CSyntax> TSyntaxVec;

			TSyntaxVec m_syntax;

			//------------------------------------------------------------------------
		}; // End [class CConfiguration]

		//==========================================================================
	} // End [namespace system]

	//============================================================================
} // End [namespace engine]

//==============================================================================

#endif // !defined(__CONFIGURATION_H__)
// EOF

