#include "common/stdafx.h"

#define BOOST_FILESYSTEM_VERSION 3

#if defined(BOOST_FILESYSTEM_NO_DEPRECATED)
#define BOOST_FILESYSTEM_NO_DEPRECATED
#endif // defined(BOOST_FILESYSTEM_NO_DEPRECATED)
#if defined(BOOST_SYSTEM_NO_DEPRECATED)
#define BOOST_SYSTEM_NO_DEPRECATED
#endif // defined(BOOST_SYSTEM_NO_DEPRECATED)

#include <boost/filesystem.hpp>
#include <boost/filesystem/fstream.hpp>
#include <iostream>
#include <sstream>
#include <string>

//==============================================================================

enum eFlags
{
	eF_HELP = 1 << 0,
	eF_RESET_BUILD_NUMBER = 1 << 1,
	eF_HAVE_VERSION_MAJOR = 1 << 2,
	eF_VERSION_MAJOR_BUMP = 1 << 3,
	eF_HAVE_VERSION_MINOR = 1 << 4,
	eF_VERSION_MINOR_BUMP = 1 << 5
};

//==============================================================================

int main(int argc, char* argv[])
{
	//============================================================================

	boost::filesystem::path full_path(boost::filesystem::initial_path<boost::filesystem::path>());
	boost::uintmax_t fileSize = 0;
	uint32 versionMajor = 0;
	uint32 versionMinor = 0;
	uint32 buildNumber = 0;
	uint32 flags = 0;

	//============================================================================
	// Parse the arguments
	//============================================================================
	int arg = 0;
	while (++arg < argc)
	{
		std::cout << "arg " << arg << ") [" << argv[arg] << "]" << std::endl;
		if ((strcmp(argv[arg], "--help") == 0) || (strcmp(argv[arg], "-h") == 0) || (strcmp(argv[arg], "?") == 0))
		{
			flags |= eF_HELP;
		}

		if (strcmp(argv[arg], "--file") == 0)
		{
			full_path = boost::filesystem::system_complete(boost::filesystem::path(argv[++arg]));
		}

		if ((strcmp(argv[arg], "--version-major") == 0) || (strcmp(argv[arg], "-vM") == 0))
		{
			versionMajor = atoi(argv[++argc]);
			flags |= eF_RESET_BUILD_NUMBER | eF_HAVE_VERSION_MAJOR;
		}

		if ((strcmp(argv[arg], "--version-minor") == 0) || (strcmp(argv[arg], "-vm") == 0))
		{
			versionMinor = atoi(argv[++argc]);
			flags |= eF_RESET_BUILD_NUMBER | eF_HAVE_VERSION_MINOR;
		}

		if ((strcmp(argv[arg], "--version-major-bump") == 0) || (strcmp(argv[arg], "-vM+") == 0))
		{
			flags |= eF_VERSION_MAJOR_BUMP;
		}

		if ((strcmp(argv[arg], "--version-minor-bump") == 0) || (strcmp(argv[arg], "-vm+") == 0))
		{
			flags |= eF_VERSION_MINOR_BUMP;
		}
	}
	//============================================================================

	if (flags & eF_HELP)
	{
		// TODO: help
		std::cout << std::endl << "TODO: help" << std::endl;
		return 0;
	}

	//============================================================================
	// Verify any arguments
	//============================================================================
	try
	{
		//==========================================================================
		// Fist check the file exists and is actually a file
		//==========================================================================
		if (strcmp(full_path.string().c_str(), boost::filesystem::initial_path<boost::filesystem::path>().string().c_str()) == 0)
		{
			// TODO: throw an exception here
			throw(false);
		}

		boost::filesystem::file_status status = boost::filesystem::status(full_path);
		if (boost::filesystem::exists(status) == false)
		{
			std::cout << std::endl << "[" << full_path.string() << "] does not exist" << std::endl;
			return -1;
		}
		if (boost::filesystem::is_directory(status) == true)
		{
			std::cout << std::endl << "[" << full_path.string() << "] is not a file" << std::endl;
			return -2;
		}

		//==========================================================================
		// Next get the size
		//==========================================================================
		fileSize = boost::filesystem::file_size(full_path);
	}

	catch (const boost::filesystem::filesystem_error& exception)
	{
		std::cout << std::endl << "[" << exception.code() << "]" << std::endl;
		std::cout << std::endl << "[" << exception.what() << "]" << std::endl;
	}
	//============================================================================

	std::ifstream input_file(full_path.native().c_str());
	std::string version_file((std::istreambuf_iterator<char>(input_file)), std::istreambuf_iterator<char>());

	std::size_t pos = version_file.find('\"');
	if (pos != std::string::npos)
	{
		++pos;

		if ((flags & eF_HAVE_VERSION_MAJOR) == 0)
		{
			versionMajor = atoi(version_file.substr(pos).c_str());
		}
		else if (flags & eF_VERSION_MAJOR_BUMP)
		{
			++versionMajor;
		}

		std::cout << "[" << version_file.substr(pos) <<  "]" << std::endl;
		pos = version_file.substr(pos).find('.');
		if (pos == std::string::npos)
		{
			// TODO: proper exception handling here
			throw(false);
		}
		++pos;

		if ((flags & eF_HAVE_VERSION_MINOR) == 0)
		{
			versionMinor = atoi(version_file.substr(pos).c_str());
		}
		else if (flags & eF_VERSION_MINOR_BUMP)
		{
			++versionMinor;
		}

		pos = version_file.substr(pos).find('.');
		if (pos == std::string::npos)
		{
			// TODO: proper exception handling here
			throw(false);
		}
		++pos;

		if (flags & eF_RESET_BUILD_NUMBER)
		{
			buildNumber = 0;
		}
		else
		{
			buildNumber = atoi(version_file.substr(pos).c_str());
		}
	}
	else
	{
		std::cout << "not found \"" << std::endl;
	}

	std::cout << std::endl << versionMajor << "." << versionMinor << "." << buildNumber << std::endl;
//	std::cout << version_file.c_str() << std::endl;
//	std::cout << version_file.length() << std::endl;


/*
	FILE* pNumbers = fopen(argv[1], "r");
	if (pNumbers != NULL)
	{
		fscanf(pNumbers, "%u.%u.%u.%u", &versionMajor, &versionMinor, &buildMajor, &buildMinor);
		fclose(pNumbers);
	}

	versionMajor &= 0xff;
	versionMinor &= 0xff;
	uint32 build = ((((buildMajor&0xff)<<8) | (buildMinor&0xff))+1)&0xffff;
	buildMajor = (build>>8)&0xff;
	buildMinor = build&0xff;

	pNumbers = fopen(argv[1], "w");
	if (pNumbers != NULL)
	{
		fprintf(pNumbers, "%u.%u.%u.%u", versionMajor, versionMinor, buildMajor, buildMinor);
		fclose(pNumbers);
		printf("Updated [%s]\n", argv[1]);
	}
	else
	{
		printf("Unable to open [%s] for writing...\n", argv[1]);
		return eEC_UNABLE_TO_OPEN_BUILD_NUMBERS_FOR_WRITING;
	}

	//============================================================================

	FILE* pTemplate = fopen(argv[2], "rb");
	if (pTemplate == NULL)
	{
		printf("Unable to open template [%s] for reading...\n", argv[2]);
		return eEC_UNABLE_TO_OPEN_TEMPLATE_FILE_FOR_READING;
	}

	FILE* pOutput = fopen(argv[3], "wb");
	if (pOutput == NULL)
	{
		printf("Unable to open output [%s] for writing...\n", argv[3]);
		return eEC_UNABLE_TO_OPEN_OUTPUT_FILE_FOR_WRITING;
	}

	char templateFile[SIZE_IN_KB(64)];
	memset(templateFile, 0, sizeof(templateFile));
	size_t bytesRead = fread(templateFile, sizeof(char), sizeof(templateFile), pTemplate);
	switch (bytesRead)
	{
		case 0:
			printf("Template [%s] is empty...\n", argv[2]);
			return eEC_TEMPLATE_FILE_EMPTY;

		case sizeof(templateFile):
			printf("Template [%s] is too big...\n", argv[2]);
			return eEC_TEMPLATE_FILE_TOO_BIG;

		default:
			break;
	}

	char outputFile[SIZE_IN_KB(64)];
	memset(outputFile, 0, sizeof(outputFile));
	char* pTag = NULL;

	while ((pTag = strstr(templateFile, "@VERSION_MAJOR@")) != NULL)
	{
		uint32 preamble = pTag-templateFile;
		memcpy(outputFile, templateFile, preamble);
		sprintf(outputFile+preamble, "%u%s", versionMajor, pTag+sizeof("@VERSION_MAJOR@")-1); 
		memcpy(templateFile, outputFile, sizeof(templateFile));
	}
	while ((pTag = strstr(templateFile, "@VERSION_MINOR@")) != NULL)
	{
		uint32 preamble = pTag-templateFile;
		memcpy(outputFile, templateFile, preamble);
		sprintf(outputFile+preamble, "%u%s", versionMinor, pTag+sizeof("@VERSION_MINOR@")-1); 
		memcpy(templateFile, outputFile, sizeof(templateFile));
	}
	while ((pTag = strstr(templateFile, "@BUILD_NUMBER@")) != NULL)
	{
		uint32 preamble = pTag-templateFile;
		memcpy(outputFile, templateFile, preamble);
		sprintf(outputFile+preamble, "%u%s", build, pTag+sizeof("@BUILD_NUMBER@")-1); 
		memcpy(templateFile, outputFile, sizeof(templateFile));
	}
	while ((pTag = strstr(templateFile, "@BUILD_NUMBER_PADDED@")) != NULL)
	{
		uint32 preamble = pTag-templateFile;
		memcpy(outputFile, templateFile, preamble);
		sprintf(outputFile+preamble, "%05u%s", build, pTag+sizeof("@BUILD_NUMBER_PADDED@")-1); 
		memcpy(templateFile, outputFile, sizeof(templateFile));
	}

	fwrite(templateFile, strlen(templateFile), 1, pOutput);
	fclose(pTemplate);
	fclose(pOutput);
*/
	return 0;
}

//==============================================================================
// EOF


