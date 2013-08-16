#include "common/stdafx.h"

#include "common/console.h"

//==============================================================================

namespace engine
{
	CConsole::CConsole(void)
	{
		for (uint32 index = IVariable::eT_FIRST; index < IVariable::eT_MAX; ++index)
		{
			m_varCount[index] = 0;
		}
	}

	//============================================================================

	CConsole::~CConsole(void)
	{
		for (uint32 index = IVariable::eT_FIRST; index < IVariable::eT_MAX; ++index)
		{
			if (m_varCount[index] != 0)
			{
				printf("[CONSOLE]: still have %d vars of type %d registered/n", m_varCount[index], index);
			}
		}

		for (TVariableMap::const_iterator it = m_variables.begin(), end = m_variables.end(); it != end; ++it)
		{
			printf("[CONSOLE]: still have variable %p registered\n", it->second.get());
		}
	}

	//============================================================================

	CConsole::TIVariablePtr CConsole::RegisterVariable(uint32 nameHash, int32& variable, CI32Variable::OnChangeCallback pOnChangeCallback /* = NULL */, const char* name /* = NULL */, const char* description /* = NULL */, int32 minValue /* = std::numeric_limits<int32>::min() */, int32 maxValue /* = std::numeric_limits<int32>::max() */)
	{
		boost::shared_ptr<CI32Variable> pVariable(new CI32Variable(variable, minValue, maxValue, pOnChangeCallback));
		if (pVariable != NULL)
		{
			m_variables[nameHash] = pVariable;
			++m_varCount[IVariable::eT_I32];
		}
		return pVariable;
	}

	//============================================================================

	CConsole::TIVariablePtr CConsole::RegisterVariable(uint32 nameHash, float& variable, CF32Variable::OnChangeCallback pOnChangeCallback /* = NULL */, const char* name /* = NULL */, const char* description /* = NULL */, float minValue /* = std::numeric_limits<float>::min */, float maxValue /* = std::numeric_limits<float>::max() */)
	{
		boost::shared_ptr<CF32Variable> pVariable(new CF32Variable(variable, minValue, maxValue, pOnChangeCallback));
		if (pVariable != NULL)
		{
			m_variables[nameHash] = pVariable;
			++m_varCount[IVariable::eT_F32];
		}
		return pVariable;
	}

	//============================================================================

	CConsole::TIVariablePtr CConsole::RegisterVariable(uint32 nameHash, std::string& variable, CStringVariable::OnChangeCallback pOnChangeCallback /* = NULL */, const char* name /* = NULL */, const char* description /* = NULL */, int32 dummyMinValue /* = 0 */, int32 dummyMaxValue /* = 0 */)
	{
		boost::shared_ptr<CStringVariable> pVariable(new CStringVariable(variable, pOnChangeCallback));
		if (pVariable != NULL)
		{
			m_variables[nameHash] = pVariable;
			++m_varCount[IVariable::eT_STRING];
		}
		return pVariable;
	}

	//============================================================================

	void CConsole::UnregisterVariable(uint32 nameHash)
	{
		TVariableMap::const_iterator it = m_variables.find(nameHash);
		if (it != m_variables.end())
		{
			--m_varCount[it->second->GetType()];
			m_variables.erase(nameHash);
		}

	}

	//============================================================================

	uint32 CConsole::IVariable::GetFlags(void) const
	{
		return m_flags;
	}

	//============================================================================

	uint32 CConsole::IVariable::SetFlags(uint32 newFlags)
	{
		uint32 oldFlags = m_flags;
		m_flags = newFlags;
		return oldFlags;
	}

	//============================================================================

	uint32 CConsole::IVariable::GetType(void) const
	{
		return m_type;
	}

	//============================================================================

	CConsole::CI32Variable::CI32Variable(int32& variable, int32 minValue, int32 maxValue, CConsole::CI32Variable::OnChangeCallback pCallback)
		: PARENT(eT_I32)
		,	m_pCallback(pCallback)
		, m_variable(variable)
		, m_minValue(minValue)
		, m_maxValue(maxValue)
	{
		printf("CI32Variable()\n");
	}

	//============================================================================

	CConsole::CI32Variable::~CI32Variable(void)
	{
		printf("~CI32Variable()\n");
	}

	//============================================================================

	int32 CConsole::CI32Variable::GetI32Val(void) const
 	{
	 	return m_variable;
 	}

	//============================================================================

