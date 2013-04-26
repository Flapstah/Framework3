#include "common/stdafx.h"

#if !USE_OPENGL_SUPERBIBLE

#include "common/itime.h"
#include "common/commandargs.h"
#include "unit_tests/typetest.h"
#include "unit_tests/timetest.h"
#include "common/console.h"

//==============================================================================

class CSudoku
{
	public:
		CSudoku(void)
	 	{
			memset(m_grid, 0, sizeof(m_grid));
		}

		~CSudoku(void) {}

		bool InitialiseCell(uint32 row, uint32 column, uint32 value)
		{
			bool done = false;

			if ((row < 9) && (column < 9) && (value < 10))
			{
				m_grid[row][column] = ((1<<value)>>1);
				done = true;
			}

			return done;
		}

		void Display(void)
		{
			for (uint32 row = 0; row < 9; ++row)
			{
				for (uint32 column = 0; column < 9; ++column)
				{
					switch (m_grid[row][column])
					{
						case 1:
							printf("1");
							break;
						case 2:
							printf("2");
							break;
						case 4:
							printf("3");
							break;
						case 8:
							printf("4");
							break;
						case 16:
							printf("5");
							break;
						case 32:
							printf("6");
							break;
						case 64:
							printf("7");
							break;
						case 128:
							printf("8");
							break;
						case 256:
							printf("9");
							break;

						default:
							printf(" ");
							break;
					}

					if ((column == 2) || (column == 5))
					{
						printf("|");
					}
				}

				printf("\n");
				if ((row == 2) || (row == 5))
				{
					printf("---+---+---\n");
				}
			}
			printf("\n");
		}

		bool Solve(void)
		{
			bool solved = false;
			for (uint32 pass = 0; (!solved) && (pass < 81); ++pass)
			{
				solved = Calculate();
				Display();
			}
			return solved;
		}

	protected:
		bool Calculate(void)
		{
			bool solved = true;
			for (uint32 row = 0; row < 9; ++row)
			{
				for (uint32 column = 0; column < 9; ++column)
				{
					switch (m_grid[row][column])
					{
						case 1:
						case 2:
						case 4:
						case 8:
						case 16:
						case 32:
						case 64:
						case 128:
						case 256:
							break;

						default:
							m_grid[row][column] = (1<<9)-1 & CalculateRow(row) & CalculateColumn(column) & Calculate3x3For(row, column);
							solved = false;
							break;
					}
				}
			}
			return solved;
		}

		uint16 CalculateRow(uint32 row)
		{
			return ~m_grid[row][0] & ~m_grid[row][1] & ~m_grid[row][2] & ~m_grid[row][3] & ~m_grid[row][4] & ~m_grid[row][5] & ~m_grid[row][6] & ~m_grid[row][7] & ~m_grid[row][8];
		}

		uint16 CalculateColumn(uint32 column)
		{
			return ~m_grid[0][column] & ~m_grid[1][column] & ~m_grid[2][column] & ~m_grid[3][column] & ~m_grid[4][column] & ~m_grid[5][column] & ~m_grid[6][column] & ~m_grid[7][column] & ~m_grid[8][column];
		}

		uint16 Calculate3x3For(uint32 row, uint32 column)
		{
			row = (row/3)*3;
			column = (column/3)*3;

			return ~m_grid[row][column] & ~m_grid[row+1][column] & ~m_grid[row+2][column] & ~m_grid[row][column+1] & ~m_grid[row+1][column+1] & ~m_grid[row+2][column+1] & ~m_grid[row][column+2] & ~m_grid[row+1][column+2] & ~m_grid[row+2][column+2];
		}

	private:
		uint16 m_grid[9][9];
};

//==============================================================================

