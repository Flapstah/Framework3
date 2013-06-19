#include "common/stdafx.h"

#include "sudoku.h"

//==============================================================================

CSudoku::CSudoku(void)
	: m_unknownCellCount(0)
	, m_setRecursionCount(0)
		, m_showWorking(false)
{
	for (uint32 row = 0; row < 9; ++row)
	{
		for (uint32 column = 0; column < 9; ++column)
		{
			m_grid[row][column] = 0x1ff;
			++m_unknownCellCount;
		}
	}
}

//==============================================================================

CSudoku::~CSudoku(void)
{
}

//==============================================================================

void CSudoku::Initialise(uint8 v00, uint8 v01, uint8 v02, uint8 v03, uint8 v04, uint8 v05, uint8 v06, uint8 v07, uint8 v08,
		uint8 v10, uint8 v11, uint8 v12, uint8 v13, uint8 v14, uint8 v15, uint8 v16, uint8 v17, uint8 v18,
		uint8 v20, uint8 v21, uint8 v22, uint8 v23, uint8 v24, uint8 v25, uint8 v26, uint8 v27, uint8 v28,
		uint8 v30, uint8 v31, uint8 v32, uint8 v33, uint8 v34, uint8 v35, uint8 v36, uint8 v37, uint8 v38,
		uint8 v40, uint8 v41, uint8 v42, uint8 v43, uint8 v44, uint8 v45, uint8 v46, uint8 v47, uint8 v48,
		uint8 v50, uint8 v51, uint8 v52, uint8 v53, uint8 v54, uint8 v55, uint8 v56, uint8 v57, uint8 v58,
		uint8 v60, uint8 v61, uint8 v62, uint8 v63, uint8 v64, uint8 v65, uint8 v66, uint8 v67, uint8 v68,
		uint8 v70, uint8 v71, uint8 v72, uint8 v73, uint8 v74, uint8 v75, uint8 v76, uint8 v77, uint8 v78,
		uint8 v80, uint8 v81, uint8 v82, uint8 v83, uint8 v84, uint8 v85, uint8 v86, uint8 v87, uint8 v88)
{
	if ((v00 > 0) && (v00 < 10)) SetCell(0, 0, (1<<v00)>>1);
	if ((v01 > 0) && (v01 < 10)) SetCell(0, 1, (1<<v01)>>1);
	if ((v02 > 0) && (v02 < 10)) SetCell(0, 2, (1<<v02)>>1);
	if ((v03 > 0) && (v03 < 10)) SetCell(0, 3, (1<<v03)>>1);
	if ((v04 > 0) && (v04 < 10)) SetCell(0, 4, (1<<v04)>>1);
	if ((v05 > 0) && (v05 < 10)) SetCell(0, 5, (1<<v05)>>1);
	if ((v06 > 0) && (v06 < 10)) SetCell(0, 6, (1<<v06)>>1);
	if ((v07 > 0) && (v07 < 10)) SetCell(0, 7, (1<<v07)>>1);
	if ((v08 > 0) && (v08 < 10)) SetCell(0, 8, (1<<v08)>>1);

	if ((v10 > 0) && (v10 < 10)) SetCell(1, 0, (1<<v10)>>1);
	if ((v11 > 0) && (v11 < 10)) SetCell(1, 1, (1<<v11)>>1);
	if ((v12 > 0) && (v12 < 10)) SetCell(1, 2, (1<<v12)>>1);
	if ((v13 > 0) && (v13 < 10)) SetCell(1, 3, (1<<v13)>>1);
	if ((v14 > 0) && (v14 < 10)) SetCell(1, 4, (1<<v14)>>1);
	if ((v15 > 0) && (v15 < 10)) SetCell(1, 5, (1<<v15)>>1);
	if ((v16 > 0) && (v16 < 10)) SetCell(1, 6, (1<<v16)>>1);
	if ((v17 > 0) && (v17 < 10)) SetCell(1, 7, (1<<v17)>>1);
	if ((v18 > 0) && (v18 < 10)) SetCell(1, 8, (1<<v18)>>1);

	if ((v20 > 0) && (v20 < 10)) SetCell(2, 0, (1<<v20)>>1);
	if ((v21 > 0) && (v21 < 10)) SetCell(2, 1, (1<<v21)>>1);
	if ((v22 > 0) && (v22 < 10)) SetCell(2, 2, (1<<v22)>>1);
	if ((v23 > 0) && (v23 < 10)) SetCell(2, 3, (1<<v23)>>1);
	if ((v24 > 0) && (v24 < 10)) SetCell(2, 4, (1<<v24)>>1);
	if ((v25 > 0) && (v25 < 10)) SetCell(2, 5, (1<<v25)>>1);
	if ((v26 > 0) && (v26 < 10)) SetCell(2, 6, (1<<v26)>>1);
	if ((v27 > 0) && (v27 < 10)) SetCell(2, 7, (1<<v27)>>1);
	if ((v28 > 0) && (v28 < 10)) SetCell(2, 8, (1<<v28)>>1);

	if ((v30 > 0) && (v30 < 10)) SetCell(3, 0, (1<<v30)>>1);
	if ((v31 > 0) && (v31 < 10)) SetCell(3, 1, (1<<v31)>>1);
	if ((v32 > 0) && (v32 < 10)) SetCell(3, 2, (1<<v32)>>1);
	if ((v33 > 0) && (v33 < 10)) SetCell(3, 3, (1<<v33)>>1);
	if ((v34 > 0) && (v34 < 10)) SetCell(3, 4, (1<<v34)>>1);
	if ((v35 > 0) && (v35 < 10)) SetCell(3, 5, (1<<v35)>>1);
	if ((v36 > 0) && (v36 < 10)) SetCell(3, 6, (1<<v36)>>1);
	if ((v37 > 0) && (v37 < 10)) SetCell(3, 7, (1<<v37)>>1);
	if ((v38 > 0) && (v38 < 10)) SetCell(3, 8, (1<<v38)>>1);

	if ((v40 > 0) && (v40 < 10)) SetCell(4, 0, (1<<v40)>>1);
	if ((v41 > 0) && (v41 < 10)) SetCell(4, 1, (1<<v41)>>1);
	if ((v42 > 0) && (v42 < 10)) SetCell(4, 2, (1<<v42)>>1);
	if ((v43 > 0) && (v43 < 10)) SetCell(4, 3, (1<<v43)>>1);
	if ((v44 > 0) && (v44 < 10)) SetCell(4, 4, (1<<v44)>>1);
	if ((v45 > 0) && (v45 < 10)) SetCell(4, 5, (1<<v45)>>1);
	if ((v46 > 0) && (v46 < 10)) SetCell(4, 6, (1<<v46)>>1);
	if ((v47 > 0) && (v47 < 10)) SetCell(4, 7, (1<<v47)>>1);
	if ((v48 > 0) && (v48 < 10)) SetCell(4, 8, (1<<v48)>>1);

	if ((v50 > 0) && (v50 < 10)) SetCell(5, 0, (1<<v50)>>1);
	if ((v51 > 0) && (v51 < 10)) SetCell(5, 1, (1<<v51)>>1);
	if ((v52 > 0) && (v52 < 10)) SetCell(5, 2, (1<<v52)>>1);
	if ((v53 > 0) && (v53 < 10)) SetCell(5, 3, (1<<v53)>>1);
	if ((v54 > 0) && (v54 < 10)) SetCell(5, 4, (1<<v54)>>1);
	if ((v55 > 0) && (v55 < 10)) SetCell(5, 5, (1<<v55)>>1);
	if ((v56 > 0) && (v56 < 10)) SetCell(5, 6, (1<<v56)>>1);
	if ((v57 > 0) && (v57 < 10)) SetCell(5, 7, (1<<v57)>>1);
	if ((v58 > 0) && (v58 < 10)) SetCell(5, 8, (1<<v58)>>1);

	if ((v60 > 0) && (v60 < 10)) SetCell(6, 0, (1<<v60)>>1);
	if ((v61 > 0) && (v61 < 10)) SetCell(6, 1, (1<<v61)>>1);
	if ((v62 > 0) && (v62 < 10)) SetCell(6, 2, (1<<v62)>>1);
	if ((v63 > 0) && (v63 < 10)) SetCell(6, 3, (1<<v63)>>1);
	if ((v64 > 0) && (v64 < 10)) SetCell(6, 4, (1<<v64)>>1);
	if ((v65 > 0) && (v65 < 10)) SetCell(6, 5, (1<<v65)>>1);
	if ((v66 > 0) && (v66 < 10)) SetCell(6, 6, (1<<v66)>>1);
	if ((v67 > 0) && (v67 < 10)) SetCell(6, 7, (1<<v67)>>1);
	if ((v68 > 0) && (v68 < 10)) SetCell(6, 8, (1<<v68)>>1);

	if ((v70 > 0) && (v70 < 10)) SetCell(7, 0, (1<<v70)>>1);
	if ((v71 > 0) && (v71 < 10)) SetCell(7, 1, (1<<v71)>>1);
	if ((v72 > 0) && (v72 < 10)) SetCell(7, 2, (1<<v72)>>1);
	if ((v73 > 0) && (v73 < 10)) SetCell(7, 3, (1<<v73)>>1);
	if ((v74 > 0) && (v74 < 10)) SetCell(7, 4, (1<<v74)>>1);
	if ((v75 > 0) && (v75 < 10)) SetCell(7, 5, (1<<v75)>>1);
	if ((v76 > 0) && (v76 < 10)) SetCell(7, 6, (1<<v76)>>1);
	if ((v77 > 0) && (v77 < 10)) SetCell(7, 7, (1<<v77)>>1);
	if ((v78 > 0) && (v78 < 10)) SetCell(7, 8, (1<<v78)>>1);

	if ((v80 > 0) && (v80 < 10)) SetCell(8, 0, (1<<v80)>>1);
	if ((v81 > 0) && (v81 < 10)) SetCell(8, 1, (1<<v81)>>1);
	if ((v82 > 0) && (v82 < 10)) SetCell(8, 2, (1<<v82)>>1);
	if ((v83 > 0) && (v83 < 10)) SetCell(8, 3, (1<<v83)>>1);
	if ((v84 > 0) && (v84 < 10)) SetCell(8, 4, (1<<v84)>>1);
	if ((v85 > 0) && (v85 < 10)) SetCell(8, 5, (1<<v85)>>1);
	if ((v86 > 0) && (v86 < 10)) SetCell(8, 6, (1<<v86)>>1);
	if ((v87 > 0) && (v87 < 10)) SetCell(8, 7, (1<<v87)>>1);
	if ((v88 > 0) && (v88 < 10)) SetCell(8, 8, (1<<v88)>>1);

	printf("Number of unknown cells: %d\n", m_unknownCellCount);
}

