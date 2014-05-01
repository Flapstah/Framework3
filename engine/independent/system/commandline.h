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

		public:
			struct SSyntax
			{
				enum EFlags
				{
					// Flags which determine item status after parsing
					eF_PARSED_OK							= 1 << 0,
					eF_PRE										= 1 << 1,
					eF_POST										= 1 << 2,
					eF_COMMANDLINE						= 1 << 3,

					// Flags which determine how to parse item
					eF_EXPECTED_ARGS_SHIFT		= 4,
					eF_EXPECTED_ARGS_MASK			= (1 << 4) | (1 << 5) | (1 << 6) | (1 << 7),
					eF_EXPECTED_ARG0_IS_PATH	= 1 << 8,
					eF_EXPECTED_ARG1_IS_PATH	= 1 << 9,
					eF_EXPECTED_ARG2_IS_PATH	= 1 << 10,
					eF_EXPECTED_ARG3_IS_PATH	= 1 << 11,
					eF_EXPECTED_ARG4_IS_PATH	= 1 << 12,
					eF_EXPECTED_ARG5_IS_PATH	= 1 << 13,
					eF_EXPECTED_ARG6_IS_PATH	= 1 << 14,
					eF_EXPECTED_ARG7_IS_PATH	= 1 << 15,
					eF_EXPECTED_ARG8_IS_PATH	= 1 << 16,
					eF_EXPECTED_ARG9_IS_PATH	= 1 << 17,
					eF_EXPECTED_ARG10_IS_PATH	= 1 << 18,
					eF_EXPECTED_ARG11_IS_PATH	= 1 << 19,
					eF_EXPECTED_ARG12_IS_PATH	= 1 << 20,
					eF_EXPECTED_ARG13_IS_PATH	= 1 << 21,
					eF_EXPECTED_ARG14_IS_PATH	= 1 << 22,
					eF_EXPECTED_ARG15_IS_PATH	= 1 << 23,

					eF_CUSTOM_ARGS_PARSING		= 1 << 24,
				};

				typedef bool (*CustomArgParsing)(uint32 argc, const char* const* argv, uint32& index);

				SSyntax(uint32 id, const char* name, uint32 flags, CustomArgParsing pParseFn = NULL);

				uint32											m_ID;
				uint32											m_flags;
				const char*									m_name;
				CustomArgParsing						m_pParseFn;
			};

			struct SParsedItem
			{
				SParsedItem(uint32 id, uint32 flags);
				bool PushArg(const char* arg);

				uint32											m_ID;
				uint32											m_flags;
				std::vector<const char*>		m_argv;
			};

		public:
			CConfiguration(uint32 argc, const char* const* argv);
			CConfiguration(const char* configFile);
			~CConfiguration(void);

		protected:
			std::vector<SParsedItem> m_parsed;

			//------------------------------------------------------------------------
		}; // End [class CConfiguration]

		//==========================================================================
	} // End [namespace system]

	//============================================================================
} // End [namespace engine]

//==============================================================================

#endif // !defined(__CONFIGURATION_H__)
// EOF

