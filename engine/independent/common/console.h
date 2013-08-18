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

#define REGISTER_VARIABLE(_variable_, _on_change_callback_, _description_, _min_, _max_) \
	engine::CConsole::Get().RegisterVariable(engine::CRunTimeStringHash::Calculate(#_variable_), _variable_, _on_change_callback_, #_variable_, _description_, _min_, _max_)

#define REGISTER_HIDDEN_VARIABLE(_variable_, _on_change_callback_, _min_, _max_) \
	engine::CConsole::Get().RegisterVariable(engine::CRunTimeStringHash::Calculate(#_variable_), _variable_, _on_change_callback_, NULL, NULL, _min_, _max_)

#if defined(_DEBUG)
#define REGISTER_DEBUG_VARIABLE(_variable_, _on_change_callback_, _description_, _min_, _max_) REGISTER_VARIABLE(_variable_, _on_change_callback_, _description_, _min_, _max_)
#else
#define REGISTER_DEBUG_VARIABLE(_variable_, _on_change_callback_, _description_, _min_, _max_) REGISTER_HIDDEN_VARIABLE(_variable_, _on_change_callback_, _min_, _max_)
#endif // defined(_DEBUG)

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

			//========================================================================
			// IVariable
			//========================================================================
			struct IVariable
			{
				//----------------------------------------------------------------------
				// Flags
				//----------------------------------------------------------------------
				enum eFlags
				{
					eF_RANGE_CLAMP = BIT(0), // If set, clamps new value to permitted range, otherwise out of range values are ignored
				}; // End [enum eFlags]

				//----------------------------------------------------------------------
				// Type
				//----------------------------------------------------------------------
				enum eType
				{
					eT_FIRST,

					eT_I32 = eT_FIRST,
					eT_F32,
					eT_STRING,

					eT_MAX
				}; // End [enum eType]

				//----------------------------------------------------------------------
				// Interface
				//----------------------------------------------------------------------
				IVariable(eType type) : m_flags(0), m_type(type) { printf("IVariable()\n"); }
				virtual ~IVariable(void) { printf("~IVariable()\n"); }

				virtual int32 GetI32Val(void) const = 0;
				virtual int32 SetI32Val(int32 newValue) = 0;
				virtual float GetF32Val(void) const = 0;
				virtual float SetF32Val(float newValue) = 0;
				virtual const char* GetString(void) const = 0;
				virtual const char* SetString(const char* newValue) = 0;

				uint32 GetFlags(void) const;
				uint32 SetFlags(uint32 newFlags);

				uint32 GetType(void) const;

				protected:
				uint32 m_flags;
				eType m_type;
			}; // End [struct IVariable]
			
			//========================================================================
			// CI32Variable
			//========================================================================
			class CI32Variable : public IVariable
			{
				typedef IVariable PARENT;

				public:
				typedef void (*OnChangeCallback)(int32 newValue);

				CI32Variable(int32& variable, int32 minValue, int32 maxValue, OnChangeCallback pCallback = NULL);
				virtual ~CI32Variable(void);

				// IVariable
				virtual int32 GetI32Val(void) const;
				virtual int32 SetI32Val(int32 newValue);
				virtual float GetF32Val(void) const;
				virtual float SetF32Val(float newValue);
				virtual const char* GetString(void) const;
				virtual const char* SetString(const char* newValue);
				// ~IVariable

				protected:
				OnChangeCallback m_pCallback;
				int32& m_variable;
				int32 m_minValue;
				int32 m_maxValue;
			}; // End [class CI32Variable]

			//========================================================================
			// CF32Variable
			//========================================================================
			class CF32Variable : public IVariable
			{
				typedef IVariable PARENT;

				public:
				typedef void (*OnChangeCallback)(float newValue);

				CF32Variable(float& variable, int32 minValue, int32 maxValue, OnChangeCallback pCallback);
				virtual ~CF32Variable(void);

				// IVariable
				virtual int32 GetI32Val(void) const;
				virtual int32 SetI32Val(int32 newValue);
				virtual float GetF32Val(void) const;
				virtual float SetF32Val(float newValue);
				virtual const char* GetString(void) const;
				virtual const char* SetString(const char* newValue);
				// ~IVariable

				protected:
				OnChangeCallback m_pCallback;
				float& m_variable;
				float m_minValue;
				float m_maxValue;
			}; // End [class CF32Variable]

			//========================================================================
			// CStringVariable
			//========================================================================
			class CStringVariable : public IVariable
			{
				typedef IVariable PARENT;

				public:
				typedef void (*OnChangeCallback)(const char* newValue);

				CStringVariable(std::string& variable, OnChangeCallback pCallback);
				virtual ~CStringVariable(void);

				// IVariable
				virtual int32 GetI32Val(void) const;
				virtual int32 SetI32Val(int32 newValue);
				virtual float GetF32Val(void) const;
				virtual float SetF32Val(float newValue);
				virtual const char* GetString(void) const;
				virtual const char* SetString(const char* newValue);
				// ~IVariable

				protected:
				OnChangeCallback m_pCallback;
				std::string& m_variable;
			}; // End [class CStringVariable]

			typedef boost::shared_ptr<IVariable> TIVariablePtr;

			TIVariablePtr RegisterVariable(uint32 nameHash, int32& variable, CI32Variable::OnChangeCallback pOnChangeCallback = NULL, const char* name = NULL, const char* description = NULL, int32 minValue = std::numeric_limits<int32>::min(), int32 maxValue = std::numeric_limits<int32>::max());
			TIVariablePtr RegisterVariable(uint32 nameHash, float& variable, CF32Variable::OnChangeCallback pOnChangeCallback = NULL, const char* name = NULL, const char* description = NULL, float minValue = std::numeric_limits<float>::min(), float maxValue = std::numeric_limits<float>::max());
			TIVariablePtr RegisterVariable(uint32 nameHash, std::string& variable, CStringVariable::OnChangeCallback pOnChangeCallback = NULL, const char* name = NULL, const char* description = NULL, int32 dummyMinValue = 0, int32 dummyMaxValue = 0);
			void UnregisterVariable(uint32 nameHash);

			TIVariablePtr FindVariable(uint32 nameHash);
			TIVariablePtr FindVariable(const char* name);

			const SVariableDetails* FindDetails(uint32 nameHash);
			const SVariableDetails* FindDetails(const char* name);

		protected:
			void AddDescription(uint32 nameHash, const char* name, const char* description);

		private:
			typedef std::map<uint32, TIVariablePtr> TVariableMap;
			typedef std::map<uint32, SVariableDetails*> TVariableDetailsMap;
			TVariableMap m_variables;
			TVariableDetailsMap m_variableDetails;
			uint32 m_varCount[IVariable::eT_MAX];
	}; // End [class CConsole]

} // End [namespace engine]

//==============================================================================

#endif // !defined(__CONSOLE_H__)
// EOF


