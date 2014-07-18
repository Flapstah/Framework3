#include "common/stdafx.h"

#define BOOST_FILESYSTEM_VERSION 3

#if defined(BOOST_FILESYSTEM_NO_DEPRECATED)
#define BOOST_FILESYSTEM_NO_DEPRECATED
#endif // defined(BOOST_FILESYSTEM_NO_DEPRECATED)
#if defined(BOOST_SYSTEM_NO_DEPRECATED)
#define BOOST_SYSTEM_NO_DEPRECATED
#endif // defined(BOOST_SYSTEM_NO_DEPRECATED)

#include <boost/filesystem.hpp>
#include <iostream>
#include <iomanip>
#include <fstream>
#include <sstream>

//==============================================================================

enum eg_flags
{
	eF_HELP = 1 << 0,
	eF_RESET_BUILD_NUMBER = 1 << 1,
	eF_HAVE_VERSION_MAJOR = 1 << 2,
	eF_VERSION_MAJOR_BUMP = 1 << 3,
	eF_HAVE_VERSION_MINOR = 1 << 4,
	eF_VERSION_MINOR_BUMP = 1 << 5
};

enum eFileID
{
	eFID_TEMPLATE = 0,
	eFID_BUILD_NUMBER,
	eFID_OUTPUT,

	eFID_NUM_FILES
};

enum eReturnCode
{
	eRC_OK = 0,
	eRC_PATH_DOES_NOT_EXIST = -1,
	eRC_NOT_A_FILE = -2,
	eRC_VERSION_STRING_NOT_FOUND = -3
};

//==============================================================================

uint32 g_versionMajor = 0;
uint32 g_versionMinor = 0;
uint32 g_buildNumber = 0;
uint32 g_flags = 0;

//==============================================================================

eReturnCode CheckFile(boost::filesystem::path& path)
{
	boost::filesystem::file_status status = boost::filesystem::status(path);
	if (boost::filesystem::exists(status) == false)
	{
		std::cout << std::endl << "[" << path.string() << "] does not exist" << std::endl;
		return eRC_PATH_DOES_NOT_EXIST;
	}

	if (boost::filesystem::is_directory(status) == true)
	{
		std::cout << std::endl << "[" << path.string() << "] is not a file" << std::endl;
		return eRC_NOT_A_FILE;
	}

	return eRC_OK;
}

//==============================================================================

eReturnCode ParseVersionNumbers(boost::filesystem::path& path)
{
	std::ifstream inputFile(path.string().c_str());
	std::string versionFile((std::istreambuf_iterator<char>(inputFile)), std::istreambuf_iterator<char>());
	inputFile.close();

	uint32 tempVersionMajor = 0;
	uint32 tempVersionMinor = 0;
	uint32 tempBuildNumber = 0;

	sscanf(versionFile.c_str(), "%u.%u.%u", &tempVersionMajor, &tempVersionMinor, &tempBuildNumber);

	if ((g_flags & eF_HAVE_VERSION_MAJOR) == 0)
	{
		g_versionMajor = tempVersionMajor;
		if (g_flags & eF_VERSION_MAJOR_BUMP)
		{
			++g_versionMajor;
		}
	}

	if ((g_flags & eF_HAVE_VERSION_MINOR) == 0)
	{
		g_versionMinor = tempVersionMinor;
		if (g_flags & eF_VERSION_MINOR_BUMP)
		{
			++g_versionMinor;
		}
	}

	if (g_flags & eF_RESET_BUILD_NUMBER)
	{
		g_buildNumber = 0;
	}
	else
	{
		g_buildNumber = tempBuildNumber+1;
	}

	//============================================================================
	// Version number fettling
	//============================================================================
	if (g_buildNumber > 0xffff)
	{
		g_buildNumber = 0;
		++g_versionMinor;
	}

	if (g_versionMinor > 255)
	{
		g_versionMinor = 0;
		++g_versionMajor;
	}

	if (g_versionMajor > 255)
	{
		g_buildNumber = 0;
		g_versionMinor = 0;
		g_versionMajor = 0;
	}
	//============================================================================

	std::ofstream outputFile(path.string().c_str(), std::ios_base::out | std::ios_base::binary);
	outputFile << g_versionMajor << "." << g_versionMinor << "." << g_buildNumber;
	outputFile.close();

	return eRC_OK;
}

bool ReplaceString(std::string& source, const std::string& target, const std::string& replace)
{
	bool rc = false;
	std::string temp;

	std::size_t pos = source.find(target);
	if (pos != std::string::npos)
	{
		temp = source.substr(0, pos) + replace + source.substr(pos+target.length());
		source.swap(temp);
		rc = true;
	}

	return rc;
}

//==============================================================================