int main(int argc, char* argv[])
{
//	IGNORE_PARAMETER(argc);
//	IGNORE_PARAMETER(argv);

	if (engine::CCommandArgs::Parse(argc, argv) == engine::CCommandArgs::ePS_SUCCESS)
	{

		//	DumpArgs(argc, argv);
		/*
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
			 */

		/*
			 uint32 x = engine::CompileTimeStringHash("a nice long string to hash");
			 printf("x %08x\n", x);
			 uint32 y = engine::CRunTimeStringHash::Calculate("a nice long string to hash");
			 printf("y %08x\n", y);
			 */

		/*
		int32 variable = 0;
		uint32 flags = engine::CConsole::IVariable::eF_CLAMP_TO_RANGE;
		engine::CConsole::IVariable::TOnChangeCallback pCallback;
		pCallback.m_pOnChangeI32 = NULL;
		engine::CConsole::CI32Variable cvar(variable, int32 123, int32 100, int32 200, uint32 engine::CConsole::CI32Variable::eF_CLAMP_TO_RANGE, "variable", "test console variable", NULL);
		*/

		//  x 6 x   x 3 x   x 7 x        4 6 8   9 3 1   5 7 2
		//  x 2 x   8 4 x   3 x x        7 2 5   8 4 6   3 9 1
		//  x x x   x x x   4 x 6        3 9 1   2 5 7   4 8 6
		//
		//  1 x x   x 8 x   x 5 x        1 4 2   3 8 9   6 5 7
		//  x x x   x x x   9 4 x        6 7 3   1 2 5   9 4 8
		//  8 x x   x 7 x   x x x        8 5 9   6 7 4   1 2 3
		//
		//  9 8 x   4 x x   2 x 5        9 8 7   4 1 3   2 6 5
		//  5 x x   7 x 2   x x x        5 1 6   7 9 2   8 3 4
		//  x x x   x 6 x   x 1 x        2 3 4   5 6 8   7 1 9

		// set up board here
		CSudoku sudoku;
#define SI sudoku.InitialiseCell
		SI(0, 0, 0); SI(0, 1, 6); SI(0, 2, 0);		SI(0, 3, 0); SI(0, 4, 3); SI(0, 5, 0);		SI(0, 6, 0); SI(0, 7, 7); SI(0, 8, 0);
		SI(1, 0, 0); SI(1, 1, 2); SI(1, 2, 0);		SI(1, 3, 8); SI(1, 4, 4); SI(1, 5, 0);		SI(1, 6, 3); SI(1, 7, 0); SI(1, 8, 0);
		SI(2, 0, 0); SI(2, 1, 0); SI(2, 2, 0);		SI(2, 3, 0); SI(2, 4, 0); SI(2, 5, 0);		SI(2, 6, 4); SI(2, 7, 0); SI(2, 8, 6);

		SI(3, 0, 1); SI(3, 1, 0); SI(3, 2, 0);		SI(3, 3, 0); SI(3, 4, 8); SI(3, 5, 0);		SI(3, 6, 0); SI(3, 7, 5); SI(3, 8, 0);
		SI(4, 0, 0); SI(4, 1, 0); SI(4, 2, 0);		SI(4, 3, 0); SI(4, 4, 0); SI(4, 5, 0);		SI(4, 6, 9); SI(4, 7, 4); SI(4, 8, 0);
		SI(5, 0, 8); SI(5, 1, 0); SI(5, 2, 0);		SI(5, 3, 0); SI(5, 4, 7); SI(5, 5, 0);		SI(5, 6, 0); SI(5, 7, 0); SI(5, 8, 0);

		SI(6, 0, 9); SI(6, 1, 8); SI(6, 2, 0);		SI(6, 3, 4); SI(6, 4, 0); SI(6, 5, 0);		SI(6, 6, 2); SI(6, 7, 0); SI(6, 8, 5);
		SI(7, 0, 5); SI(7, 1, 0); SI(7, 2, 0);		SI(7, 3, 7); SI(7, 4, 0); SI(7, 5, 2);		SI(7, 6, 0); SI(7, 7, 0); SI(7, 8, 0);
		SI(8, 0, 0); SI(8, 1, 0); SI(8, 2, 0);		SI(8, 3, 0); SI(8, 4, 6); SI(8, 5, 0);		SI(8, 6, 0); SI(8, 7, 1); SI(8, 8, 0);

		sudoku.Display();
		sudoku.Solve();

	}

	printf("All done.\n");

	return 0;
}

//==============================================================================

#endif // !USE_OPENGL_SUPERBIBLE

// [EOF]
