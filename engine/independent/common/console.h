#if !defined(__CONSOLE_H__)
#define __CONSOLE_H__

//==============================================================================

#include <limits>
#include <map>
#include <sstream>
#include <boost/shared_ptr.hpp>
#include <boost/make_shared.hpp>
#include <boost/tokenizer.hpp>
#include "common/runtimestringhash.h"

//==============================================================================

#define REGISTER_VARIABLE(_variable_, _value_, _flags_, _on_change_callback_, _description_) \
	engine::CConsole::Get().RegisterVariable(engine::CompileTimeStringHash(#_variable_), _variable_, _value_, _flags_, _on_change_callback_, #_variable_, _description_)
#define REGISTER_NAMED_VARIABLE(_name_, _variable_, _value_, _flags_, _on_change_callback_, _description_) \
	engine::CConsole::Get().RegisterVariable(engine::CompileTimeStringHash(_name_), _variable_, _value_, _flags_, _on_change_callback_, _name_, _description_)
#define REGISTER_COMMAND(_flags_, _execute_callback_, _description_) \
	engine::CConsole::Get().RegisterCommand(engine::CompileTimeStringHash(#_execute_callback_), _flags_, _execute_callback_, #_execute_callback_, _description_)
#define REGISTER_NAMED_COMMAND(_command_, _flags_, _execute_callback_, _description_) \
	engine::CConsole::Get().RegisterCommand(engine::CompileTimeStringHash(_command_), _flags_, _execute_callback_, _command_, _description_)

//------------------------------------------------------------------------------
// A "hidden" variable/command will have no plain text details stored when
// CONSOLE_HIDDEN_VARIABLES_ENABLED
//------------------------------------------------------------------------------
#if CONSOLE_HIDDEN_VARIABLES_ENABLED
#define REGISTER_HIDDEN_VARIABLE(_variable_, _value_, _flags_, _on_change_callback_, _description_) \
	engine::CConsole::Get().RegisterVariable(engine::CompileTimeStringHash(#_variable_), _variable_, _value_, _flags_, _on_change_callback_, NULL, NULL)
#define REGISTER_HIDDEN_NAMED_VARIABLE(_name_, _variable_, _value_, _flags_, _on_change_callback_, _description_) \
	engine::CConsole::Get().RegisterVariable(engine::CompileTimeStringHash(_name_), _variable_, _value_, _flags_, _on_change_callback_, NULL, NULL)
#define REGISTER_HIDDEN_COMMAND(_flags_, _execute_callback_, _description_) \
	engine::CConsole::Get().RegisterCommand(engine::CompileTimeStringHash(#_execute_callback_), _flags_, _execute_callback_, NULL, NULL)
#define REGISTER_HIDDEN_NAMED_COMMAND(_command_, _flags_, _execute_callback_, _description_) \
	engine::CConsole::Get().RegisterCommand(engine::CompileTimeStringHash(_command_), _flags_, _execute_callback_, NULL, NULL)
#else
#define REGISTER_HIDDEN_VARIABLE(_variable_, _value_, _flags_, _on_change_callback_, _description_) REGISTER_VARIABLE(_variable_, _value_, _flags_, _on_change_callback_, _description_)
#define REGISTER_HIDDEN_NAMED_VARIABLE(_name_, _variable_, _value_, _flags_, _on_change_callback_, _description_) REGISTER_NAMED_VARIABLE(_name_, _variable_, _value_, _flags_, _on_change_callback_, _description_)
#define REGISTER_HIDDEN_COMMAND(_flags_, _execute_callback_, _description_) REGISTER_COMMAND(_flags_, _execute_callback_, _description_)
#define REGISTER_HIDDEN_NAMED_COMMAND(_command_, _flags_, _execute_callback_, _description_) REGISTER_NAMED_COMMAND(_command_, _flags_, _execute_callback_, _description_)
#endif // CONSOLE_HIDDEN_VARIABLES_ENABLED

//------------------------------------------------------------------------------
// A "development" variable/command will only exist in the console variable when
// CONSOLE_DEVELOPMENT_VARIABLES_ENABLED
//------------------------------------------------------------------------------
#if CONSOLE_DEVELOPMENT_VARIABLES_ENABLED
#define REGISTER_DEBUG_VARIABLE(_variable_, _value_, _flags_, _on_change_callback_, _description_) REGISTER_VARIABLE(_variable_, _value_, _flags_, _on_change_callback_, _description_)
#define REGISTER_DEBUG_NAMED_VARIABLE(_name_, _variable_, _value_, _flags_, _on_change_callback_, _description_) REGISTER_NAMED_VARIABLE(_name_, _variable_, _value_, _flags_, _on_change_callback_, _description_)
#define REGISTER_DEBUG_COMMAND(_flags_, _execute_callback_, _description_) REGISTER_COMMAND(_flags_, _execute_callback_, _description_)
#define REGISTER_DEBUG_NAMED_COMMAND(_command_, _flags_, _execute_callback_, _description_) REGISTER_NAMED_COMMAND(_command_, _flags_, _execute_callback_, _description_)
#else
#define REGISTER_DEBUG_VARIABLE(_variable_, _value_, _flags_, _on_change_callback_, _description_) _variable_ = (_value_)
#define REGISTER_DEBUG_NAMED_VARIABLE(_name_, _variable_, _value_, _flags_, _on_change_callback_, _description_) _variable_ = (_value_)
#define REGISTER_DEBUG_COMMAND(_flags_, _execute_callback_, _description_)
#define REGISTER_DEBUG_NAMED_COMMAND(_command_, _flags_, _execute_callback_, _description_)
#endif // DEVELOPMENT_CONSOLE_VARIABLES_ENABLED

#define UNREGISTER_VARIABLE(_variable_) engine::CConsole::Get().UnregisterVariable(engine::CompileTimeStringHash(#_variable_))
#define UNREGISTER_VARIABLE_BY_NAME(_variable_) engine::CConsole::Get().UnregisterVariable(engine::CompileTimeStringHash(_variable_))
#define UNREGISTER_VARIABLE_BY_POINTER(_tivariableptr_) engine::CConsole::Get().UnregisterVariable(_tivariableptr_)

#define UNREGISTER_COMMAND(_command_) engine::CConsole::Get().UnregisterCommand(engine::CompileTimeStringHash(#_command_))
#define UNREGISTER_COMMAND_BY_NAME(_command_) engine::CConsole::Get().UnregisterCommand(engine::CompileTimeStringHash(_command_))
#define UNREGISTER_COMMAND_BY_POINTER(_ticommandptr_) engine::CConsole::Get().UnregisterCommand(_ticommandptr_)

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

			//========================================================================
			// eConsoleState
			//========================================================================
			enum eConsoleState
			{
				eCS_OK,
				eCS_OUT_OF_MEMORY,
				eCS_TOO_MANY_ARGS,
				eCS_DEFERRED_QUEUE_FULL,
				eCS_NOT_FOUND,
				eCS_COMMAND_FAILED,
			}; // End [enum eConsoleState]

			//========================================================================
			// SDetails holds the name/description of a variable/command
			//========================================================================
			struct SDetails
			{
				std::string						m_name;
				std::string						m_description;
			}; // End [struct SDetails]

			//========================================================================
			// IVariable is the console variable interface
			//========================================================================
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

				virtual int64					GetInteger(void) const = 0;
				virtual int64					SetInteger(const int64 value) = 0;
				virtual double				GetDouble(void) const = 0;
				virtual double				SetDouble(const double value) = 0;
				virtual const char*		GetString(void) const = 0;
				virtual const char*		SetString(const char* value) = 0;

				virtual uint32				ModifyFlags(uint32 set, uint32 clear) = 0;
			}; // End [struct IVariable]
			//========================================================================

			//========================================================================
			// TVariable (maps a real variable to the console)
			//========================================================================
			template <typename _type_> class TVariable : public IVariable
			{
			public:
				typedef const _type_& (*OnChangeCallback)(const _type_& value);

				TVariable(_type_& variable, uint32 flags, OnChangeCallback pCallback = NULL);
				virtual ~TVariable(void);

				// IVariable
				virtual	int64					GetInteger(void) const;
				virtual	int64					SetInteger(const int64 value);
				virtual	double				GetDouble(void) const;
				virtual	double				SetDouble(const double value);
				virtual	const char*		GetString(void) const;
				virtual	const char*		SetString(const char* value);

				virtual	uint32				ModifyFlags(uint32 set, uint32 clear);
				// ~IVariable

			protected:
				static	const _type_&	DefaultOnChange(const _type_& value);

			protected:
				_type_&								m_variable;
				OnChangeCallback			m_pCallback;
				uint32								m_flags;
			}; // End [template <typename _type_> class TVariable]
			//========================================================================

			//========================================================================
			// ICommand is the console command interface
			//========================================================================
			struct ICommand
			{
				//----------------------------------------------------------------------
				// Flags
				//----------------------------------------------------------------------
				enum eFlags
				{
				}; // End [eFlags]

				typedef bool (*ExecuteCommandCallback)(std::vector<std::string>& argv);

				virtual bool Execute(std::vector<std::string>& argv) = 0;
			}; // End [stuct ICommand]

			//========================================================================
			// CCommand is the console command class
			//========================================================================
			class CCommand : public ICommand
			{
			public:

				CCommand(uint32 flags, ExecuteCommandCallback pCallback);
				virtual ~CCommand(void);

				// ICommand
				virtual bool Execute(std::vector<std::string>& argv);
				// ~ICommand

			protected:
				ExecuteCommandCallback	m_pCallback;
				uint32									m_flags;
			}; // End [class CCommand : public ICommand]

			//========================================================================

			//------------------------------------------------------------------------
			// Exposed types to make code more readable
			//------------------------------------------------------------------------
			typedef boost::shared_ptr<IVariable> TIVariablePtr;
			typedef TVariable<int64> TInteger;
			typedef TVariable<double> TDouble;
			typedef TVariable<std::string> TString;

			typedef ICommand* TICommandPtr;

			//------------------------------------------------------------------------
			// Registration methods for the variable types
			//------------------------------------------------------------------------
			TIVariablePtr		RegisterVariable(uint32 nameHash, int64& variable, int64 value, uint32 flags, TInteger::OnChangeCallback pOnChangeCallback = NULL, const char* name = NULL, const char* description = NULL);
			TIVariablePtr		RegisterVariable(uint32 nameHash, double& variable, double value, uint32 flags, TDouble::OnChangeCallback pOnChangeCallback = NULL, const char* name = NULL, const char* description = NULL);
			TIVariablePtr		RegisterVariable(uint32 nameHash, std::string& variable, const char* value, uint32 flags, TString::OnChangeCallback pOnChangeCallback = NULL, const char* name = NULL, const char* description = NULL);

			//------------------------------------------------------------------------
			// Unregister is type agnostic
			//------------------------------------------------------------------------
			void						UnregisterVariable(uint32 nameHash);
			void						UnregisterVariable(TIVariablePtr& pVariable);

			//------------------------------------------------------------------------
			// Find a variable by name or hash
			//------------------------------------------------------------------------
			TIVariablePtr		FindVariable(uint32 nameHash);
			TIVariablePtr		FindVariable(const char* name);

			//------------------------------------------------------------------------
			// Find variable details by name or hash
			//------------------------------------------------------------------------
			const SDetails*	FindDetails(uint32 nameHash);
			const SDetails*	FindDetails(const char* name);

			//------------------------------------------------------------------------
			// Registration/unregistration of commands
			//------------------------------------------------------------------------
			TICommandPtr		RegisterCommand(uint32 nameHash, uint32 flags, ICommand::ExecuteCommandCallback pExecuteCommandCallback, const char* name = NULL, const char* description = NULL);
			void						UnregisterCommand(uint32 nameHash);
			void						UnregisterCommand(TICommandPtr& pCommand);

			//------------------------------------------------------------------------
			// Find a variable by name or hash
			//------------------------------------------------------------------------
			TICommandPtr		FindCommand(uint32 nameHash);
			TICommandPtr		FindCommand(const char* name);

			//------------------------------------------------------------------------
			// Immediate execution of command (on calling thread)
			//------------------------------------------------------------------------
			eConsoleState		Execute(const char* commandLine);
			eConsoleState		Execute(std::string commandLine);

			//------------------------------------------------------------------------
			// Adds commands to the command buffer (processed FIFO, on console thread)
			//------------------------------------------------------------------------
			eConsoleState		ExecuteDeferred(const char* commandLine, uint32 frames);
			eConsoleState		ExecuteDeferred(const char* commandLine, float seconds);

		protected:
			// Variables and commands without a description cannot be searched for in
			// the console, or tab completed.
			void						AddDescription(uint32 nameHash, const char* name, const char* description);

		private:
			// Store the variable map as a map of name hash and pointer to variable
			typedef std::map<uint32, TIVariablePtr> TVariableMap;
			TVariableMap m_variables;
			// Store the command map as a map of name hash and pointer to command
			typedef std::map<uint32, TICommandPtr> TCommandMap;
			TCommandMap m_commands;
			// Store a second map of name hash and pointer to name and description
			// string
			typedef std::map<uint32, SDetails*> TDetailsMap;
			TDetailsMap m_details;
			// This will ensure we only store strings for those variables/commands
			// that have names and descriptions (instead of spurious NULL pointers),
			// and they're not easily linked with the source in the first place.

	}; // End [class CConsole]

} // End [namespace engine]

//==============================================================================

#endif // !defined(__CONSOLE_H__)
// EOF