//==============================================================================

bool CSudoku::Solve(void)
{
	bool solved = false;
	Display(m_showWorking);

	printf("Working");

	for (uint32 row = 0; (m_unknownCellCount > 0) && (row < 9); ++row)
	{
		for (uint32 column = 0; (m_unknownCellCount > 0) && (column < 9); ++column)
		{
			printf(".");
			ExtrapolateCell(row, column);
		}
	}

	printf("\n\n");

	Display(m_showWorking);
	return solved;
}

//==============================================================================

void CSudoku::ShowWorking(bool set)
{
	m_showWorking = set;
}

//==============================================================================

void CSudoku::SetCell(uint32 row, uint32 column, uint16 bitmask)
{
	++m_setRecursionCount;

	if (IsSingleValue(bitmask))
	{
		if (!IsSingleValue(m_grid[row][column]))
		{
			--m_unknownCellCount;
		}
		m_grid[row][column] = bitmask;

		for (uint32 index = 0; index < 9; ++index)
		{
			// For all cells in this column (except the one specified)
			// remove the inferred number from the bitmask
			if (index != row)
			{
				bool undetermined = !IsSingleValue(m_grid[index][column]);
				m_grid[index][column] &= ~bitmask;
				if (undetermined && IsSingleValue(m_grid[index][column]))
				{
					// We've just worked out this cell, so set it
					--m_unknownCellCount;
					if (m_showWorking)
					{
						printf("%02d: determined (%d, %d): ", m_setRecursionCount, index, column);
						DisplayCell(row, column);
						printf(", %d unknown cells remaining...\n", m_unknownCellCount);
					}
					SetCell(index, column, m_grid[index][column]);
				}
			}

			// For all cells in this row (except the one specified)
			// remove the inferred number from the bitmask
			if (index != column)
			{
				bool undetermined = !IsSingleValue(m_grid[row][index]);
				m_grid[row][index] &= ~bitmask;
				if (undetermined && IsSingleValue(m_grid[row][index]))
				{
					// We've just worked out this cell, so set it
					--m_unknownCellCount;
					if (m_showWorking)
					{
						printf("%02d: determined (%d, %d): ", m_setRecursionCount, row, index);
						DisplayCell(row, column);
						printf(", %d unknown cells remaining...\n", m_unknownCellCount);
					}
					SetCell(row, index, m_grid[row][index]);
				}
			}
		}

		// For all cells in this 3x3 block (except the one specified)
		// remove the inferred number from the bitmask
		uint32 blockRow = (row/3)*3;
		uint32 blockColumn = (column/3)*3;

		for (uint32 dr = 0; dr < 3; ++dr)
		{
			for (uint32 dc = 0; dc < 3; ++dc)
			{
				if (((blockRow+dr) != row) || ((blockColumn+dc) != column))
				{
					bool undetermined = !IsSingleValue(m_grid[blockRow+dr][blockColumn+dc]);
					m_grid[blockRow+dr][blockColumn+dc] &= ~bitmask;
					if (undetermined && IsSingleValue(m_grid[blockRow+dr][blockColumn+dc]))
					{
						// We've just worked out this cell, so set it
						--m_unknownCellCount;
						if (m_showWorking)
						{
							printf("%02d: determined (%d, %d): ", m_setRecursionCount, blockRow+dr, blockColumn+dc);
							DisplayCell(row, column);
							printf(", %d unknown cells remaining...\n", m_unknownCellCount);
						}
						SetCell(blockRow+dr, blockColumn+dc, m_grid[blockRow+dr][blockColumn+dc]);
					}
				}
			}
		}
	}

	--m_setRecursionCount;
}

