#include "common/stdafx.h"

#if !USE_OPENGL_SUPERBIBLE

#include "common/itime.h"
#include "common/commandline.h"
#include "unit_tests/cvartest.h"
#include "unit_tests/typetest.h"
#include "unit_tests/timetest.h"
#include "common/console.h"
#include "common/version.h"

#include <cmath>

bool TestCommand(std::vector<std::string>& argv)
{
	printf("*** TestCommand\n");

	int argc = 0;
	for (std::vector<std::string>::iterator it = argv.begin(), end = argv.end(); it != end; ++it)
	{
		printf("argv[%d]=\"%s\"\n", argc++, (*it).c_str());
	}

	printf("*** ~TestCommand\n");
	return true;
}


//==============================================================================

int main(int argc, char* argv[])
{
	//	IGNORE_PARAMETER(argc);
	//	IGNORE_PARAMETER(argv);

	engine::CConsole& console = engine::CConsole::Get();
	engine::CCommandLine cl(argc, argv, console);

	/*
	REGISTER_COMMAND("Test", 0, TestCommand, "A test command");
	std::string cmd = "Test \"1 2\" 3";
	printf("%s\n", cmd.c_str());
	console.Execute(cmd);
	UNREGISTER_COMMAND_BY_NAME("Test");
	*/

		{
			test::CTypeTest test;
			test.Start();
			while (test.Update() == test::CUnitTest::eTS_RUNNING);
			test.End();
		}

		{
			test::CTimeTest test;
			test.Start();
			while (test.Update() == test::CUnitTest::eTS_RUNNING);
			test.End();
		}

		{
			test::CCVarTest test;
			test.Start();
			while (test.Update() == test::CUnitTest::eTS_RUNNING);
			test.End();
		}

		/*
			 uint32 x = engine::CompileTimeStringHash("a nice long string to hash");
			 printf("x %08x\n", x);
			 uint32 y = engine::CRunTimeStringHash::Calculate("a nice long string to hash");
			 printf("y %08x\n", y);
			 */

	printf("All done.\n");

	return 0;
}

//==============================================================================

#endif // !USE_OPENGL_SUPERBIBLE

// [EOF]
