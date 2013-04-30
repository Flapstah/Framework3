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

		bool Initialise(uint8 v00, uint8 v01, uint8 v02, uint8 v03, uint8 v04, uint8 v05, uint8 v06, uint8 v07, uint8 v08,
										uint8 v10, uint8 v11, uint8 v12, uint8 v13, uint8 v14, uint8 v15, uint8 v16, uint8 v17, uint8 v18,
										uint8 v20, uint8 v21, uint8 v22, uint8 v23, uint8 v24, uint8 v25, uint8 v26, uint8 v27, uint8 v28,
										uint8 v30, uint8 v31, uint8 v32, uint8 v33, uint8 v34, uint8 v35, uint8 v36, uint8 v37, uint8 v38,
										uint8 v40, uint8 v41, uint8 v42, uint8 v43, uint8 v44, uint8 v45, uint8 v46, uint8 v47, uint8 v48,
										uint8 v50, uint8 v51, uint8 v52, uint8 v53, uint8 v54, uint8 v55, uint8 v56, uint8 v57, uint8 v58,
										uint8 v60, uint8 v61, uint8 v62, uint8 v63, uint8 v64, uint8 v65, uint8 v66, uint8 v67, uint8 v68,
										uint8 v70, uint8 v71, uint8 v72, uint8 v73, uint8 v74, uint8 v75, uint8 v76, uint8 v77, uint8 v78,
										uint8 v80, uint8 v81, uint8 v82, uint8 v83, uint8 v84, uint8 v85, uint8 v86, uint8 v87, uint8 v88)
		{
			bool done = true;

			(v00 < 10) ? m_grid[0][0] = ((1<<v00)>>1) : done = false;
			(v01 < 10) ? m_grid[0][1] = ((1<<v01)>>1) : done = false;
			(v02 < 10) ? m_grid[0][2] = ((1<<v02)>>1) : done = false;
			(v03 < 10) ? m_grid[0][3] = ((1<<v03)>>1) : done = false;
			(v04 < 10) ? m_grid[0][4] = ((1<<v04)>>1) : done = false;
			(v05 < 10) ? m_grid[0][5] = ((1<<v05)>>1) : done = false;
			(v06 < 10) ? m_grid[0][6] = ((1<<v06)>>1) : done = false;
			(v07 < 10) ? m_grid[0][7] = ((1<<v07)>>1) : done = false;
			(v08 < 10) ? m_grid[0][8] = ((1<<v08)>>1) : done = false;

			(v10 < 10) ? m_grid[1][0] = ((1<<v10)>>1) : done = false;
			(v11 < 10) ? m_grid[1][1] = ((1<<v11)>>1) : done = false;
			(v12 < 10) ? m_grid[1][2] = ((1<<v12)>>1) : done = false;
			(v13 < 10) ? m_grid[1][3] = ((1<<v13)>>1) : done = false;
			(v14 < 10) ? m_grid[1][4] = ((1<<v14)>>1) : done = false;
			(v15 < 10) ? m_grid[1][5] = ((1<<v15)>>1) : done = false;
			(v16 < 10) ? m_grid[1][6] = ((1<<v16)>>1) : done = false;
			(v17 < 10) ? m_grid[1][7] = ((1<<v17)>>1) : done = false;
			(v18 < 10) ? m_grid[1][8] = ((1<<v18)>>1) : done = false;

			(v20 < 10) ? m_grid[2][0] = ((1<<v20)>>1) : done = false;
			(v21 < 10) ? m_grid[2][1] = ((1<<v21)>>1) : done = false;
			(v22 < 10) ? m_grid[2][2] = ((1<<v22)>>1) : done = false;
			(v23 < 10) ? m_grid[2][3] = ((1<<v23)>>1) : done = false;
			(v24 < 10) ? m_grid[2][4] = ((1<<v24)>>1) : done = false;
			(v25 < 10) ? m_grid[2][5] = ((1<<v25)>>1) : done = false;
			(v26 < 10) ? m_grid[2][6] = ((1<<v26)>>1) : done = false;
			(v27 < 10) ? m_grid[2][7] = ((1<<v27)>>1) : done = false;
			(v28 < 10) ? m_grid[2][8] = ((1<<v28)>>1) : done = false;

			(v30 < 10) ? m_grid[3][0] = ((1<<v30)>>1) : done = false;
			(v31 < 10) ? m_grid[3][1] = ((1<<v31)>>1) : done = false;
			(v32 < 10) ? m_grid[3][2] = ((1<<v32)>>1) : done = false;
			(v33 < 10) ? m_grid[3][3] = ((1<<v33)>>1) : done = false;
			(v34 < 10) ? m_grid[3][4] = ((1<<v34)>>1) : done = false;
			(v35 < 10) ? m_grid[3][5] = ((1<<v35)>>1) : done = false;
			(v36 < 10) ? m_grid[3][6] = ((1<<v36)>>1) : done = false;
			(v37 < 10) ? m_grid[3][7] = ((1<<v37)>>1) : done = false;
			(v38 < 10) ? m_grid[3][8] = ((1<<v38)>>1) : done = false;

			(v40 < 10) ? m_grid[4][0] = ((1<<v40)>>1) : done = false;
			(v41 < 10) ? m_grid[4][1] = ((1<<v41)>>1) : done = false;
			(v42 < 10) ? m_grid[4][2] = ((1<<v42)>>1) : done = false;
			(v43 < 10) ? m_grid[4][3] = ((1<<v43)>>1) : done = false;
			(v44 < 10) ? m_grid[4][4] = ((1<<v44)>>1) : done = false;
			(v45 < 10) ? m_grid[4][5] = ((1<<v45)>>1) : done = false;
			(v46 < 10) ? m_grid[4][6] = ((1<<v46)>>1) : done = false;
			(v47 < 10) ? m_grid[4][7] = ((1<<v47)>>1) : done = false;
			(v48 < 10) ? m_grid[4][8] = ((1<<v48)>>1) : done = false;

			(v50 < 10) ? m_grid[5][0] = ((1<<v50)>>1) : done = false;
			(v51 < 10) ? m_grid[5][1] = ((1<<v51)>>1) : done = false;
			(v52 < 10) ? m_grid[5][2] = ((1<<v52)>>1) : done = false;
			(v53 < 10) ? m_grid[5][3] = ((1<<v53)>>1) : done = false;
			(v54 < 10) ? m_grid[5][4] = ((1<<v54)>>1) : done = false;
			(v55 < 10) ? m_grid[5][5] = ((1<<v55)>>1) : done = false;
			(v56 < 10) ? m_grid[5][6] = ((1<<v56)>>1) : done = false;
			(v57 < 10) ? m_grid[5][7] = ((1<<v57)>>1) : done = false;
			(v58 < 10) ? m_grid[5][8] = ((1<<v58)>>1) : done = false;

			(v60 < 10) ? m_grid[6][0] = ((1<<v60)>>1) : done = false;
			(v61 < 10) ? m_grid[6][1] = ((1<<v61)>>1) : done = false;
			(v62 < 10) ? m_grid[6][2] = ((1<<v62)>>1) : done = false;
			(v63 < 10) ? m_grid[6][3] = ((1<<v63)>>1) : done = false;
			(v64 < 10) ? m_grid[6][4] = ((1<<v64)>>1) : done = false;
			(v65 < 10) ? m_grid[6][5] = ((1<<v65)>>1) : done = false;
			(v66 < 10) ? m_grid[6][6] = ((1<<v66)>>1) : done = false;
			(v67 < 10) ? m_grid[6][7] = ((1<<v67)>>1) : done = false;
			(v68 < 10) ? m_grid[6][8] = ((1<<v68)>>1) : done = false;

			(v70 < 10) ? m_grid[7][0] = ((1<<v70)>>1) : done = false;
			(v71 < 10) ? m_grid[7][1] = ((1<<v71)>>1) : done = false;
			(v72 < 10) ? m_grid[7][2] = ((1<<v72)>>1) : done = false;
			(v73 < 10) ? m_grid[7][3] = ((1<<v73)>>1) : done = false;
			(v74 < 10) ? m_grid[7][4] = ((1<<v74)>>1) : done = false;
			(v75 < 10) ? m_grid[7][5] = ((1<<v75)>>1) : done = false;
			(v76 < 10) ? m_grid[7][6] = ((1<<v76)>>1) : done = false;
			(v77 < 10) ? m_grid[7][7] = ((1<<v77)>>1) : done = false;
			(v78 < 10) ? m_grid[7][8] = ((1<<v78)>>1) : done = false;

			(v80 < 10) ? m_grid[8][0] = ((1<<v80)>>1) : done = false;
			(v81 < 10) ? m_grid[8][1] = ((1<<v81)>>1) : done = false;
			(v82 < 10) ? m_grid[8][2] = ((1<<v82)>>1) : done = false;
			(v83 < 10) ? m_grid[8][3] = ((1<<v83)>>1) : done = false;
			(v84 < 10) ? m_grid[8][4] = ((1<<v84)>>1) : done = false;
			(v85 < 10) ? m_grid[8][5] = ((1<<v85)>>1) : done = false;
			(v86 < 10) ? m_grid[8][6] = ((1<<v86)>>1) : done = false;
			(v87 < 10) ? m_grid[8][7] = ((1<<v87)>>1) : done = false;
			(v88 < 10) ? m_grid[8][8] = ((1<<v88)>>1) : done = false;

			return done;
		}

		void DisplayCell(uint32 row, uint32 column)
		{
			char cell[16];
			sprintf(cell, "|123456789|");

			for (uint32 index = 0; index < 9; ++index)
			{
				if ((m_grid[row][column] & (1<<index)) == 0)
				{
					cell[index+1] = '.';
				}
			}
			printf(cell);
		}

		void Display(void)
		{
			for (uint32 row = 0; row < 9; ++row)
			{
				for (uint32 column = 0; column < 9; ++column)
				{
					DisplayCell(row, column);
					/*
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
					*/

					if ((column == 2) || (column == 5))
					{
						printf("*");
					}
				}

				printf("\n");
				if ((row == 2) || (row == 5))
				{
					printf("*****************************************************************************************************\n");
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

		bool Calculate(uint32 row, uint32 column)
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
					m_grid[row][column] = (1<<9)-1 & ~(CalculateRow(row) | CalculateColumn(column) | Calculate3x3For(row, column));
					break;
			}
			return true;
		}

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
							m_grid[row][column] = (1<<9)-1 & ~(CalculateRow(row) | CalculateColumn(column) | Calculate3x3For(row, column));
							solved = false;
							break;
					}
				}
			}
			return solved;
		}