//==============================================================================

void CSudoku::ExtrapolateCell(uint32 row, uint32 column)
{
	uint16 rowExcluded = 0;
	uint16 columnExcluded = 0;
	uint16 blockExcluded = 0;
	uint16& cell = m_grid[row][column];

	for (uint32 index = 0; index < 9; ++index)
	{
		// For all cells in this column (except the one specified)
		// OR all the currently worked out values to create a mask
		if (index != row)
		{
			columnExcluded |= m_grid[index][column];
		}

		// For all cells in this row (except the one specified) OR
		// all the currently worked out values to create a mask
		if (index != column)
		{
			rowExcluded |= m_grid[row][index];
		}
	}

	// For all cells in this 3x3 block (except the one specified)
	// OR all the currently worked out values to create a mask
	uint32 blockRow = (row/3)*3;
	uint32 blockColumn = (column/3)*3;

	for (uint32 dr = 0; dr < 3; ++dr)
	{
		for (uint32 dc = 0; dc < 3; ++dc)
		{
			if (((blockRow+dr) != row) || ((blockColumn+dc) != column))
			{
				blockExcluded |= m_grid[blockRow+dr][blockColumn+dc];
			}
		}
	}

	/*
		 if (m_showWorking)
		 {
		 printf("Excluded from row %d:           ", row);
		 DisplayPossibilities(rowExcluded);
		 printf("\nExcluded from column %d:        ", column);
		 DisplayPossibilities(columnExcluded);
		 printf("\nExcluded from block (%d, %d):    ", (row/3)*3, (column/3)*3);
		 DisplayPossibilities(blockExcluded);
		 printf("\nInferred number from row     : ");
		 DisplayPossibilities(cell & ~rowExcluded);
		 printf("\nInferred number from column  : ");
		 DisplayPossibilities(cell & ~columnExcluded);
		 printf("\nInferred number from block   : ");
		 DisplayPossibilities(cell & ~blockExcluded);
		 printf("\n");
		 }
		 */

	uint16 inferredBitmask = cell & ~rowExcluded;
	if (IsSingleValue(inferredBitmask))
	{
		SetCell(row, column, inferredBitmask);
	}
	else
	{
		inferredBitmask = cell & ~columnExcluded;
		if (IsSingleValue(inferredBitmask))
		{
			SetCell(row, column, inferredBitmask);
		}
		else
		{
			inferredBitmask = cell & ~blockExcluded;
			if (IsSingleValue(inferredBitmask))
			{
				SetCell(row, column, inferredBitmask);
			}
		}
	}
}