void CreateFile(boost::filesystem::path& templatePath, boost::filesystem::path& outputPath)
{
	//============================================================================
	// Read in the template file
	//============================================================================
	std::ifstream inputFile(templatePath.string().c_str());
	std::string templateFile((std::istreambuf_iterator<char>(inputFile)), std::istreambuf_iterator<char>());
	inputFile.close();

	std::stringstream number;
	number << g_versionMajor;
	while (ReplaceString(templateFile, std::string("@VERSION_MAJOR@"), number.str()));
	number.str(std::string());
	number << g_versionMinor;
	while (ReplaceString(templateFile, std::string("@VERSION_MINOR@"), number.str()));
	number.str(std::string());
	number << g_buildNumber;
	while (ReplaceString(templateFile, std::string("@BUILD_NUMBER@"), number.str()));
	number.str(std::string());
	number << std::setfill('0') << std::setw(5) << g_buildNumber;
	while (ReplaceString(templateFile, std::string("@BUILD_NUMBER_PADDED@"), number.str()));

	//============================================================================
	// Write the output file
	//============================================================================
	std::ofstream outputFile(outputPath.string().c_str(), std::ios_base::out | std::ios_base::binary);
	outputFile << templateFile;
	outputFile.close();
}

//==============================================================================

int main(int argc, char* argv[])
{
	//============================================================================

	boost::filesystem::path path[eFID_NUM_FILES];

	//============================================================================
	// Parse the arguments
	//============================================================================
	int arg = 0;
	while (++arg < argc)
	{
		if ((strcmp(argv[arg], "--help") == 0) || (strcmp(argv[arg], "-h") == 0) || (strcmp(argv[arg], "?") == 0))
		{
			g_flags |= eF_HELP;
			continue;
		}

		if (strcmp(argv[arg], "--template-file") == 0)
		{
			if (++arg < argc)
			{
				path[eFID_TEMPLATE] = boost::filesystem::system_complete(boost::filesystem::path(argv[arg]));
				continue;
			}
		}

		if (strcmp(argv[arg], "--output-file") == 0)
		{
			if (++arg < argc)
			{
				path[eFID_OUTPUT] = boost::filesystem::system_complete(boost::filesystem::path(argv[arg]));
				continue;
			}
		}

		if (strcmp(argv[arg], "--build-number-file") == 0)
		{
			if (++arg < argc)
			{
				path[eFID_BUILD_NUMBER] = boost::filesystem::system_complete(boost::filesystem::path(argv[arg]));
				continue;
			}
		}

		if ((strcmp(argv[arg], "--version-major") == 0) || (strcmp(argv[arg], "-vM") == 0))
		{
			if (++arg < argc)
			{
				g_versionMajor = atoi(argv[arg]);
				g_flags |= eF_RESET_BUILD_NUMBER | eF_HAVE_VERSION_MAJOR;
				continue;
			}
		}

		if ((strcmp(argv[arg], "--version-minor") == 0) || (strcmp(argv[arg], "-vm") == 0))
		{
			if (++arg < argc)
			{
				g_versionMinor = atoi(argv[arg]);
				g_flags |= eF_RESET_BUILD_NUMBER | eF_HAVE_VERSION_MINOR;
				continue;
			}
		}

		if ((strcmp(argv[arg], "--version-major-bump") == 0) || (strcmp(argv[arg], "-vM+") == 0))
		{
			g_flags |= eF_VERSION_MAJOR_BUMP | eF_RESET_BUILD_NUMBER;
			continue;
		}

		if ((strcmp(argv[arg], "--version-minor-bump") == 0) || (strcmp(argv[arg], "-vm+") == 0))
		{
			g_flags |= eF_VERSION_MINOR_BUMP | eF_RESET_BUILD_NUMBER;
			continue;
		}

		if ((strcmp(argv[arg], "--reset-build-number") == 0) || (strcmp(argv[arg], "-rb") == 0))
		{
			g_flags |= eF_RESET_BUILD_NUMBER;
			continue;
		}
	}
	//============================================================================

	if (g_flags & eF_HELP)
	{
		TODO("need to put some help text here")
		std::cout << std::endl << "TODO: help" << std::endl;
		return eRC_OK;
	}

	//============================================================================
	// Verify the files exist and are file
	//============================================================================
	eReturnCode rc = eRC_OK;
	if (((rc = CheckFile(path[eFID_TEMPLATE])) != eRC_OK) || ((rc = CheckFile(path[eFID_BUILD_NUMBER])) != eRC_OK))
	{
		return rc;
	}
	//============================================================================
	
	if ((rc = ParseVersionNumbers(path[eFID_BUILD_NUMBER])) != eRC_OK)
	{
		return rc;
	}

	//============================================================================
	// Read in the file and parse the version string
	//============================================================================
	CreateFile(path[eFID_TEMPLATE], path[eFID_OUTPUT]);
	//============================================================================

	return eRC_OK;
}

//==============================================================================
// EOF

