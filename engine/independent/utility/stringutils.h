#if !defined(__STRINGUTILS_H__)
#define __STRINGUTILS_H__

//==============================================================================

#include <string>

//==============================================================================

namespace engine
{
	//============================================================================

	namespace utility
	{
		//==========================================================================

		std::string& StripComment(std::string& line, char commentChar);
		std::string& TrimLeft(std::string& line);
		std::string& TrimRight(std::string& line);
		std::string& Trim(std::string& line);

		//==========================================================================
	} // End [namespace utility]

	//============================================================================
} // End [namespace engine]

//==============================================================================
#endif // End [!defined(__STRINGUTILS_H__)]
// EOF

