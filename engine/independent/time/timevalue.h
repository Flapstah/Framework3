#if !defined(__TIMEVALUE_H__)
#define __TIMEVALUE_H__

//==============================================================================

namespace engine
{
	//============================================================================

	namespace time
	{
		//==========================================================================
		// CTimeValue
		//==========================================================================
		class CTimeValue
		{
			public:
				//======================================================================
				// CTimeValue constructors
				//======================================================================
				CTimeValue(void);
				explicit CTimeValue(int64 ticks);
				explicit CTimeValue(double seconds);
				CTimeValue(const CTimeValue& other);

				//======================================================================
				// CTimeValue overloaded operators
				//======================================================================
				CTimeValue& operator=(const CTimeValue& other);
				CTimeValue& operator=(double seconds);
				CTimeValue& operator=(int64 ticks);

				CTimeValue& operator+=(const CTimeValue& other);
				CTimeValue& operator+=(double seconds);
				CTimeValue& operator+=(int64 ticks);

				CTimeValue& operator-=(const CTimeValue& other);
				CTimeValue& operator-=(double seconds);
				CTimeValue& operator-=(int64 ticks);

				const CTimeValue operator+(const CTimeValue& other) const;
				const CTimeValue operator+(double seconds) const;
				const CTimeValue operator+(int64 ticks) const;

				const CTimeValue operator-(const CTimeValue& other) const;
				const CTimeValue operator-(double seconds) const;
				const CTimeValue operator-(int64 ticks) const;

				bool operator==(const CTimeValue& other) const;
				bool operator==(double seconds) const;
				bool operator==(int64 ticks) const;

				bool operator!=(const CTimeValue& other) const;
				bool operator!=(double seconds) const;
				bool operator!=(int64 ticks) const;

				bool operator<(const CTimeValue& other) const;
				bool operator<(double seconds) const;
				bool operator<(int64 ticks) const;

				bool operator<=(const CTimeValue& other) const;
				bool operator<=(double seconds) const;
				bool operator<=(int64 ticks) const;

				bool operator>(const CTimeValue& other) const;
				bool operator>(double seconds) const;
				bool operator>(int64 ticks) const;

				bool operator>=(const CTimeValue& other) const;
				bool operator>=(double seconds) const;
				bool operator>=(int64 ticks) const;

				//======================================================================
				// GetSeconds() returns the number of seconds represented by this
				// instance
				//======================================================================
				double GetSeconds(void) const;

				//======================================================================
				// GetTicks() returns the number of ticks represented by this instance
				//======================================================================
				int64 GetTicks(void) const;

				//======================================================================
				// GetTime() deconstructs the time represented by this instance
				// N.B. This always returns absolute time; determine sign with
				// GetTicks()
				//======================================================================
				void GetTime(int32& days, int32& hours, int32& minutes, float& seconds);

			protected:
				int64 m_ticks;
		}; // End [class CTimeValue]

		extern const CTimeValue INVALID_TIME;

		//==========================================================================
	} // End [namespace time]

	//============================================================================
} // End [namespace engine]

#include "time/timevalue.inl"

//==============================================================================
#endif // End [!defined(__TIMEVALUE_H__)]
// [EOF]

