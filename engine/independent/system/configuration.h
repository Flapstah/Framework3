#if !defined(__CONFIGURATION_H__)
#define __CONFIGURATION_H__

//==============================================================================

#include <map>
#include <string>
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

		public:
			enum eSyntaxID
			{
				eSID_HELP = 0,
				eSID_ROOT,
				eSID_LOG,
				eSID_FIRST_USERID,
			};

			class CSyntax
			{
			public:
				enum eFlags
				{
					eF_NUMBER_OF_ARGUMENTS_MASK		= 0x7,			// max 7 arguments
					eF_MAX_NUMBER_OF_ARGS					= 7,
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

			typedef std::vector<const char *> TArgumentVec;
			class COption
			{
			public:
				COption(uint32 id, uint32 flags, TArgumentVec args);
				uint32 GetArgCount(void) const;
				const char* GetArg(uint32 index) const;
				uint32 GetID(void) const { return m_ID; }

			private:
				TArgumentVec			m_args;
				uint32						m_ID;
				uint32						m_flags;
			};

		public:
			CConfiguration(void);
			~CConfiguration(void);

			void AddSyntax(uint32 syntaxCount, const CSyntax* pSyntax);
			bool Parse(uint32 argc, const char* const* argv);
			bool Parse(const char* configFile);
			const COption* GetOption(uint32 optionID) const;
			const std::string GetValue(const std::string& key) const;
			bool GetValue(const std::string& key, uint32& value) const;
			bool GetValue(const std::string& key, bool& value) const;
			void ShowHelp(void);

		protected:
			void SplitKeyValue(std::string& line, char split, std::string& key, std::string& value);
			void ProcessLine(std::string* pLine);

		protected:
			typedef std::vector<CSyntax> TSyntaxVec;
			typedef std::vector<COption> TOptionVec;
			typedef std::map<std::string, std::string> TConfigurationMap;

			TSyntaxVec m_syntax;
			TOptionVec m_option;
			TConfigurationMap m_config;

			//------------------------------------------------------------------------
		}; // End [class CConfiguration]

		//==========================================================================
	} // End [namespace system]

	//============================================================================
} // End [namespace engine]

//==============================================================================

#endif // !defined(__CONFIGURATION_H__)
// EOF