//	protected:
		uint16 CalculateRow(uint32 row)
		{
			printf("CalculateRow(%d): ", row);
			uint16 result = 0;
			for (uint32 column = 0; column < 9; ++column)
			{
				switch (m_grid[row][column])
				{
					case 1:
						printf("1");
						result |= m_grid[row][column];
						break;
					case 2:
						printf("2");
						result |= m_grid[row][column];
						break;
					case 4:
						printf("3");
						result |= m_grid[row][column];
						break;
					case 8:
						printf("4");
						result |= m_grid[row][column];
						break;
					case 16:
						printf("5");
						result |= m_grid[row][column];
						break;
					case 32:
						printf("6");
						result |= m_grid[row][column];
						break;
					case 64:
						printf("7");
						result |= m_grid[row][column];
						break;
					case 128:
						printf("8");
						result |= m_grid[row][column];
						break;
					case 256:
						printf("9");
						result |= m_grid[row][column];
						break;

					default:
						break;
				}
			}
			printf("\n");
			return result;
		}

		uint16 CalculateColumn(uint32 column)
		{
			printf("CalculateColumn(%d): ", column);
			uint16 result = 0;
			for (uint32 row = 0; row < 9; ++row)
			{
				switch (m_grid[row][column])
				{
					case 1:
						printf("1");
						result |= m_grid[row][column];
						break;
					case 2:
						printf("2");
						result |= m_grid[row][column];
						break;
					case 4:
						printf("3");
						result |= m_grid[row][column];
						break;
					case 8:
						printf("4");
						result |= m_grid[row][column];
						break;
					case 16:
						printf("5");
						result |= m_grid[row][column];
						break;
					case 32:
						printf("6");
						result |= m_grid[row][column];
						break;
					case 64:
						printf("7");
						result |= m_grid[row][column];
						break;
					case 128:
						printf("8");
						result |= m_grid[row][column];
						break;
					case 256:
						printf("9");
						result |= m_grid[row][column];
						break;

					default:
						break;
				}
			}
			printf("\n");
			return result;
		}

		uint16 Calculate3x3For(uint32 row, uint32 column)
		{
			printf("Calculate3x3For(%d,%d) => ", row, column);
			row = (row/3)*3;
			column = (column/3)*3;
			printf(" (%d,%d): ", row, column);

			uint16 result = 0;
			for (uint32 dr = 0; dr < 3; ++dr)
			{
				for (uint32 dc = 0; dc < 3; ++dc)
				{
					uint16 cell = m_grid[row+dr][column+dc];
					switch (cell)
					{
						case 1:
							printf("1");
							result |= cell;
							break;
						case 2:
							printf("2");
							result |= cell;
							break;
						case 4:
							printf("3");
							result |= cell;
							break;
						case 8:
							printf("4");
							result |= cell;
							break;
						case 16:
							printf("5");
							result |= cell;
							break;
						case 32:
							printf("6");
							result |= cell;
							break;
						case 64:
							printf("7");
							result |= cell;
							break;
						case 128:
							printf("8");
							result |= cell;
							break;
						case 256:
							printf("9");
							result |= cell;
							break;

						default:
							break;
					}
				}
			}
			printf("\n");
			return result;
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
		sudoku.Initialise( 0, 6, 0,   0, 3, 0,   0, 7, 0,
											 0, 2, 0,   8, 4, 0,   3, 0, 0,
											 0, 0, 0,   0, 0, 0,   4, 0, 6,

											 1, 0, 0,   0, 8, 0,   0, 5, 0,
											 0, 0, 0,   0, 0, 0,   9, 4, 0,
											 8, 0, 0,   0, 7, 0,   0, 0, 0,

											 9, 8, 0,   4, 0, 0,   2, 0, 5,
											 5, 0, 0,   7, 0, 2,   0, 0, 0,
											 0, 0, 0,   0, 6, 0,   0, 1, 0 );
		sudoku.Display();
		sudoku.Calculate();
//		sudoku.Calculate(0,0);
		sudoku.Display();
		sudoku.Calculate(7,5);
		sudoku.Display();
	}

	printf("All done.\n");

	return 0;
}

//==============================================================================

#endif // !USE_OPENGL_SUPERBIBLE

// [EOF]
