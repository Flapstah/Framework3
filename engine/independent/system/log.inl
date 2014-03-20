#if !defined(__LOG_INL__)
#define __LOG_INL__

//==============================================================================

namespace engine
{
	//============================================================================

	inline bool CLog::IsActive(void) const
	{
		bool active = m_flags & eB_ACTIVE;
		return (active && ((m_pParent != NULL) ? m_pParent->IsActive() : active));
	}

	//============================================================================

	inline bool CLog::SetActive(bool set)
	{
		bool old = m_flags & eB_ACTIVE;
		(set) ? m_flags |= eB_ACTIVE : m_flags &= ~eB_ACTIVE;
		return old;
	}

	//============================================================================

	inline uint32 CLog::GetFlags(void) const
	{
		return m_flags;
	}

	//============================================================================

	inline uint32 CLog::SetFlags(uint32 flags)
	{
		uint32 old = m_flags;
		m_flags = flags;
		return old;
	}

	//============================================================================
} // End [namespace engine]

//==============================================================================
#endif // !defined(__LOG_INL__)
// EOF