//==============================================================================

bool CSudoku::IsSingleValue(uint16 bitMask)
{
	bool isSingleValue = false;

	switch (bitMask)
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
			isSingleValue = true;
			break;

		default:
			break;
	}

	return isSingleValue;
}

//==============================================================================

void CSudoku::DisplayCell(uint32 row, uint32 column)
{
	printf("|");
	DisplayPossibilities(m_grid[row][column]);
	printf("|");
}

//==============================================================================

void CSudoku::DisplayPossibilities(uint16 bitMask)
{
	char cell[16];
	sprintf(cell, "123456789");

	for (uint32 index = 0; index < 9; ++index)
	{
		if ((bitMask & (1<<index)) == 0)
		{
			cell[index] = '.';
		}
	}
	puts(cell);
}

//==============================================================================

void CSudoku::Display(bool expanded)
{
	for (uint32 row = 0; row < 9; ++row)
	{
		if (expanded)
		{
			for (uint32 column = 0; column < 9; ++column)
			{
				DisplayCell(row, column);
				if ((column == 2) || (column == 5))
				{
					printf("*");
				}
			}

			printf("   ");
		}

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
					printf("%d", (int)(log((float)m_grid[row][column])/log(2.0f))+1);
					break;

				default:
					printf(".");
					break;
			}

			if ((column == 2) || (column == 5))
			{
				printf("*");
			}
		}

		printf("\n");
		if ((row == 2) || (row == 5))
		{
			if (expanded)
			{
				printf("*****************************************************************************************************   ***********\n");
			}
			else
			{
				printf("***********\n");
			}
		}
	}
	printf("\n");
}

//==============================================================================
// [EOF]

