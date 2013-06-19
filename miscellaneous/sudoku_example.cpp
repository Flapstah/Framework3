#include "common/stdafx.h"

#include "sudoku.h"

int main(int argc, char* argv[])
{
	IGNORE_PARAMETER(argc);
	IGNORE_PARAMETER(argv);

	CSudoku sudoku;
	sudoku.ShowWorking(true);

	// Blank sudoku template
	//  x x x   x x x   x x x        x x x   x x x   x x x
	//  x x x   x x x   x x x        x x x   x x x   x x x
	//  x x x   x x x   x x x        x x x   x x x   x x x
	//
	//  x x x   x x x   x x x        x x x   x x x   x x x
	//  x x x   x x x   x x x        x x x   x x x   x x x
	//  x x x   x x x   x x x        x x x   x x x   x x x
	//
	//  x x x   x x x   x x x        x x x   x x x   x x x
	//  x x x   x x x   x x x        x x x   x x x   x x x
	//  x x x   x x x   x x x        x x x   x x x   x x x
	/*
	sudoku.Initialise( 0, 0, 0,   0, 0, 0,   0, 0, 0,
										 0, 0, 0,   0, 0, 0,   0, 0, 0,
										 0, 0, 0,   0, 0, 0,   0, 0, 0,

										 0, 0, 0,   0, 0, 0,   0, 0, 0,
										 0, 0, 0,   0, 0, 0,   0, 0, 0,
										 0, 0, 0,   0, 0, 0,   0, 0, 0,

										 0, 0, 0,   0, 0, 0,   0, 0, 0,
										 0, 0, 0,   0, 0, 0,   0, 0, 0,
										 0, 0, 0,   0, 0, 0,   0, 0, 0 );
	*/

	// Easy sudoku:									 Solution:
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
	/*
	sudoku.Initialise( 0, 6, 0,   0, 3, 0,   0, 7, 0,
										 0, 2, 0,   8, 4, 0,   3, 0, 0,
										 0, 0, 0,   0, 0, 0,   4, 0, 6,

										 1, 0, 0,   0, 8, 0,   0, 5, 0,
										 0, 0, 0,   0, 0, 0,   9, 4, 0,
										 8, 0, 0,   0, 7, 0,   0, 0, 0,

										 9, 8, 0,   4, 0, 0,   2, 0, 5,
										 5, 0, 0,   7, 0, 2,   0, 0, 0,
										 0, 0, 0,   0, 6, 0,   0, 1, 0 );
	*/

	// Medium sudoku:								 Solution:
	//  6 x x   x 5 9   x x x        6 3 8   4 5 9   2 7 1
	//  x 9 2   1 x x   x 4 x        7 9 2   1 8 6   3 4 5
	//  x x x   2 x x   6 8 x        4 1 5   2 7 3   6 8 9
	//
	//  x x x   x x x   4 3 x        8 5 7   9 1 2   4 3 6
	//  x x x   5 x x   x x x        3 2 1   5 6 4   7 9 8
	//  x x 6   7 x 8   1 x x        9 4 6   7 3 8   1 5 2
	//
	//  5 6 3   x 4 x   x 2 7        5 6 3   8 4 1   9 2 7
	//  x x x   x x x   8 x x        1 7 9   3 2 5   8 6 4
	//  x x 4   x 9 x   x x 3        2 8 4   6 9 7   5 1 3
	/*
	sudoku.Initialise( 6, 0, 0,   0, 5, 9,   0, 0, 0,
										 0, 9, 2,   1, 0, 0,   0, 4, 0,
										 0, 0, 0,   2, 0, 0,   6, 8, 0,

										 0, 0, 0,   0, 0, 0,   4, 3, 0,
										 0, 0, 0,   5, 0, 0,   0, 0, 0,
										 0, 0, 6,   7, 0, 8,   1, 0, 0,

										 5, 6, 3,   0, 4, 0,   0, 2, 7,
										 0, 0, 0,   0, 0, 0,   8, 0, 0,
										 0, 0, 4,   0, 9, 0,   0, 0, 3 );
	*/

	// Hard sudoku:									 Solution:
	//  9 1 6   x x x   5 x 8        9 1 6   4 2 7   5 3 8
	//  x x x   x x x   x x 1        2 4 5   3 8 9   6 7 1
	//  x 7 8   x 6 x   x x 2        3 7 8   5 6 1   4 9 2
	//
	//  x x x   x 3 2   7 x 5        4 9 1   6 3 2   7 8 5
	//  5 6 x   7 4 x   x x x        5 6 2   7 4 8   9 1 3
	//  7 x x   9 x x   x 6 x        7 8 3   9 1 5   2 6 4
	//
	//  x x 4   x 9 3   1 x x        6 2 4   8 9 3   1 5 7
	//  x 5 x   x 7 x   x x x        8 5 9   1 7 4   3 2 6
	//  x x x   x 5 x   x x 9        1 3 7   2 5 6   8 4 9
	sudoku.Initialise( 9, 1, 6,   0, 0, 0,   5, 0, 8,
										 0, 0, 0,   0, 0, 0,   0, 0, 1,
										 0, 7, 8,   0, 6, 0,   0, 0, 2,

										 0, 0, 0,   0, 3, 2,   7, 0, 5,
										 5, 6, 0,   7, 4, 0,   0, 0, 0,
										 7, 0, 0,   9, 0, 0,   0, 6, 0,

										 0, 0, 4,   0, 9, 3,   1, 0, 0,
										 0, 5, 0,   0, 7, 0,   0, 0, 0,
										 0, 0, 0,   0, 5, 0,   0, 0, 9 );

	// World's hardest sudoku
	//  x x 5   3 x x   x x x
	//  8 x x   x x x   x 2 x
	//  x 7 x   x 1 x   5 x x
	//
	//  4 x x   x x 5   3 x x
	//  x 1 x   x 7 x   x x 6
	//  x x 3   2 x x   x 8 x
	//
	//  x 6 x   5 x x   x x 9
	//  x x 4   x x x   x 3 x
	//  x x x   x x 9   7 x x
	//
	/*
	sudoku.Initialise( 0, 0, 5,   3, 0, 0,   0, 0, 0,
										 8, 0, 0,   0, 0, 0,   0, 2, 0,
										 0, 7, 0,   0, 1, 0,   5, 0, 0, 

										 4, 0, 0,   0, 0, 5,   3, 0, 0,
										 0, 1, 0,   0, 7, 0,   0, 0, 6,
										 0, 0, 3,   2, 0, 0,   0, 8, 0,

										 0, 6, 0,   5, 0, 0,   0, 0, 9,
										 0, 0, 4,   0, 0, 0,   0, 3, 0,
										 0, 0, 0,   0, 0, 9,   7, 0, 0 );
	 */

	sudoku.Solve();

	return 0;
}
