#include "common/stdafx.h"

#include "common/console.h"
#include "common/log.h"
#include <iomanip>
#include <ostream>

//==============================================================================

namespace engine
{
	//============================================================================
	// Create custom log for the console
	//============================================================================
	static CLog g_log(DEFAULT_LOGGER, "Console");

	//============================================================================
	// TVariable specialisation for int64
	//============================================================================

	template class CConsole::TVariable<int64>;

	//============================================================================

	template<> const char* CConsole::TVariable<int64>::SetString(const char* value)
	{
		std::ostringstream buffer;
		buffer << m_variable;

		if ((m_flags & eF_CONST) == 0)
		{
			m_variable = m_pCallback(strtoll(value, NULL, 0));
		}
#if !defined(_RELEASE)
		else
		{
			LOG_WARNING(g_log, "Failed to set const integer variable with %s", value);
		}
#endif // !defined(_RELEASE)


		return buffer.str().c_str();
	}

	//============================================================================
	// TVariable specialisation for double
	//============================================================================

	template class CConsole::TVariable<double>;

	//============================================================================

	template<> const char* CConsole::TVariable<double>::SetString(const char* value)
	{
		std::ostringstream buffer;
		buffer << std::setprecision(std::numeric_limits<double>::digits10+2) << m_variable;

		if ((m_flags & eF_CONST) == 0)
		{
			m_variable = m_pCallback(strtold(value, NULL));
		}
#if !defined(_RELEASE)
		else
		{
			LOG_WARNING(g_log, "Failed to set const double variable with %s", value);
		}
#endif // !defined(_RELEASE)

		return buffer.str().c_str();
	}

	//============================================================================
	// TVariable specialisation for std::string
	//============================================================================

	template class CConsole::TVariable<std::string>;

	//============================================================================

	template<> int64 CConsole::TVariable<std::string>::GetInteger(void) const
	{
		return atol(m_variable.c_str());
	}

	//============================================================================

	template<> int64 CConsole::TVariable<std::string>::SetInteger(const int64 value)
	{
		int64 old = GetInteger();

		std::ostringstream buffer;
		buffer << value;

		if ((m_flags & eF_CONST) == 0)
		{
			m_variable = m_pCallback(buffer.str());
		}
#if !defined(_RELEASE)
		else
		{
			LOG_WARNING(g_log, "Failed to set const string variable with %s", buffer.str().c_str());
		}
#endif // !defined(_RELEASE)

		return old;
	}

	//============================================================================

	template<> double CConsole::TVariable<std::string>::GetDouble(void) const
	{
		return atof(m_variable.c_str());
	}

	//============================================================================

	template<> double CConsole::TVariable<std::string>::SetDouble(const double value)
	{
		double old = GetInteger();

		std::ostringstream buffer;
		buffer << std::setprecision(std::numeric_limits<double>::digits10+2) << value;

		if ((m_flags & eF_CONST) == 0)
		{
			m_variable = m_pCallback(buffer.str());
		}
#if !defined(_RELEASE)
		else
		{
			LOG_WARNING(g_log, "Failed to set const string variable with %s", buffer.str().c_str());
		}
#endif // !defined(_RELEASE)

		return old;
	}

	//============================================================================

	template<> const char* CConsole::TVariable<std::string>::GetString(void) const
	{
		return m_variable.c_str();
	}

	//============================================================================

	template<> const char* CConsole::TVariable<std::string>::SetString(const char* value)
	{
		std::string old(m_variable);

		if ((m_flags & eF_CONST) == 0)
		{
			m_variable = m_pCallback(std::string(value));
		}
#if !defined(_RELEASE)
		else
		{
			LOG_WARNING(g_log, "Failed to set const string variable with %s", value);
		}
#endif // !defined(_RELEASE)

		return old.c_str();
	}

	//============================================================================
	// TVariable generic template functions
	//============================================================================

	template<typename _type_> CConsole::TVariable<_type_>::TVariable(_type_& variable, uint32 flags, typename CConsole::TVariable<_type_>::OnChangeCallback pCallback /* = NULL */)
		: m_variable(variable)
		, m_pCallback(pCallback)
		, m_flags(flags)
	{
		if (m_pCallback == NULL)
		{
			m_pCallback = &CConsole::TVariable<_type_>::DefaultOnChange;
		}
	}

	//============================================================================

