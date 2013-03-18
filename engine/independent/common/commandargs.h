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
			struct SOption
			{
				typedef bool (*TOptionFn)(void);

				SOption(const char* pOption, char flag, const char* pHelp, TOptionFn pOptionFuntion);

				const	char*	m_pOption;
				const char* m_pHelp;
				TOptionFn		m_pOptionFuntion;
				const	char	m_flag;
			};

			//------------------------------------------------------------------------

			struct SOptionMap
			{
				SOptionMap(SOptionMap* pBase, SOption* pOptions, uint32 count);

							SOptionMap*	m_pNext;
				const	SOption*		m_pOptions;
				const	uint32			m_count;
			};

			//------------------------------------------------------------------------

			virtual					~CCommandArgs(void);

			static	bool		Parse(int argc, const char* const* argv);

			//------------------------------------------------------------------------

		protected:
											CCommandArgs(int argc, const char* const* argv);

			virtual	uint32	ParseArgument(const char* argument);
			virtual	uint32	ParseOption(const char* option);
			virtual	uint32	ParseFlags(const char* flags);

			virtual	bool		ProcessHelp(void);
			virtual	bool		ProcessConfig(void);
			virtual	bool		ProcessVersion(void);

			//------------------------------------------------------------------------

			SOptionMap*					m_pOptionMap;
			const char* const*	m_argv;
			int									m_argc;
			bool								m_shouldExit;
	};

	//============================================================================

} // End [namespace engine]

//==============================================================================

#endif // !defined(__COMMANDARGS_H__)
// EOF


