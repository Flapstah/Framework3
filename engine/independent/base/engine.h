#if !defined(__ENGINE_H__)
#define __ENGINE_H__

//==============================================================================

#include "base/filesystem.h"
#include "glfw/glfw.h"
#include "system/configuration.h"
#include "system/console.h"
#include "time/time.h"
#include "time/fpscalculator.h"

//==============================================================================

namespace engine
{
	//============================================================================

	namespace base
	{
		//==========================================================================
		// CEngine
		//==========================================================================
		class CEngine
		{
			//========================================================================

		public:
			enum eFlags
			{
				eF_INITIALISED = 1 << 0,
				eF_SIGNAL_TERMINATE = 1 << 1,
			}; // End [enum eFlags]

			//------------------------------------------------------------------------

		public:
			SINGLETON(CEngine);
			virtual ~CEngine(void);

			//========================================================================
			// Lifecycle
			//========================================================================
			bool Initialise(engine::system::CConfiguration& config);
			engine::time::CTimeValue Update(void);
			bool Uninitialise(void);
			bool Terminate(void);

			//========================================================================
			// Systems
			//========================================================================
			engine::base::CFileSystem* GetFileSystem(void) const;
			engine::glfw::CGLFW* GetGLFW(void) const;
			engine::time::CTime* GetTime(void) const;
			engine::system::CConsole* GetConsole(void) const;
			const engine::time::CFPSCalculator* GetFPS(void) const;

			//========================================================================
			// Accessors
			//========================================================================

			//------------------------------------------------------------------------

		protected:
			uint32 m_flags;
			engine::time::CFPSCalculator m_fps;

			//========================================================================
		}; // End [class CEngine]

		//==========================================================================
	} // End [namespace base]

	//============================================================================
} // End [namespace engine]

//==============================================================================
#endif // End [!defined(__ENGINE_H__)]
// EOF

