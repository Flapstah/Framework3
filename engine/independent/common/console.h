#if !defined(__CONSOLE_H__)
#define __CONSOLE_H__

//==============================================================================

#include <sstream>

//==============================================================================

namespace engine
{
	//============================================================================
	// CConsole
	//============================================================================
	class CConsole
	{
		//--------------------------------------------------------------------------
		public:
			CConsole(void) {};
			~CConsole(void) {};

			// TODO: storing the variable map
			// Store the variable map as a map of name hash and pointer to variable
			// Store a second map of name hash and pointer to name and description string
			// This will ensure we only store strings for those variables that have names
			// and descriptions (instead of spurious NULL pointers), and they're not easily
			// linked with the variable in the first place.
			struct SVariableDetails
			{
				const char* m_name;
				const char* m_description;
			}; // End [struct SVariableDetails]

			struct IVariable
			{
				//----------------------------------------------------------------------
				// Flags
				//----------------------------------------------------------------------
				enum eFlags
				{
					eF_ENFORCE_RANGE = BIT(0), // If set, this cvar has a range
					eF_RANGE_CLAMP = BIT(1), // If set, clamps new value to permitted range, otherwise out of range values are ignored
				}; // End [enum eFlags]

								IVariable(void) : m_flags(0) {}
				virtual ~IVariable(void) = 0;

				virtual int32 GetI32Val(void) const = 0;
				virtual int32 SetI32Val(int32 newValue) = 0;
				virtual float GetF32Val(void) const = 0;
				virtual float SetF32Val(float newValue) = 0;
				virtual const char* GetString(void) const = 0;
				virtual const char* SetString(const char* newValue) = 0;

				virtual uint32 GetFlags(void) const = 0;
				virtual uint32 SetFlags(uint32 newFlags) = 0;

				uint32 m_flags;
			}; // End [struct IVariable]
			
			class CI32Variable : public IVariable
			{
				public:
				typedef void (*OnChangeCallback)(int32 newValue);

				CI32Variable(int32& variable, OnChangeCallback pCallback = NULL)
					: m_pCallback(pCallback)
					, m_variable(variable)
#if defined(_DEBUG)
					, m_minValue(0)
					, m_maxValue(0)
#endif // defined(_DEBUG)
				{
				}

				virtual ~CI32Variable(void) {}

				// IVariable
				virtual int32 GetI32Val(void) const { return m_variable; }

				virtual int32 SetI32Val(int32 newValue)
				{
					int32 oldValue(m_variable);

					if (m_flags & eF_ENFORCE_RANGE)
					{
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
					}
					else
					{
						m_variable = newValue;
					}

					return oldValue;
				}

				virtual float GetF32Val(void) const
				{
					return static_cast<float>(m_variable);
				}

				virtual float SetF32Val(float newValue)
				{
					return static_cast<float>(SetI32Val(static_cast<int32>(newValue)));
				}

				virtual const char* GetString(void) const
				{
					std::ostringstream buffer;
					buffer << m_variable;
					return buffer.str().c_str();
				}

				virtual const char* SetString(const char* newValue)
				{
					std::string oldValue(GetString());
					SetI32Val(atoi(newValue));
					return oldValue.c_str();
				}

				virtual uint32 GetFlags(void) const { return m_flags; }
				virtual uint32 SetFlags(uint32 newFlags)
			 	{
				 	int32 oldflags = m_flags;
					m_flags = newFlags;
					return oldflags;
			 	}
				// ~IVariable

				protected:
				OnChangeCallback m_pCallback;
				int32& m_variable;
				int32 m_minValue;
				int32 m_maxValue;
			}; // End [class CI32Variable]

			class CF32Variable : public IVariable
			{
				public:
				typedef void (*OnChangeCallback)(float newValue);
				CF32Variable(float& variable, OnChangeCallback pCallback)
					: m_pCallback(pCallback)
					, m_variable(variable)
#if defined(_DEBUG)
					, m_minValue(minValue)
					, m_maxValue(maxValue)
#endif // defined(_DEBUG)
				{
				}

				virtual ~CF32Variable(void) {}

				// IVariable
				virtual int32 GetI32Val(void) const
				{
					return static_cast<int32>(m_variable);
				}

				virtual int32 SetI32Val(int32 newValue)
				{
					return static_cast<int32>(SetF32Val(static_cast<float>(newValue)));
				}

				virtual float GetF32Val(void) const { return m_variable; }

				virtual float SetF32Val(float newValue)
				{
					float oldValue(m_variable);

					if (m_flags & eF_ENFORCE_RANGE)
					{
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
					}
					else
					{
						m_variable = newValue;
					}

					return oldValue;
				}

				virtual const char* GetString(void) const
				{
					std::ostringstream buffer;
					buffer << m_variable;
					return buffer.str().c_str();
				}

				virtual const char* SetString(const char* newValue)
				{
					std::string oldValue(GetString());
					SetF32Val(atof(newValue));
					return oldValue.c_str();
				}

				virtual uint32 GetFlags(void) const { return m_flags; }
				virtual uint32 SetFlags(uint32 newFlags)
			 	{
				 	int32 oldflags = m_flags;
					m_flags = newFlags;
					return oldflags;
			 	}
				// ~IVariable

				protected:
				OnChangeCallback m_pCallback;
				float& m_variable;
				float m_minValue;
				float m_maxValue;
			}; // End [class CF32Variable]

			class CStringVariable : public IVariable
			{
				public:
				typedef void (*OnChangeCallback)(const char* newValue);

				CStringVariable(std::string& variable, OnChangeCallback pCallback)
					: m_pCallback(pCallback)
					, m_variable(variable)
				{
				}

				virtual ~CStringVariable(void) {};

				// IVariable
				virtual int32 GetI32Val(void) const
				{
					return atoi(m_variable.c_str());
				}

				virtual int32 SetI32Val(int32 newValue)
				{
					int32 oldValue = atoi(m_variable.c_str());
					std::ostringstream buffer;
					buffer << newValue;
					m_variable = buffer.str();
					return oldValue;
				}

				virtual float GetF32Val(void) const
				{
					return atof(m_variable.c_str());
				}

				virtual float SetF32Val(float newValue)
				{
					float oldValue = atof(m_variable.c_str());
					std::ostringstream buffer;
					buffer << newValue;
					m_variable = buffer.str();
					return oldValue;
				}

				virtual const char* GetString(void) const
				{
					return m_variable.c_str();
				}

				virtual const char* SetString(const char* newValue)
				{
					std::string oldValue(m_variable);
					m_variable = newValue;
					return oldValue.c_str();
				}

				virtual uint32 GetFlags(void) const { return m_flags; }
				virtual uint32 SetFlags(uint32 newFlags)
			 	{
				 	int32 oldflags = m_flags;
					m_flags = newFlags;
					return oldflags;
			 	}
				// ~IVariable

				protected:
				OnChangeCallback m_pCallback;
				std::string& m_variable;
			}; // End [class CStringVariable]

			CI32Variable* RegisterVariable(int32& variable, CI32Variable::OnChangeCallback pOnChangeCallback = NULL);
			CF32Variable* RegisterVariable(float& variable, CF32Variable::OnChangeCallback pOnChangeCallback = NULL);
			CStringVariable* RegisterVariable(std::string& variable, CStringVariable::OnChangeCallback pOnChangeCallback = NULL);

	}; // End [class CConsole]

} // End [namespace engine]

//==============================================================================

#endif // !defined(__CONSOLE_H__)
// EOF


