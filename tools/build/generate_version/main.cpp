#include "common/stdafx.h"

//==============================================================================
//
// Simple tool to generate the code for version numbers
//
// Usage:
//		generate_version <build_numbers> <template> <output>
//
// Where:
//		<build_numbers>	is a text file in the format:
//											a.b.c.d
//										where:
//											a		- major version (manually generated)
//											b		- minor version (manually generated)
//											c		- major build number } automatically generated
//											d		- minor build number } but manually overidden
//											in the range 0-255 (out of range values truncated
//		<template>			is a code template file that contains:
//											@VERSION_MAJOR@		- replaced with 'a'
//											@VERSION_MINOR@		- replaced with 'b'
//											@BUILD_MAJOR@			- replaced with 'c'
//											@BUILD_MINOR@			- replaced with 'd'
//		<output>				is the code file to output
//
//		e.g. generate_version versions.txt version.cpp.in version.cpp
//
//==============================================================================

enum eErrorCode
{
	eEC_OK = 0,
	eEC_UNABLE_TO_OPEN_BUILD_NUMBERS_FOR_WRITING = -1,
	eEC_UNABLE_TO_OPEN_TEMPLATE_FILE_FOR_READING = -2,
	eEC_UNABLE_TO_OPEN_OUTPUT_FILE_FOR_WRITING = -3,
	eEC_TEMPLATE_FILE_EMPTY = -4,
	eEC_TEMPLATE_FILE_TOO_BIG = -5
}; // End [enum eErrorCode]

//==============================================================================

int main(int argc, char* argv[])
{

	//============================================================================

	if (argc != 4)
	{
		printf("\nSimple tool to generate the code for version numbers\n");
		printf("\n");
		printf("Usage:\n");
		printf("  generate_version <build_numbers> <template> <output>\n");
		printf("Where:\n");
		printf("  <build_numbers>  is a text file in the format:\n");
		printf("                     a.b.c.d\n");
		printf("                   where:\n");
		printf("                     a - major version (manually generated)\n");
		printf("                     b - minor version (manually generated)\n");
		printf("                     c - major build number } automatically generated\n");
		printf("                     d - minor build number } but manually overidden\n");
		printf("                     in the range 0-255 (out of range values truncated\n)");
		printf("  <template>       is a code template file that contains:\n");
		printf("                     @VERSION_MAJOR@ - replaced with 'a'\n");
		printf("                     @VERSION_MINOR@ - replaced with 'b'\n");
		printf("                     @BUILD_MAJOR@   - replaced with 'c'\n");
		printf("                     @BUILD_MINOR@   - replaced with 'd'\n");
		printf("  <output>         is the code file to output\n");
		printf("\n");
		printf("  e.g. generate_version versions.txt version.cpp.in version.cpp\n");
		return 0;
	}

	//============================================================================

	uint32 versionMajor = 0;
	uint32 versionMinor = 0;
	uint32 buildMajor = 0;
	uint32 buildMinor = 0;

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
		sprintf(outputFile+preamble, "%05u%s", build, pTag+sizeof("@BUILD_NUMBER@")-1); 
		memcpy(templateFile, outputFile, sizeof(templateFile));
	}

	fwrite(templateFile, strlen(templateFile), 1, pOutput);
	fclose(pTemplate);
	fclose(pOutput);

	return eEC_OK;
}

//==============================================================================
// EOF


