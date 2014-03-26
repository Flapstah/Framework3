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
			Initialise();
		}

		//==========================================================================

		CEngine::~CEngine(void)
		{
			Terminate();
		}

		//==========================================================================

		bool CEngine::Initialise(void)
		{
			bool ok = true;

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