	template<typename _type_> CConsole::TVariable<_type_>::~TVariable(void)
	{
	}

	//============================================================================

	template<typename _type_> int64 CConsole::TVariable<_type_>::GetInteger(void) const
	{
		return static_cast<int64>(m_variable);
	}

	//============================================================================

	template<typename _type_> int64 CConsole::TVariable<_type_>::SetInteger(const int64 value)
	{
		int64 old = GetInteger();

		if ((m_flags & eF_CONST) == 0)
		{
			m_variable = m_pCallback(value);
		}
#if !defined(_RELEASE)
		else
		{
			LOG_WARNING(g_log, "Failed to set const variable with %" PRId64, value);
		}
#endif // !defined(_RELEASE)

		return old;
	}

	//============================================================================

	template<typename _type_> double CConsole::TVariable<_type_>::GetDouble(void) const
	{
		return static_cast<double>(m_variable);
	}

	//============================================================================

	template<typename _type_> double CConsole::TVariable<_type_>::SetDouble(const double value)
	{
		double old = GetDouble();

		if ((m_flags & eF_CONST) == 0)
		{
			m_variable = m_pCallback(value);
		}
#if !defined(_RELEASE)
		else
		{
			LOG_WARNING(g_log, "Failed to set const variable with %g", value);
		}
#endif // !defined(_RELEASE)

		return old;
	}

	//============================================================================

	template<typename _type_> const char* CConsole::TVariable<_type_>::GetString(void) const
	{
		std::ostringstream buffer;
		buffer << std::setprecision(std::numeric_limits<double>::digits10+2) << m_variable;
		return buffer.str().c_str();
	}

	//============================================================================

	template<typename _type_> uint32 CConsole::TVariable<_type_>::ModifyFlags(uint32 set, uint32 clear)
	{
		uint32 old = m_flags;
		m_flags = ((m_flags | set) & ~clear);
		return old;
	}

	//============================================================================

	template<typename _type_> const _type_& CConsole::TVariable<_type_>::DefaultOnChange(const _type_& value)
	{
		return value;
	}

	//============================================================================

	CConsole::CCommand::CCommand(uint32 flags, ExecuteCommandCallback pCallback)
		: m_pCallback(pCallback)
		, m_flags(flags)
	{
	}

	//============================================================================

	CConsole::CCommand::~CCommand(void)
	{
	}

	//============================================================================
	
	bool CConsole::CCommand::Execute(std::vector<std::string>& argv)
	{
		return m_pCallback(argv);
	}

	//============================================================================
	// CConsole
	//============================================================================

	CConsole::CConsole(void)
	{
	}

	//============================================================================

	CConsole::~CConsole(void)
	{
		for (TVariableMap::const_iterator it = m_variables.begin(), end = m_variables.end(); it != end; ++it)
		{
			const SDetails* pDetails = FindDetails(it->first);
			if (pDetails != NULL)
			{
				LOG_ERROR(g_log, "Still have variable [%s] @ 0x%p registered", pDetails->m_name.c_str(), it->second.get());
			}
			else
			{
				LOG_ERROR(g_log, "Still have variable [%#x] @ 0x%p registered", it->first, it->second.get());
			}
		}
	}

	//============================================================================

	CConsole::TIVariablePtr CConsole::RegisterVariable(uint32 nameHash, int64& variable, int64 value, uint32 flags, TInteger::OnChangeCallback pOnChangeCallback /* = NULL */, const char* name /* = NULL */, const char* description /* = NULL */)
	{
		boost::shared_ptr<TInteger> pVariable;

		if ((FindVariable(nameHash) == NULL) && (FindCommand(nameHash) == NULL))
		{
			// Make sure the variable is non-const before setting it's initial value...
			uint32 adjustedFlags = flags&~IVariable::eF_CONST;
			pVariable = boost::make_shared<TInteger>(TInteger(variable, adjustedFlags, pOnChangeCallback));
			if (pVariable != NULL)
			{
				m_variables[nameHash] = pVariable;
			}

			pVariable->SetInteger(value);
			//...then restore the flags
			pVariable->ModifyFlags(flags, 0);

			if (name != NULL)
			{
				AddDescription(nameHash, name, description);
			}
		}
		else
		{
			LOG_FATAL(g_log, "Trying to register an integer variable named [%s] (hash [%d]), with description [%s], but that name already exists!", name, nameHash, description);
		}

		return pVariable;
	}

