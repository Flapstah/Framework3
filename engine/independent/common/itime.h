#if !defined(__ITIME_H__)
#define __ITIME_H__

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


		//==========================================================================
		// ITimer
		//==========================================================================
		struct ITimer
		{
			typedef bool (*TimerCallback)(ITimer*, void* const);

			virtual CTimeValue GetCurrentTime(void) const = 0;
			virtual CTimeValue GetElapsedTime(void) const = 0;
			virtual CTimeValue GetFrameTime(void) const = 0;
			virtual float GetMaxFrameTime(void) const = 0;
			virtual void SetMaxFrameTime(float maxFrameTime) = 0;
			virtual void SetScale(float scale) = 0;
			virtual float GetScale(void) const = 0;
			virtual void Pause(bool pause) = 0;
			virtual bool IsPaused(void) = 0;
			virtual void SuspendCallbacks(bool suspend) = 0;
			virtual bool HasSuspendedCallbacks(void) = 0;
			virtual void Reset(const CTimeValue& when) = 0;
			virtual void SetCallbackInterval(const CTimeValue& interval) = 0;
			virtual const CTimeValue& GetCallbackInterval(void) = 0;
		}; // End [struct ITimer]
		//==========================================================================


		//==========================================================================
		// ITime
		//==========================================================================
		struct ITime
		{
			virtual	const CTimeValue Update(void) = 0;
			virtual const CTimeValue GetCurrentTime(void) const = 0;
			virtual ITimer* CreateTimer(ITimer& parent, float maxFrameTime, float scale, CTimeValue& callbackInterval, ITimer::TimerCallback pCallback, void* const pUserData) = 0;
			virtual void Sleep(uint32 microseconds) = 0;
		}; // End [struct ITime]
		//==========================================================================

		//==========================================================================
		// Get the ITime interface
		//==========================================================================
		ITime* GetITime(void);

		//==========================================================================
	} // End [namespace time]

	//============================================================================
} // End [namespace engine]

#include "common/itime.inl"

//==============================================================================
#endif // End [!defined(__ITIME_H__)]
// [EOF]


