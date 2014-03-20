#if !defined(__COMPILETIMESTRINGHASH_H__)
#define __COMPILETIMESTRINGHASH_H__

//==============================================================================

#include "utility/versionkeys.h"

//==============================================================================

namespace engine
{
	//============================================================================
	// CCompileTimeStringHash
	// - generic template
	//============================================================================
	template <uint32 _LENGTH_, uint32 _INDEX_>
		class CCompileTimeStringHash
		{
			public:
				__inline static uint32 Calculate(const char (&id)[_LENGTH_])
				{
					return (CCompileTimeStringHash<_LENGTH_, _INDEX_-1>::Calculate(id) ^ id[_INDEX_-1])*STRING_HASH_PRIME2;
				}
		};

	//============================================================================
	// CCompileTimeStringHash
	// - partial specialisation to terminate recursion
	//============================================================================
	template <uint32 _LENGTH_>
		class CCompileTimeStringHash<_LENGTH_, 1>
		{
			public:
				__inline static uint32 Calculate(const char (&id)[_LENGTH_])
				{
					return (STRING_HASH_PRIME1 ^ id[0])*STRING_HASH_PRIME2;
				}
		};

	//============================================================================
	// CompileTimeStringHash
	// - usage: uint32 hash = CompileTimeStringHash("hello");
	//============================================================================
	template <uint32 _LENGTH_>
		__inline uint32 CompileTimeStringHash(const char (&id)[_LENGTH_])
		{
			return CCompileTimeStringHash<_LENGTH_, _LENGTH_>::Calculate(id);
		}

	//============================================================================

} // End [namespace engine]

//==============================================================================

#endif // !defined(__COMPILETIMESTRINGHASH_H__)
// EOF


