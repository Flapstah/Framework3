#include "common/stdafx.h" // log.h included here

#include "base/engine.h"

//==============================================================================

namespace engine
{
	//============================================================================

	namespace base
	{
		//==========================================================================

		CEngine::CEngine(void)
			: m_flags(0)
		{
		}

		//==========================================================================

		CEngine::~CEngine(void)
		{
			Terminate();
		}

		//==========================================================================

		bool CEngine::Initialise(int argc, char* argv[])
		{
			bool ok = true;

			// Initialise the CTime singleton by accessing it (it will be instanced)
			time::CTime::Get();

			if (ok)
			{
				m_flags |= eF_INITIALISED;
			}

			return ok;
		}

		//==========================================================================

		engine::time::CTimeValue CEngine::Update(void)	
		{
			engine::time::CTimeValue tickTime;

			if (m_flags & eF_INITIALISED)
			{
				tickTime = time::CTime::Get().Update();
			}

			return tickTime;
		}

		//==========================================================================

		bool CEngine::Uninitialise(void)
		{
			m_flags &= ~eF_INITIALISED;
			return true;
		}

		//==========================================================================

		bool CEngine::Terminate(void)
		{
			Uninitialise();

			return true;
		}

		//==========================================================================

		engine::time::CTime* CEngine::GetTime(void)
		{
			return (m_flags & eF_INITIALISED) ? &time::CTime::Get() : NULL;
		}

		//==========================================================================
	} // End [namespace base]

	//============================================================================
} // End [namespace engine]

//==============================================================================
// EOF


