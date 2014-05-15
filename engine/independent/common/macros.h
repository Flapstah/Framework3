#if !defined(__MACROS_H__)
#define __MACROS_H__

//==============================================================================

//------------------------------------------------------------------------------
// Create environment independent 64 bit literals
//------------------------------------------------------------------------------
#if defined(ENVIRONMENT32)
	#define DECLARE_64BIT(_val_) static_cast<int64>(_val_##ll)
#elif defined(ENVIRONMENT64)
	#define DECLARE_64BIT(_val_) static_cast<int64>(_val_##l)
#else
	#error Unable to determine compilation environment (neither ENVIRONMENT32 or ENVIRONMENT64 defined)
#endif // [defined(ENVIRONMENT32)]

//------------------------------------------------------------------------------
// Prevent copy constructor and assignment operator
//------------------------------------------------------------------------------
#define PREVENT_CLASS_COPY(_class_) \
	private: \
		_class_(const _class_&); \
		_class_& operator = (const _class_&); \
	public:

//------------------------------------------------------------------------------
// Create a singleton class with a public Get(), and private constructor, copy
// constructor and assignment operator
//------------------------------------------------------------------------------
#define SINGLETON(_class_) \
	private: \
		_class_(void); \
		PREVENT_CLASS_COPY(_class_) \
	public: \
		static _class_& Get(void) \
		{ \
			static _class_ instance; \
			return instance; \
		}

//------------------------------------------------------------------------------
// Prevent instancing this class
//------------------------------------------------------------------------------
#define PREVENT_CLASS_INSTANCE virtual void YouCannotInstanceThisClass(void) = 0

//------------------------------------------------------------------------------
// Prevent compiler warnings for intentionally unreferenced parameters
//------------------------------------------------------------------------------
#define IGNORE_PARAMETER(_parameter_) (void)(_parameter_)

//------------------------------------------------------------------------------
// Use STRINGIZE() to get a string version of a macro's value
// e.g:
// #define SOME_MACRO some_text
// STRINGIZE(SOME_MACRO) will yield "some_text"
//------------------------------------------------------------------------------
#define _STRINGIZE(_thing_) #_thing_
#define STRINGIZE(_thing_) _STRINGIZE(_thing_)

//------------------------------------------------------------------------------
// Size macros
//------------------------------------------------------------------------------
#define SIZE_IN_KB(_size_) ((_size_)*1024)
#define SIZE_IN_MB(_size_) ((_size_)*1024*1024)

//------------------------------------------------------------------------------
// Disambiguate specific bit manipulation
//------------------------------------------------------------------------------
#define BIT(_number_) (1<<_number_)

//------------------------------------------------------------------------------
// Trigger an intentional crash to get a dump and/or chance to debug
//------------------------------------------------------------------------------
#define INTENTIONAL_CRASH { fflush(stderr); fflush(stdout); uint8* pFatal = NULL; *pFatal = 0; }

//==============================================================================

#endif // End [!defined(__MACROS_H__)]
// [EOF]

