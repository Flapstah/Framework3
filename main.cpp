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

	REGISTER_COMMAND("Test", 0, TestCommand, "A test command");
	std::string cmd = "Test \"1 2\" 3";
	printf("%s\n", cmd.c_str());
	console.Execute(cmd);
	UNREGISTER_COMMAND_BY_NAME("Test");

	double x = 0;
	engine::CConsole::TIVariablePtr pIVar = REGISTER_VARIABLE(x, 0, 0, NULL, "Test");
	printf("x is %f\n", pIVar->GetDouble());
	cmd = "x 0x12.3";
	printf("%s\n", cmd.c_str());
	console.Execute(cmd);
	printf("x is %f\n", pIVar->GetDouble());
	UNREGISTER_VARIABLE_BY_POINTER(pIVar);
	return 0;

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

		/*
			 engine::CConsole console;

			 int32 x = 0;
			 printf("Creating i32 var...\n");
			 engine::CConsole::TIVariablePtr pIVar = console.RegisterVariable(engine::CRunTimeStringHash::Calculate("ivar"), x);
			 printf("...i32 var created.\n");
			 if (pIVar != NULL)
			 {
			 printf("default: pIVar = %p, %d %d\n", pIVar.get(), pIVar->GetI32Val(), x);
			 x = 32;
			 printf("direct:  pIVar = %p, %d %d\n", pIVar.get(), pIVar->GetI32Val(), x);
			 pIVar->SetI32Val(64);
			 printf("iface i: pIVar = %p, %d %d\n", pIVar.get(), pIVar->GetI32Val(), x);
			 pIVar->SetF32Val(6.28);
			 printf("iface f: pIVar = %p, %f %d\n", pIVar.get(), pIVar->GetF32Val(), x);
			 pIVar->SetString("123.456");
			 printf("iface s: pIVar = %p, [%s] %d\n", pIVar.get(), pIVar->GetString(), x);
			 }

			 float y = 0;
			 printf("Creating f32 var...\n");
			 engine::CConsole::TIVariablePtr pFVar = console.RegisterVariable(engine::CRunTimeStringHash::Calculate("fvar"), y);
			 printf("...f32 var created.\n");
			 if (pFVar != NULL)
			 {
			 printf("default: pFVar = %p, %f %f\n", pFVar.get(), pFVar->GetF32Val(), y);
			 y = 3.14;
			 printf("direct:  pFVar = %p, %f %f\n", pFVar.get(), pFVar->GetF32Val(), y);
			 pIVar->SetI32Val(64);
			 printf("iface i: pFVar = %p, %d %f\n", pFVar.get(), pFVar->GetI32Val(), y);
			 pFVar->SetF32Val(6.28);
			 printf("iface f: pFVar = %p, %f %f\n", pFVar.get(), pFVar->GetF32Val(), y);
			 pFVar->SetString("123.456");
			 printf("iface s: pFVar = %p, [%s] %f\n", pFVar.get(), pFVar->GetString(), y);
			 }

			 std::string z("hello world");
			 printf("Creating string var...\n");
			 engine::CConsole::TIVariablePtr pSVar = console.RegisterVariable(engine::CRunTimeStringHash::Calculate("svar"), z);
			 printf("...string var created.\n");
			 if (pSVar != NULL)
			 {
			 printf("default: pSVar = %p, [%s] [%s]\n", pSVar.get(), pSVar->GetString(), z.c_str());
			 z = "nobber";
			 printf("direct:  pSVar = %p, [%s] [%s]\n", pSVar.get(), pSVar->GetString(), z.c_str());
			 pSVar->SetI32Val(64);
			 printf("iface i: pSVar = %p, %d [%s]\n", pSVar.get(), pSVar->GetI32Val(), z.c_str());
			 pSVar->SetF32Val(6.28);
			 printf("iface f: pSVar = %p, %f [%s]\n", pSVar.get(), pSVar->GetF32Val(), z.c_str());
			 pSVar->SetString("interface");
			 printf("iface s: pSVar = %p, [%s] [%s]\n", pSVar.get(), pSVar->GetString(), z.c_str());
			 }
			 int32 v = 0;
			 printf("Creating i32 var...\n");
			 engine::CConsole::TIVariablePtr pIRVar = console.RegisterVariable(engine::CRunTimeStringHash::Calculate("irvar"), v, -10, 10);
			 printf("...i32 var created.\n");
			 if (pIRVar != NULL)
			 {
			 pIRVar->SetFlags(engine::CConsole::IVariable::eF_RANGE_CLAMP);
			 printf("default: pIVar = %p, %d %d\n", pIRVar.get(), pIRVar->GetI32Val(), v);
			 v = 32;
			 printf("direct:  pIVar = %p, %d %d\n", pIRVar.get(), pIRVar->GetI32Val(), v);
			 pIRVar->SetI32Val(64);
			 printf("iface i: pIVar = %p, %d %d\n", pIRVar.get(), pIRVar->GetI32Val(), v);
			 pIRVar->SetF32Val(-100.28);
			 printf("iface f: pIVar = %p, %f %d\n", pIRVar.get(), pIRVar->GetF32Val(), v);
			 pIRVar->SetString("123.456");
			 printf("iface s: pIVar = %p, [%s] %d\n", pIRVar.get(), pIRVar->GetString(), v);
			 }
			 */

	printf("All done.\n");

	return 0;
}

//==============================================================================

#endif // !USE_OPENGL_SUPERBIBLE

// [EOF]
