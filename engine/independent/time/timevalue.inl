#if !defined(__TIMEVALUE_INL__)
#define __TIMEVALUE_INL__

//==============================================================================

namespace engine
{
	//============================================================================

	namespace time
	{
		//==========================================================================

		extern const int64& TICKS_PER_SECOND;

		//==========================================================================

		inline CTimeValue::CTimeValue(void)
			: m_ticks(0)
		{
		}

		//==========================================================================

		inline CTimeValue::CTimeValue(int64 ticks)
			: m_ticks(ticks)
		{
		}

		//==========================================================================

		inline CTimeValue::CTimeValue(double seconds)
			: m_ticks(static_cast<int64>(seconds*TICKS_PER_SECOND))
		{
		}

		//==========================================================================

		inline CTimeValue::CTimeValue(const CTimeValue& other)
			: m_ticks(other.m_ticks)
		{
		}

		//==========================================================================

		inline CTimeValue& CTimeValue::operator=(const CTimeValue& other)
		{
			m_ticks = other.m_ticks;
			return *this;
		}

		//==========================================================================

		inline CTimeValue& CTimeValue::operator=(double seconds)
		{
			m_ticks = static_cast<int64>(seconds*TICKS_PER_SECOND);
			return *this;
		}

		//==========================================================================

		inline CTimeValue& CTimeValue::operator=(int64 ticks)
		{
			m_ticks = ticks;
			return *this;
		}

		//==========================================================================

		inline CTimeValue& CTimeValue::operator+=(const CTimeValue& other)
		{
			m_ticks += other.m_ticks;
			return *this;
		}

		//==========================================================================

		inline CTimeValue& CTimeValue::operator+=(double seconds)
		{
			m_ticks += static_cast<int64>(seconds*TICKS_PER_SECOND);
			return *this;
		}

		//==========================================================================

		inline CTimeValue& CTimeValue::operator+=(int64 ticks)
		{
			m_ticks += ticks;
			return *this;
		}

		//==========================================================================

		inline CTimeValue& CTimeValue::operator-=(const CTimeValue& other)
		{
			m_ticks -= other.m_ticks;
			return *this;
		}

		//==========================================================================

		inline CTimeValue& CTimeValue::operator-=(double seconds)
		{
			m_ticks -= static_cast<int64>(seconds*TICKS_PER_SECOND);
			return *this;
		}

		//==========================================================================

		inline CTimeValue& CTimeValue::operator-=(int64 ticks)
		{
			m_ticks -= ticks;
			return *this;
		}

		//==========================================================================

		inline const CTimeValue CTimeValue::operator+(const CTimeValue& other) const
		{
			CTimeValue result(m_ticks+other.m_ticks);
			return result;
		}

		//==========================================================================

		inline const CTimeValue CTimeValue::operator+(double seconds) const
		{
			CTimeValue result(m_ticks+static_cast<int64>(seconds*TICKS_PER_SECOND));
			return result;
		}

		//==========================================================================

		inline const CTimeValue CTimeValue::operator+(int64 ticks) const
		{
			CTimeValue result(m_ticks+ticks);
			return result;
		}

		//==========================================================================

		inline const CTimeValue CTimeValue::operator-(const CTimeValue& other) const
		{
			CTimeValue result(m_ticks-other.m_ticks);
			return result;
		}

		//==========================================================================

		inline const CTimeValue CTimeValue::operator-(double seconds) const
		{
			CTimeValue result(m_ticks-static_cast<int64>(seconds*TICKS_PER_SECOND));
			return result;
		}

		//==========================================================================

		inline const CTimeValue CTimeValue::operator-(int64 ticks) const
		{
			CTimeValue result(m_ticks-ticks);
			return result;
		}

		//==========================================================================

		inline bool CTimeValue::operator==(const CTimeValue& other) const
		{
			return (m_ticks == other.m_ticks);
		}

		//==========================================================================

		inline bool CTimeValue::operator==(double seconds) const
		{
			return (m_ticks == static_cast<int64>(seconds*TICKS_PER_SECOND));
		}

		//==========================================================================

		inline bool CTimeValue::operator==(int64 ticks) const
		{
			return (m_ticks == ticks);
		}

		//==========================================================================

		inline bool CTimeValue::operator!=(const CTimeValue& other) const
		{
			return (m_ticks != other.m_ticks);
		}

		//==========================================================================

		inline bool CTimeValue::operator!=(double seconds) const
		{
			return (m_ticks != static_cast<int64>(seconds*TICKS_PER_SECOND));
		}

		//==========================================================================

		inline bool CTimeValue::operator!=(int64 ticks) const
		{
			return (m_ticks != ticks);
		}

		//==========================================================================

		inline bool CTimeValue::operator<(const CTimeValue& other) const
		{
			return (m_ticks < other.m_ticks);
		}

		//==========================================================================

		inline bool CTimeValue::operator<(double seconds) const
		{
			return (m_ticks < seconds*TICKS_PER_SECOND);
		}

		//==========================================================================

		inline bool CTimeValue::operator<(int64 ticks) const
		{
			return (m_ticks < ticks);
		}

		//==========================================================================

		inline bool CTimeValue::operator<=(const CTimeValue& other) const
		{
			return (m_ticks <= other.m_ticks);
		}

		//==========================================================================

		inline bool CTimeValue::operator<=(double seconds) const
		{
			return (m_ticks <= seconds*TICKS_PER_SECOND);
		}

		//==========================================================================

		inline bool CTimeValue::operator<=(int64 ticks) const
		{
			return (m_ticks <= ticks);
		}

		//==========================================================================

		inline bool CTimeValue::operator>(const CTimeValue& other) const
		{
			return (m_ticks > other.m_ticks);
		}

		//==========================================================================

		inline bool CTimeValue::operator>(double seconds) const
		{
			return (m_ticks > seconds*TICKS_PER_SECOND);
		}

		//==========================================================================

		inline bool CTimeValue::operator>(int64 ticks) const
		{
			return (m_ticks > ticks);
		}

		//==========================================================================

		inline bool CTimeValue::operator>=(const CTimeValue& other) const
		{
			return (m_ticks >= other.m_ticks);
		}

		//==========================================================================

		inline bool CTimeValue::operator>=(double seconds) const
		{
			return (m_ticks >= seconds*TICKS_PER_SECOND);
		}	

		//==========================================================================

		inline bool CTimeValue::operator>=(int64 ticks) const
		{
			return (m_ticks >= ticks);
		}

		//==========================================================================

		inline double CTimeValue::GetSeconds(void) const
		{
			return static_cast<double>(m_ticks)/TICKS_PER_SECOND;
		}

		//==========================================================================

		inline int64 CTimeValue::GetTicks(void) const
		{
			return m_ticks;
		}

		//==========================================================================
	} // End [namespace time]

	//============================================================================
} // End [namespace engine]

//==============================================================================
#endif // End [!defined(__TIMEVALUE_INL__)]
// [EOF]


