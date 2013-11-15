#include "common/stdafx.h"

#define BOOST_FILESYSTEM_NO_DEPRECATED
#include <boost/filesystem.hpp>

#include <iostream>

//==============================================================================

int main(int argc, char* argv[])
{
	//============================================================================

	uint32 versionMajor = 0;
	uint32 versionMinor = 0;
	uint32 buildMajor = 0;
	uint32 buildMinor = 0;

	if (argc != 2)
	{
		std::cout << std::endl << "usage:  update_version <version_header>" << std::endl;
		return 0;
	}

	/*
	// Current working directory
	boost::filesystem::path full_path(boost::filesystem::initial_path<boost::filesystem::path>());
	*/

	//============================================================================
	// Fist check the file exists and is actually a file
	//============================================================================
	boost::filesystem::path full_path = boost::filesystem::system_complete(boost::filesystem::path(argv[1]));
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
	//============================================================================

	//============================================================================
	// Next get the size
	//============================================================================
	boost::uintmax_t fileSize = 0;
	try
	{
		fileSize = boost::filesystem::file_size(full_path);
		std::cout << std::endl << "[" << full_path.string() << "] is " << fileSize << " bytes" << std::endl;
	}

	catch (const boost::filesystem::filesystem_error& exception)
	{
		std::cout << std::endl << "[" << exception.code() << "]" << std::endl;
		std::cout << std::endl << "[" << exception.what() << "]" << std::endl;
	}
	//============================================================================

	/*

	catch (const boost::filesystem::filesystem_error& exception)
	{
		std::cout << std::endl << "[" << exception.code() << "]" << std::endl;
		std::cout << std::endl << "[" << exception.what() << "]" << std::endl;
	}
	*/

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


