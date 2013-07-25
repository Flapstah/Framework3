#if !defined(__CONSOLE_H__)
#define __CONSOLE_H__

//==============================================================================

#include <limits>
#include <map>
#include <sstream>
#include <boost/shared_ptr.hpp>
#include "common/runtimestringhash.h"

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

								IVariable(void) : m_flags(0) { printf("IVariable()\n"); }
				virtual ~IVariable(void) { printf("~IVariable()\n"); }

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
			
			typedef boost::shared_ptr<IVariable> TIVariablePtr;

			//========================================================================
			// CI32Variable
			//========================================================================
			class CI32Variable : public IVariable
			{
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
				virtual uint32 GetFlags(void) const;
				virtual uint32 SetFlags(uint32 newFlags);
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
				virtual uint32 GetFlags(void) const;
				virtual uint32 SetFlags(uint32 newFlags);
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
				virtual uint32 GetFlags(void) const;
				virtual uint32 SetFlags(uint32 newFlags);
				// ~IVariable

				protected:
				OnChangeCallback m_pCallback;
				std::string& m_variable;
			}; // End [class CStringVariable]

			TIVariablePtr RegisterVariable(uint32 nameHash, int32& variable, int32 minValue = std::numeric_limits<int32>::min(), int32 maxValue = std::numeric_limits<int32>::max(), CI32Variable::OnChangeCallback pOnChangeCallback = NULL, const char* name = NULL, const char* description = NULL);
			TIVariablePtr RegisterVariable(uint32 nameHash, float& variable, int32 minValue = std::numeric_limits<float>::min(), int32 maxValue = std::numeric_limits<float>::max(), CF32Variable::OnChangeCallback pOnChangeCallback = NULL, const char* name = NULL, const char* description = NULL);
			TIVariablePtr RegisterVariable(uint32 nameHash, std::string& variable, CStringVariable::OnChangeCallback pOnChangeCallback = NULL, const char* name = NULL, const char* description = NULL);

		private:
			std::map<uint32, TIVariablePtr> m_variables;
			std::map<uint32, SVariableDetails*> m_variableDetails;
	}; // End [class CConsole]

} // End [namespace engine]

//==============================================================================

#endif // !defined(__CONSOLE_H__)
// EOF


