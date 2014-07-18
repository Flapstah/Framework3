#if !defined(__CALLBACK_H__)
#define __CALLBACK_H__

//==============================================================================

namespace engine
{
	//============================================================================

	namespace utility
	{
		//==========================================================================

		class CCallbackBase
		{
		public:
			virtual void operator()(void) const {}
			virtual void operator()(void* pParam1) const { IGNORE_PARAMETER(pParam1); }
			virtual void operator()(void* pParam1, void* pParam2) const { IGNORE_PARAMETER(pParam1); IGNORE_PARAMETER(pParam2);  }
			virtual void operator()(void* pParam1, void* pParam2, void* pParam3) const { IGNORE_PARAMETER(pParam1); IGNORE_PARAMETER(pParam2); IGNORE_PARAMETER(pParam3);   }
			virtual ~CCallbackBase() {}
		};

		//==========================================================================

		template <typename T>
		class CCallback : public CCallbackBase
		{
		public:
			typedef void (T::*F)(void);

			CCallback(void) : m_o(NULL), m_f(NULL) {}
			CCallback(T& o, F f) : m_o(&o), m_f(f) {}
			virtual void operator()(void) const { (m_o->*m_f)(); }

		private:
			T* m_o;
			F m_f;
		};

		//==========================================================================

		template <typename T, typename P1>
		class CUnaryCallback : public CCallbackBase
		{
		public:
			typedef void (T::*F)(P1*);

			CUnaryCallback(void) : m_o(NULL), m_f(NULL) {}
			CUnaryCallback(T& o, F f) : m_o(&o), m_f(f) {}
			virtual void operator()(void* p1) const { (m_o->*m_f)((P1*)p1); }

		private:
			T* m_o;
			F m_f;
		};

		//==========================================================================

		template <typename T, typename P1, typename P2>
		class CBinaryCallback : public CCallbackBase
		{
		public:
			typedef void (T::*F)(P1*, P2*);

			CBinaryCallback(void) : m_o(NULL), m_f(NULL) {}
			CBinaryCallback(T& o, F f) : m_o(&o), m_f(f) {}
			virtual void operator()(void* p1, void* p2) const { (m_o->*m_f)((P1*)p1, (P2*)p2); }

		private:
			T* m_o;
			F m_f;
		};

		//==========================================================================
		template <typename T, typename P1, typename P2, typename P3>
		class CTertiaryCallback : public CCallbackBase
		{
		public:
			typedef void (T::*F)(P1*, P2*, P3*);

			CTertiaryCallback(void) : m_o(NULL), m_f(NULL) {}
			CTertiaryCallback(T& o, F f) : m_o(&o), m_f(f) {}
			virtual void operator()(void* p1, void* p2, void* p3) const { (m_o->*m_f)((P1*)p1, (P2*)p2, (P3*)p3); }

		private:
			T* m_o;
			F m_f;
		};

		//==========================================================================

		template<typename T>
		CCallback<T> MakeCallback(T& o, void (T::*f)())
		{
			return CCallback<T>(o, f);
		}

		//==========================================================================

		template<typename T, typename P1>
		CUnaryCallback<T, P1> MakeUnaryCallback(T& o, void (T::*f)(P1*))
		{
			return CUnaryCallback<T, P1>(o, f);
		}

		//==========================================================================

		template<typename T, typename P1, typename P2>
		CBinaryCallback<T, P1, P2> MakeBinaryCallback(T& o, void (T::*f)(P1*, P2*))
		{
			return CBinaryCallback<T, P1, P2>(o, f);
		}

		//==========================================================================

		template<typename T, typename P1, typename P2, typename P3>
		CTertiaryCallback<T, P1, P2, P3> MakeTertiaryCallback(T& o, void (T::*f)(P1*, P2*, P3*))
		{
			return CTertiaryCallback<T, P1, P2, P3>(o, f);
		}

		//==========================================================================
	} // End [namespace utility]

	//============================================================================
} // End [namespace engine]

//==============================================================================
#endif // End [!defined(__CALLBACK_H__)]
// EOF

