#if !defined(__CONSOLE_H__)
#define __CONSOLE_H__

//==============================================================================

#include <limits>
#include <map>
#include <sstream>
#include <boost/shared_ptr.hpp>
#include <boost/make_shared.hpp>
#include "common/runtimestringhash.h"

//==============================================================================

#define REGISTER_VARIABLE(_variable_, _value_, _flags_, _on_change_callback_, _description_) \
	engine::CConsole::Get().RegisterVariable(engine::CompileTimeStringHash(#_variable_), _variable_, _value_, _flags_, _on_change_callback_, #_variable_, _description_)

//------------------------------------------------------------------------------
// A "hidden" variable will have no plain text details stored when
// CONSOLE_HIDDEN_VARIABLES_ENABLED
//------------------------------------------------------------------------------
#if CONSOLE_HIDDEN_VARIABLES_ENABLED
#define REGISTER_HIDDEN_VARIABLE(_variable_, _value_, _flags_, _on_change_callback_, _description_) \
	engine::CConsole::Get().RegisterVariable(engine::CompileTimeStringHash(#_variable_), _variable_, _value_, _flags_, _on_change_callback_, NULL, NULL)
#else
#define REGISTER_HIDDEN_VARIABLE(_variable_, _value_, _flags_, _on_change_callback_, _description_) REGISTER_VARIABLE(_variable_, _value_, _flags_, _on_change_callback_, _description_)
#endif // CONSOLE_HIDDEN_VARIABLES_ENABLED

//------------------------------------------------------------------------------
// A "development" variable will only exist as a console variable when
// CONSOLE_DEVELOPMENT_VARIABLES_ENABLED
//------------------------------------------------------------------------------
#if CONSOLE_DEVELOPMENT_VARIABLES_ENABLED
#define REGISTER_DEBUG_VARIABLE(_variable_, _value_, _flags_, _on_change_callback_, _description_) REGISTER_VARIABLE(_variable_, _value_, _flags_, _on_change_callback_, _description_)
#else
#define REGISTER_DEBUG_VARIABLE(_variable_, _value_, _flags_, _on_change_callback_, _description_) _variable_ = (_value_);
#endif // DEVELOPMENT_CONSOLE_VARIABLES_ENABLED

#define UNREGISTER_VARIABLE_BY_NAME(_variable_) engine::CConsole::Get().UnregisterVariable(engine::CompileTimeStringHash(#_variable_))
#define UNREGISTER_VARIABLE_BY_POINTER(_tivariableptr_) engine::CConsole::Get().UnregisterVariable(_tivariableptr_)

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
			SINGLETON(CConsole);
			~CConsole(void);

			// TODO: storing the variable map
			// Store the variable map as a map of name hash and pointer to variable
			// Store a second map of name hash and pointer to name and description string
			// This will ensure we only store strings for those variables that have names
			// and descriptions (instead of spurious NULL pointers), and they're not easily
			// linked with the variable in the first place.
			struct SVariableDetails
			{
				std::string m_name;
				std::string m_description;
			}; // End [struct SVariableDetails]

			struct IVariable
			{
				//----------------------------------------------------------------------
				// Flags
				//----------------------------------------------------------------------
				enum eFlags
				{
					eF_CONST = BIT(0),		// If set, the mapped variable cannot be changed by
																// Get/Set methods (with the exception of variable
																// registration, where it's initial value *will*
																// be passed to Set (and any OnChange callback)
				}; // End [enum eFlags]

				virtual int64 GetInteger(void) const = 0;
				virtual int64 SetInteger(const int64 value) = 0;
				virtual double GetDouble(void) const = 0;
				virtual double SetDouble(const double value) = 0;
				virtual const char* GetString(void) const = 0;
				virtual const char* SetString(const char* value) = 0;

				virtual uint32 ModifyFlags(uint32 set, uint32 clear) = 0;
			}; // End [struct IVariable]

			//========================================================================
			// TVariable (maps a real variable to the console)
			//========================================================================
			template <typename _type_> class TVariable : public IVariable
			{
			public:
				typedef const _type_& (*OnChangeCallback)(const _type_& value);

				TVariable(_type_& variable, uint32 flags, OnChangeCallback pCallback = NULL);
				~TVariable(void);

				// IVariable
				virtual int64 GetInteger(void) const;
				virtual int64 SetInteger(const int64 value);
				virtual double GetDouble(void) const;
				virtual double SetDouble(const double value);
				virtual const char* GetString(void) const;
				virtual const char* SetString(const char* value);

				virtual uint32 ModifyFlags(uint32 set, uint32 clear);
				// ~IVariable

			protected:
				static const _type_& DefaultOnChange(const _type_& value);

			protected:
				_type_& m_variable;
				OnChangeCallback m_pCallback;
				uint32 m_flags;
			}; // End [template <typename _type_> class TVariable]
			//========================================================================

			typedef boost::shared_ptr<IVariable> TIVariablePtr;
			typedef TVariable<int64> TInteger;
			typedef TVariable<double> TDouble;
			typedef TVariable<std::string> TString;

			TIVariablePtr RegisterVariable(uint32 nameHash, int64& variable, int64 value, uint32 flags, TInteger::OnChangeCallback pOnChangeCallback = NULL, const char* name = NULL, const char* description = NULL);
			TIVariablePtr RegisterVariable(uint32 nameHash, double& variable, double value, uint32 flags, TDouble::OnChangeCallback pOnChangeCallback = NULL, const char* name = NULL, const char* description = NULL);
			TIVariablePtr RegisterVariable(uint32 nameHash, std::string& variable, const char* value, uint32 flags, TString::OnChangeCallback pOnChangeCallback = NULL, const char* name = NULL, const char* description = NULL);
			void UnregisterVariable(uint32 nameHash);
			void UnregisterVariable(TIVariablePtr& pVariable);

			TIVariablePtr FindVariable(uint32 nameHash);
			TIVariablePtr FindVariable(const char* name);

			const SVariableDetails* FindDetails(uint32 nameHash);
			const SVariableDetails* FindDetails(const char* name);

		protected:
			// Variables without a description cannot be searched for or tab completed.
			void AddDescription(uint32 nameHash, const char* name, const char* description);

		private:
			typedef std::map<uint32, TIVariablePtr> TVariableMap;
			typedef std::map<uint32, SVariableDetails*> TVariableDetailsMap;
			TVariableMap m_variables;
			TVariableDetailsMap m_variableDetails;
	}; // End [class CConsole]

} // End [namespace engine]

//==============================================================================

#endif // !defined(__CONSOLE_H__)
// EOF


