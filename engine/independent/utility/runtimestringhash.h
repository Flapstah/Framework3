#if !defined(__RUNTIMESTRINGHASH_H__)
#define __RUNTIMESTRINGHASH_H__

//==============================================================================

#include "utility/versionkeys.h"

//==============================================================================

#define TRACE_ENABLE false

//==============================================================================

namespace engine
{
	//============================================================================

	namespace utility
	{
		//==========================================================================
		// CRunTimeStringHash
		//==========================================================================
		class CRunTimeStringHash
		{
		public:
			static uint32 Calculate(const char* id)
			{
				TRACE(TRACE_ENABLE);

				uint32 index = 0;
				uint32 hash = (STRING_HASH_PRIME1 ^ id[index])*STRING_HASH_PRIME2;

				while (id[++index] != 0)
				{
					hash ^= id[index];
					hash *= STRING_HASH_PRIME2;
				}

				hash ^= id[index];
				hash *= STRING_HASH_PRIME2;

				return hash;
			}
		}; // End [class CRunTimeStringHash]

		//==========================================================================
	} // End [namespace utility]

	//============================================================================
} // End [namespace engine]

//==============================================================================

#endif // !defined(__RUNTIMESTRINGHASH_H__)
// EOF

