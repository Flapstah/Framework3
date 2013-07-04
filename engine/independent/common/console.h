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
			CConsole(void);
			~CConsole(void);

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

			// Intended supported types:
			// int32, float and ostrstream
			template <class _type_> class CVariable
			{
				public:
					typedef bool (*OnChangeCallback)(CVariable& variable, const _type_& newValue);

				private:
					//--------------------------------------------------------------------
					// Lifetime
					//--------------------------------------------------------------------
					CVariable(_type_& variable, OnChangeCallback pOnChangeCallback = NULL)
						: m_pOnChangedCallback(pOnChangeCallback)
						, m_variable(variable)
#if defined(_DEBUG)
						, m_minimum(0)
						, m_maximum(0)
#endif // defined(_DEBUG)
						, m_flags(0)
					{
					}

					~CVariable(void)
					{
					}

				public:
					//--------------------------------------------------------------------
					// Behaviours
					//--------------------------------------------------------------------
					void SetRange(_type_& minimum, _type_& maximum, bool clamp)
					{
						m_minimum = minimum;
						m_maximum = maximum;

						m_flags |= eF_HAS_RANGE;
						if (clamp)
						{
							m_flags |= eF_CLAMP_TO_RANGE;
						}
					}

					//--------------------------------------------------------------------
					// Mutators
					//--------------------------------------------------------------------
					const _type_& Get(void)
					{
						return m_variable;
					}

					const char* const GetString(void)
					{
						std::ostringstream buffer;
						buffer << m_variable;
						return buffer.str().c_str();
					}

					const _type_& Set(_type_& newValue)
					{
						_type_ oldValue = m_variable;
						bool set = false;

						if (m_pOnChangedCallback != NULL)
						{
							if (m_pCallback(this, newValue) == true)
							{
								// If we have an on changed callback, and it returns true, then set the new value
								set = true;
							}
						}
						else
						{
							// No callback so just set the value
							set = true;
						}

						if (set == true)
						{
							if ((m_flags & eF_HAS_RANGE) == eF_HAS_RANGE)
							{
								if ((m_flags & eF_CLAMP_TO_RANGE) == eF_CLAMP_TO_RANGE)
								{
									// Either clamp the new value...
									m_variable = min(max(newValue, m_minimum), m_maximum);
								}
								else
								{
									// ...or discard if out of range
									if ((newValue >= m_minimum) && (newValue <= m_maximum))
									{
										m_variable = newValue;
									}
								}
							}
							else
							{
								m_variable = value;
							}
						}

						return oldValue;
					}

				private:
					//--------------------------------------------------------------------
					// Flags
					//--------------------------------------------------------------------
					enum eFlags
					{
						eF_HAS_RANGE = BIT(0), // If set, a range is enforced
						eF_CLAMP_TO_RANGE = BIT(0), // If set and a range is enforced, clamps new value to permitted range, otherwise out of range values are ignored
					}; // End [enum eFlags]

					OnChangeCallback m_pOnChangedCallback;
					_type_& m_variable;
					_type_ m_minimum;
					_type_ m_maximum;
					uint32 m_flags;
			}; // End [template <class _type_> class CVariable]

			bool RegisterVariable(int32& variable, const char* name, const char* description, CVariable<int32>::OnChangeCallback pOnChangeCallback);
			bool RegisterVariable(float& variable, const char* name, const char* description, CVariable<float>::OnChangeCallback pOnChangeCallback);
			bool RegisterVariable(std::ostrstream& variable, const char* name, const char* description, CVariable<std::ostrstream>::OnChangeCallback pOnChangeCallback);

			/*
			struct IVariable
			{
				enum eFlags
				{
					eF_CLAMP_TO_RANGE = 1 << 0, // If set, clamps new value to permitted range, otherwise out of range values are ignored
				}; // End [enum eFlags]
				IVariable(void)	{ printf("Registering console variable\n"); // CConsole::Get()->Register(this); }
				virtual ~IVariable(void) { printf("Unregistering console variable\n"); // CConsole::Get()->Unregister(this); }

				virtual int32 GetI32Val(void) const = 0;
				virtual int32 SetI32Val(int32 newValue) = 0;
				virtual float GetF32Val(void) const = 0;
				virtual float SetF32Val(float newValue) = 0;
				virtual const char* GetString(void) const = 0;
				virtual const char* SetString(const char* newValue) = 0;

				virtual uint32 GetFlags(void) const = 0;
				virtual uint32 SetFlags(uint32 newFlags) = 0;

				virtual const char* GetName(void) const = 0;
				virtual const char* GetDescription(void) const = 0;

				typedef void (*TOnChangeI32)(int32 newValue);
				typedef void (*TOnChangeF32)(float newValue);
				typedef void (*TOnChangeString)(const char* newValue);
				union TOnChangeCallback
				{
					TOnChangeI32 m_pOnChangeI32;
					TOnChangeF32 m_pOnChangeF32;
					TOnChangeString m_pOnChangeString;
				}; // End [union TOnChangeCallback]
			}; // End [struct IVariable]
			
			class CI32Variable : public IVariable
			{
				public:
				CI32Variable(int32& variable, int32 initialValue, int32 minValue, int32 maxValue, uint32 flags, const char* name, const char* description, TOnChangeCallback pCallback)
					: m_name(name)
					, m_description(description)
					, m_pCallback(pCallback.m_pOnChangeI32)
					, m_variable(variable)
					, m_minValue(minValue)
					, m_maxValue(maxValue)
					, m_flags(flags)
				{
					SetI32Val(initialValue);
				}

				virtual ~CI32Variable(void) {}

				// IVariable
				virtual int32 GetI32Val(void) const { return m_variable; }

				virtual int32 SetI32Val(int32 newValue)
				{
					int32 oldValue(m_variable);

					if (newValue < m_minValue)
					{
						if (m_flags & eF_CLAMP_TO_RANGE)
						{
							m_variable = m_minValue;
						}
					}
					else if (newValue > m_maxValue)
					{
						if (m_flags & eF_CLAMP_TO_RANGE)
						{
							m_variable = m_maxValue;
						}
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

				virtual const char* GetName(void) const { return m_name; }
				virtual const char* GetDescription(void) const { return m_description; }
				// ~IVariable

				protected:
				const char* m_name;
				const char* m_description;
				TOnChangeI32 m_pCallback;
				int32& m_variable;
				int32 m_minValue;
				int32 m_maxValue;
				uint32 m_flags;
			}; // End [class CI32Variable]

			class CF32Variable : public IVariable
			{
				public:
				CF32Variable(float& variable, float initialValue, float minValue, float maxValue, uint32 flags, const char* name, const char* description, TOnChangeCallback pCallback)
					: m_name(name)
					, m_description(description)
					, m_pCallback(pCallback.m_pOnChangeF32)
					, m_variable(variable)
					, m_minValue(minValue)
					, m_maxValue(maxValue)
					, m_flags(flags)
				{
					SetF32Val(initialValue);
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

					if (newValue < m_minValue)
					{
						if (m_flags & eF_CLAMP_TO_RANGE)
						{
							m_variable = m_minValue;
						}
					}
					else if (newValue > m_maxValue)
					{
						if (m_flags & eF_CLAMP_TO_RANGE)
						{
							m_variable = m_maxValue;
						}
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

				virtual const char* GetName(void) const { return m_name; }
				virtual const char* GetDescription(void) const { return m_description; }
				// ~IVariable

				protected:
				const char* m_name;
				const char* m_description;
				TOnChangeF32 m_pCallback;
				float& m_variable;
				float m_minValue;
				float m_maxValue;
				uint32 m_flags;
			}; // End [class CF32Variable]

			class CStringVariable : public IVariable
			{
				public:
				CStringVariable(std::string& variable, const char* initialValue, uint32 flags, const char* name, const char* description, TOnChangeCallback pCallback)
					: m_name(name)
					, m_description(description)
					, m_pCallback(pCallback.m_pOnChangeString)
					, m_variable(variable)
					, m_flags(flags)
				{
					m_variable = initialValue;
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

				virtual const char* GetName(void) const { return m_name; }
				virtual const char* GetDescription(void) const { return m_description; }
				// ~IVariable

				protected:
				const char* m_name;
				const char* m_description;
				TOnChangeString m_pCallback;
				std::string& m_variable;
				uint32 m_flags;
			}; // End [class CStringVariable]
			*/

	}; // End [class CConsole]

} // End [namespace engine]

//==============================================================================

#endif // !defined(__CONSOLE_H__)
// EOF