	//============================================================================

	CConsole::TIVariablePtr CConsole::RegisterVariable(uint32 nameHash, double& variable, double value, uint32 flags, TDouble::OnChangeCallback pOnChangeCallback /* = NULL */, const char* name /* = NULL */, const char* description /* = NULL */)
	{
		boost::shared_ptr<TDouble> pVariable;

		if ((FindVariable(nameHash) == NULL) && (FindCommand(nameHash) == NULL))
		{
			// Make sure the variable is non-const before setting it's initial value...
			uint32 adjustedFlags = flags&~IVariable::eF_CONST;
			pVariable = boost::make_shared<TDouble>(TDouble(variable, adjustedFlags, pOnChangeCallback));
			if (pVariable != NULL)
			{
				m_variables[nameHash] = pVariable;
			}

			pVariable->SetDouble(value);
			//...then restore the flags
			pVariable->ModifyFlags(flags, 0);

			if (name != NULL)
			{
				AddDescription(nameHash, name, description);
			}
		}
		else
		{
			LOG_FATAL(g_log, "Trying to register a double variable named [%s] (hash [%d]), with description [%s], but that name already exists!", name, nameHash, description);
		}

		return pVariable;
	}

	//============================================================================

	CConsole::TIVariablePtr CConsole::RegisterVariable(uint32 nameHash, std::string& variable, const char* value, uint32 flags, TString::OnChangeCallback pOnChangeCallback /* = NULL */, const char* name /* = NULL */, const char* description /* = NULL */)
	{
		boost::shared_ptr<TString> pVariable;

		if ((FindVariable(nameHash) == NULL) && (FindCommand(nameHash) == NULL))
		{
			// Make sure the variable is non-const before setting it's initial value...
			uint32 adjustedFlags = flags&~IVariable::eF_CONST;
			pVariable = boost::make_shared<TString>(TString(variable, adjustedFlags, pOnChangeCallback));
			if (pVariable != NULL)
			{
				m_variables[nameHash] = pVariable;
			}

			pVariable->SetString(value);
			//...then restore the flags
			pVariable->ModifyFlags(flags, 0);

			if (name != NULL)
			{
				AddDescription(nameHash, name, description);
			}
		}
		else
		{
			LOG_FATAL(g_log, "Trying to register an string variable named [%s] (hash [%d]), with description [%s], but that name already exists!", name, nameHash, description);
		}

		return pVariable;
	}

	//============================================================================

	void CConsole::UnregisterVariable(uint32 nameHash)
	{
		m_variables.erase(nameHash);
		m_details.erase(nameHash);
	}

	//============================================================================

	void CConsole::UnregisterVariable(TIVariablePtr& pVariable)
	{
		for (TVariableMap::iterator it = m_variables.begin(), end = m_variables.end(); it != end; ++it)
		{
			if (it->second == pVariable)
			{
				m_details.erase(it->first);
				m_variables.erase(it);
				pVariable.reset();
				break;
			}
		}
	}

	//============================================================================

	CConsole::TIVariablePtr CConsole::FindVariable(uint32 nameHash)
	{
		TVariableMap::iterator it = m_variables.find(nameHash);
		TIVariablePtr pVariable;

		if (it != m_variables.end())
		{
			pVariable = it->second;
		}

		return pVariable;
	}

	//============================================================================

	CConsole::TIVariablePtr CConsole::FindVariable(const char* name)
	{
		return FindVariable(engine::CRunTimeStringHash::Calculate(name));
	}

	//============================================================================

	const CConsole::SDetails* CConsole::FindDetails(uint32 nameHash)
	{
		SDetails* pDetails = NULL;
		TDetailsMap::iterator it = m_details.find(nameHash);

		if (it != m_details.end())
		{
			pDetails = it->second;
		}
		
		return pDetails;
	}

	//============================================================================

	const CConsole::SDetails* CConsole::FindDetails(const char* name)
	{
		return FindDetails(engine::CRunTimeStringHash::Calculate(name));
	}

	//============================================================================
	
