#if !defined(__LOG_INL__)
#define __LOG_INL__

//==============================================================================

namespace engine
{
	//============================================================================

	inline bool CLog::IsActive(void) const
	{
		return (m_active && ((m_pParent != NULL) ? m_pParent->IsActive() : m_active));
	}

	//============================================================================

	inline bool CLog::SetActive(bool set)
	{
		bool old = m_active;
		m_active = set;
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