	int32 CConsole::CI32Variable::SetI32Val(int32 newValue)
	{
		int32 oldValue(m_variable);

		if (newValue < m_minValue)
		{
			if (m_flags & eF_RANGE_CLAMP)
			{
				m_variable = m_minValue;
			}
		}
		else if (newValue > m_maxValue)
		{
			if (m_flags & eF_RANGE_CLAMP)
			{
				m_variable = m_maxValue;
			}
		}

		return oldValue;
	}

	//============================================================================

	float CConsole::CI32Variable::GetF32Val(void) const

	{
		return static_cast<float>(m_variable);
	}

	//============================================================================

	float CConsole::CI32Variable::SetF32Val(float newValue)
	{
		return static_cast<float>(SetI32Val(static_cast<int32>(newValue)));
	}

	//============================================================================

	const char* CConsole::CI32Variable::GetString(void) const
	{
		std::ostringstream buffer;
		buffer << m_variable;
		return buffer.str().c_str();
	}

	//============================================================================

	const char* CConsole::CI32Variable::SetString(const char* newValue)
	{
		std::string oldValue(GetString());
		SetI32Val(atoi(newValue));
		return oldValue.c_str();
	}

	//============================================================================

	CConsole::CF32Variable::CF32Variable(float& variable, int32 minValue, int32 maxValue, CConsole::CF32Variable::OnChangeCallback pCallback)
		: PARENT(eT_F32)
		, m_pCallback(pCallback)
		, m_variable(variable)
		, m_minValue(minValue)
		, m_maxValue(maxValue)
	{
		printf("CF32Variable()\n");
	}

	//============================================================================

	CConsole::CF32Variable::~CF32Variable(void)
 	{
		printf("~CF32Variable()\n");
	}

	//============================================================================

	int32 CConsole::CF32Variable::GetI32Val(void) const
	{
		return static_cast<int32>(m_variable);
	}

	//============================================================================

	int32 CConsole::CF32Variable::SetI32Val(int32 newValue)
	{
		return static_cast<int32>(SetF32Val(static_cast<float>(newValue)));
	}

	//============================================================================

	float CConsole::CF32Variable::GetF32Val(void) const
 	{
	 	return m_variable;
 	}

	//============================================================================

	float CConsole::CF32Variable::SetF32Val(float newValue)
	{
		float oldValue(m_variable);

		if (newValue < m_minValue)
		{
			if (m_flags & eF_RANGE_CLAMP)
			{
				m_variable = m_minValue;
			}
		}
		else if (newValue > m_maxValue)
		{
			if (m_flags & eF_RANGE_CLAMP)
			{
				m_variable = m_maxValue;
			}
		}

		return oldValue;
	}

	//============================================================================

	const char* CConsole::CF32Variable::GetString(void) const
	{
		std::ostringstream buffer;
		buffer << m_variable;
		return buffer.str().c_str();
	}

	//============================================================================

	const char* CConsole::CF32Variable::SetString(const char* newValue)
	{
		std::string oldValue(GetString());
		SetF32Val(atof(newValue));
		return oldValue.c_str();
	}

	//============================================================================

	CConsole::CStringVariable::CStringVariable(std::string& variable, CConsole::CStringVariable::OnChangeCallback pCallback)
		: PARENT(eT_STRING)
		, m_pCallback(pCallback)
		, m_variable(variable)
	{
		printf("CStringVariable()\n");
	}

	//============================================================================

	CConsole::CStringVariable::~CStringVariable(void)
 	{
		printf("~CStringVariable()\n");
	};

	//============================================================================

	int32 CConsole::CStringVariable::GetI32Val(void) const
	{
		return atoi(m_variable.c_str());
	}

	//============================================================================

	int32 CConsole::CStringVariable::SetI32Val(int32 newValue)
	{
		int32 oldValue = atoi(m_variable.c_str());
		std::ostringstream buffer;
		buffer << newValue;
		m_variable = buffer.str();
		return oldValue;
	}

	//============================================================================

	float CConsole::CStringVariable::GetF32Val(void) const
	{
		return atof(m_variable.c_str());
	}

	//============================================================================

	float CConsole::CStringVariable::SetF32Val(float newValue)
	{
		float oldValue = atof(m_variable.c_str());
		std::ostringstream buffer;
		buffer << newValue;
		m_variable = buffer.str();
		return oldValue;
	}

	//============================================================================

	const char* CConsole::CStringVariable::GetString(void) const
	{
		return m_variable.c_str();
	}

	//============================================================================

	const char* CConsole::CStringVariable::SetString(const char* newValue)
	{
		std::string oldValue(m_variable);
		m_variable = newValue;
		return oldValue.c_str();
	}

	//============================================================================
} // End [namespace engine]

//==============================================================================
// EOF