	CConsole::TICommandPtr CConsole::RegisterCommand(uint32 nameHash, uint32 flags, ICommand::ExecuteCommandCallback pExecuteCommandCallback, const char* name /* = NULL */, const char* description /* = NULL */)
	{
		TICommandPtr pCommand = NULL;

		if (pExecuteCommandCallback != NULL)
		{
			if ((FindVariable(nameHash) == NULL) && (FindCommand(nameHash) == NULL))
			{
				pCommand = new CCommand(flags, pExecuteCommandCallback);
				if (pCommand != NULL)
				{
					m_commands[nameHash] = pCommand;
				}

				if (name != NULL)
				{
					AddDescription(nameHash, name, description);
				}
			}
			else
			{
				LOG_FATAL(g_log, "Trying to register command named [%s] (hash [%d]), with description [%s], but that name already exists!", name, nameHash, description);
			}
		}
		else
		{
			LOG_FATAL(g_log, "Trying to register command named [%s] (hash [%d]), with description [%s], with NULL execute callback!", name, nameHash, description);
		}

		return pCommand;
	}

	//============================================================================

	void CConsole::UnregisterCommand(uint32 nameHash)
	{
		m_commands.erase(nameHash);
		m_details.erase(nameHash);
	}

	//============================================================================

	void CConsole::UnregisterCommand(CConsole::TICommandPtr& pCommand)
	{
		for (TCommandMap::iterator it = m_commands.begin(), end = m_commands.end(); it != end; ++it)
		{
			if (it->second == pCommand)
			{
				m_details.erase(it->first);
				m_commands.erase(it);
				break;
			}
		}
	}
		
	//============================================================================

	CConsole::TICommandPtr CConsole::FindCommand(uint32 nameHash)
	{
		TCommandMap::iterator it = m_commands.find(nameHash);
		TICommandPtr pCommand = NULL;

		if (it != m_commands.end())
		{
			pCommand = it->second;
		}

		return pCommand;
	}

	//============================================================================

	CConsole::TICommandPtr CConsole::FindCommand(const char* name)
	{
		return FindCommand(engine::CRunTimeStringHash::Calculate(name));
	}

	//============================================================================

	CConsole::eConsoleState CConsole::Execute(const char* commandLine)
	{
		return Execute(std::string(commandLine));
	}

	//============================================================================

	CConsole::eConsoleState CConsole::Execute(std::string commandLine)
	{
		eConsoleState state = eCS_OK;

		// Use custom escaped_list_separator to delimit the tokens
		boost::escaped_list_separator<char> separator('\\', ' ', '\"');
		boost::tokenizer<boost::escaped_list_separator<char> > tokens(commandLine, separator);

		// Create a vector of tokens
		std::vector<std::string> argv(tokens.begin(), tokens.end());

		// Find command
		TICommandPtr command = FindCommand(engine::CRunTimeStringHash::Calculate(argv[0].c_str()));
		if (command != NULL)
		{
			state = (command->Execute(argv) == true) ? eCS_OK : eCS_COMMAND_FAILED;
		}
		else
		{
			// Not a command; maybe it's a variable?
			TIVariablePtr variable = FindVariable(engine::CRunTimeStringHash::Calculate(argv[0].c_str()));
			if (variable != NULL)
			{
				if (strcmp(argv[1].c_str(), "=") == 0)
				{
					// Skip the '='
					variable->SetString(argv[2].c_str());
				}
				else
				{
					// No '='; so assume it's a value
					variable->SetString(argv[1].c_str());
				}
			}
			else
			{
				LOG_ERROR(g_log, "[%s] not found", argv[0].c_str());
				state = eCS_NOT_FOUND;
			}
		}

		return state;
	}

	//============================================================================

	CConsole::eConsoleState CConsole::ExecuteDeferred(const char* commandLine, uint32 frames)
	{
		LOG_FATAL(g_log, "[TODO]: CConsole::ExecuteDeferred(frames)");
		return eCS_OK;
	}

	//============================================================================

	CConsole::eConsoleState CConsole::ExecuteDeferred(const char* commandLine, float seconds)
	{
		LOG_FATAL(g_log, "[TODO]: CConsole::ExecuteDeferred(seconds)");
		return eCS_OK;
	}

	//============================================================================

	void CConsole::AddDescription(uint32 nameHash, const char* name, const char* description)
	{
		SDetails* pDetails = new SDetails();
		if (pDetails != NULL)
		{
			pDetails->m_name = name;
			pDetails->m_description = description;
			m_details[nameHash] = pDetails;
		}
	}

	//============================================================================

} // End [namespace engine]

//==============================================================================
// EOF


