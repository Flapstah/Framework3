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
			}; // End [enum eFlags]

			//------------------------------------------------------------------------

		public:
			SINGLETON(CEngine);
			virtual ~CEngine(void);

			//========================================================================
			// FPS
			//========================================================================
			// N.B. If GetAverageFPS() is called in the very first frame, you'll get a divide-by-zero exception
			inline float GetAverageFPS(void) { return m_fps.GetAverageFPS(); }
			inline float GetAverageFrameTime(void) { return m_fps.GetAverageFrameTime(); }
			inline float GetMinimumFrameTime(void) { return m_fps.GetMinimumFrameTime(); }
			inline float GetMaximumFrameTime(void) { return m_fps.GetMaximumFrameTime(); }
			//========================================================================

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
			engine::glfw::CGLFW* GetGLFW(void);
			engine::time::CTime* GetTime(void) const;
			engine::system::CConsole* GetConsole(void) const;

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

