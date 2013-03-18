#if !defined(__COMMANDARGS_H__)
#define __COMMANDARGS_H__

//==============================================================================

namespace engine
{
	//============================================================================
	// CCommandArgs
	//============================================================================
	class CCommandArgs
	{
			//------------------------------------------------------------------------

		public:
			enum EParseState
			{
				ePS_UNPARSED = 0,
				ePS_SUCCESS,
				ePS_UNKNOWN_ARGUMENT,
				ePS_UNKNOWN_OPTION,
				ePS_UNKNOWN_FLAG,
				ePS_UNKNOWN_TYPE,
				ePS_REQUEST_EXIT
			};

			//------------------------------------------------------------------------

			enum EArgumentType
			{
				eAT_Argument,
				eAT_Option,
				eAT_Flag
			};

			//------------------------------------------------------------------------

			struct SOption
			{
				typedef EParseState (*TOptionFn)(uint32& skipCount);

				SOption(const char* pOption, char flag, const char* pHelp, TOptionFn pOptionFuntion);

				const	char*				m_pOption;
				const char* 			m_pHelp;
							TOptionFn		m_pOptionFuntion;
				const	char				m_flag;
			};

			//------------------------------------------------------------------------

			struct SOptionMap
			{
				SOptionMap(SOptionMap*& pParent, SOption* pOptions, uint32 count);

							SOptionMap*	m_pNext;
				const	SOption*		m_pOptions;
				const	uint32			m_count;
			};

			//------------------------------------------------------------------------

			virtual							~CCommandArgs(void);

			static	EParseState	Parse(int argc, const char* const* argv);

			//------------------------------------------------------------------------

		private:
													CCommandArgs(void);
													CCommandArgs(int argc, const char* const* argv);

		protected:
							EParseState UpdateState(EParseState state);

			virtual	void				RegisterOptionMap(void);

			virtual	uint32			ParseArgument(const char* pArgument, EArgumentType type);
			virtual	EParseState	ProcessArgument(const char* pArgument, uint32& skipCount);

			static	EParseState	ProcessHelp(uint32& skipCount);
			static	EParseState	ProcessConfig(uint32& skipCount);
			static	EParseState	ProcessVersion(uint32& skipCount);

			//------------------------------------------------------------------------

			static	CCommandArgs*	m_pThis;
			SOptionMap*					m_pOptionMap;
			const char* const*	m_argv;
			uint32							m_argc;
			EParseState					m_state;
	}; // End [class CCommandArgs]

	//============================================================================

} // End [namespace engine]

//==============================================================================

#endif // !defined(__COMMANDARGS_H__)
// EOF


