#include "common/stdafx.h"

#include "common/console.h"
#include <iomanip>

//==============================================================================

namespace engine
{
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
			m_variable = m_pCallback(atol(value));
		}
#if !defined(_RELEASE)
		else
		{
			printf("[CONSOLE]: failed to set const integer variable with %s", value);
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
			m_variable = m_pCallback(atof(value));
		}
#if !defined(_RELEASE)
		else
		{
			printf("[CONSOLE]: failed to set const double variable with %s", value);
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
			printf("[CONSOLE]: failed to set const string variable with %s", buffer.str().c_str());
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
			printf("[CONSOLE]: failed to set const string variable with %s", buffer.str().c_str());
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
			printf("[CONSOLE]: failed to set const string variable with %s", value);
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
			printf("[CONSOLE]: failed to set const variable with %" PRId64, value);
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
			printf("[CONSOLE]: failed to set const variable with %g", value);
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
			const SVariableDetails* pDetails = FindDetails(it->first);
			if (pDetails != NULL)
			{
				printf("[CONSOLE]: still have variable [%s] @ %p registered\n", pDetails->m_name.c_str(), it->second.get());
			}
			else
			{
				printf("[CONSOLE]: still have variable %p registered\n", it->second.get());
			}
		}
	}

	//============================================================================

	CConsole::TIVariablePtr CConsole::RegisterVariable(uint32 nameHash, int64& variable, int64 value, uint32 flags, TInteger::OnChangeCallback pOnChangeCallback /* = NULL */, const char* name /* = NULL */, const char* description /* = NULL */)
	{
		boost::shared_ptr<TInteger> pVariable;

		if (FindVariable(nameHash) == NULL)
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
			printf("[CONSOLE]: Trying to register an integer variable named [%s] (hash [%d]), with description [%s], but it already exists!\n", name, nameHash, description);
		}

		return pVariable;
	}

	//============================================================================

	CConsole::TIVariablePtr CConsole::RegisterVariable(uint32 nameHash, double& variable, double value, uint32 flags, TDouble::OnChangeCallback pOnChangeCallback /* = NULL */, const char* name /* = NULL */, const char* description /* = NULL */)
	{
		boost::shared_ptr<TDouble> pVariable;

		if (FindVariable(nameHash) == NULL)
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
			printf("[CONSOLE]: Trying to register a double variable named [%s] (hash [%d]), with description [%s], but it already exists!\n", name, nameHash, description);
		}

		return pVariable;
	}

	//============================================================================

	CConsole::TIVariablePtr CConsole::RegisterVariable(uint32 nameHash, std::string& variable, const char* value, uint32 flags, TString::OnChangeCallback pOnChangeCallback /* = NULL */, const char* name /* = NULL */, const char* description /* = NULL */)
	{
		boost::shared_ptr<TString> pVariable;

		if (FindVariable(nameHash) == NULL)
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
			printf("[CONSOLE]: Trying to register an string variable named [%s] (hash [%d]), with description [%s], but it already exists!\n", name, nameHash, description);
		}

		return pVariable;
	}

	//============================================================================

	void CConsole::UnregisterVariable(uint32 nameHash)
	{
		TIVariablePtr pVariable = FindVariable(nameHash);

		if (pVariable != NULL)
		{
			m_variables.erase(nameHash);
			m_variableDetails.erase(nameHash);
		}
	}

	//============================================================================

	void CConsole::UnregisterVariable(TIVariablePtr&	pVariable)
	{
		for (TVariableMap::iterator it = m_variables.begin(), end = m_variables.end(); it != end; ++it)
		{
			if (it->second == pVariable)
			{
				m_variableDetails.erase(it->first);
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
		TIVariablePtr pVar;

		if (it != m_variables.end())
		{
			pVar = it->second;
		}

		return pVar;
	}

	//============================================================================

	CConsole::TIVariablePtr CConsole::FindVariable(const char* name)
	{
		return FindVariable(engine::CRunTimeStringHash::Calculate(name));
	}

	//============================================================================

	const CConsole::SVariableDetails* CConsole::FindDetails(uint32 nameHash)
	{
		SVariableDetails* pDetails = NULL;
		TVariableDetailsMap::iterator it = m_variableDetails.find(nameHash);

		if (it != m_variableDetails.end())
		{
			pDetails = it->second;
		}
		
		return pDetails;
	}

	//============================================================================

	const CConsole::SVariableDetails* CConsole::FindDetails(const char* name)
	{
		return FindDetails(engine::CRunTimeStringHash::Calculate(name));
	}

	//============================================================================

	void CConsole::AddDescription(uint32 nameHash, const char* name, const char* description)
	{
		SVariableDetails* pDetails = new SVariableDetails();
		if (pDetails != NULL)
		{
			pDetails->m_name = name;
			pDetails->m_description = description;
			m_variableDetails[nameHash] = pDetails;
		}
	}

	//============================================================================

} // End [namespace engine]

//==============================================================================
// EOF


