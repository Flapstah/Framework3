#include "common/stdafx.h" // log.h included here

#include <algorithm>
#include <cctype>
#include <functional>

//==============================================================================

#if !defined(TRACE_ENABLE)
	#undef TRACE_ENABLE
	#define TRACE_ENABLE true
#endif //!defined(TRACE_ENABLE)

//==============================================================================

namespace engine
{
	//============================================================================

	namespace utility
	{
		//==========================================================================

		std::string& StripComment(std::string& line, char commentChar)
		{
			TRACE(TRACE_ENABLE);

			size_t pos = line.find_first_of(commentChar);
			if (pos != std::string::npos)
			{
				line.erase(pos);
			}
			return line;
		}

		//==========================================================================

		std::string& TrimLeft(std::string& line)
		{
			TRACE(TRACE_ENABLE);

			line.erase(line.begin(), std::find_if(line.begin(), line.end(), std::not1(std::ptr_fun<int, int>(std::isspace))));
			return line;
		}

		//==========================================================================

		std::string& TrimRight(std::string& line)
		{
			TRACE(TRACE_ENABLE);

			line.erase((std::find_if(line.rbegin(), line.rend(), std::not1(std::ptr_fun<int, int>(std::isspace)))).base(), line.end());
			return line;
		}

		//==========================================================================

		std::string& Trim(std::string& line)
		{
			TRACE(TRACE_ENABLE);

			return TrimLeft(TrimRight(line));
		}

		//==========================================================================
	} // End [namespace utility]

	//============================================================================
} // End [namespace engine]

//==============================================================================
// EOF

