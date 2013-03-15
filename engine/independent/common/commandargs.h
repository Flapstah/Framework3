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
		public:
											CCommandArgs(int argc, const char* const* argv);
			virtual					~CCommandArgs(void);

							bool		ShouldExit(void) { return m_shouldExit; }

		protected:
			virtual	uint32	ParseArgumentAsCommand(const char* argument);
			virtual	uint32	ParseArgumentAsFlags(const char* flags);

			virtual	bool		ProcessHelp(void);
			virtual	bool		ProcessConfig(void);
			virtual	bool		ProcessVersion(void);

			int									m_argc;
			const char* const*	m_argv;
			bool								m_shouldExit;
	};

	//============================================================================

} // End [namespace engine]

//==============================================================================

#endif // !defined(__COMMANDARGS_H__)
// EOF


