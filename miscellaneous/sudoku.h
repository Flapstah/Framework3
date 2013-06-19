#if !defined(__SUDOKU_H__)
#define __SUDOKU_H__

//==============================================================================

//==============================================================================
// CSudoku
//==============================================================================
class CSudoku
{
	public:
		//==========================================================================
		// CSudoku construction
		//==========================================================================
		CSudoku(void);
		~CSudoku(void);

		//==========================================================================
		// InitialiseCell() initialises a single cell with a value
		//==========================================================================
		void Initialise(uint8 v00, uint8 v01, uint8 v02, uint8 v03, uint8 v04, uint8 v05, uint8 v06, uint8 v07, uint8 v08,
										uint8 v10, uint8 v11, uint8 v12, uint8 v13, uint8 v14, uint8 v15, uint8 v16, uint8 v17, uint8 v18,
										uint8 v20, uint8 v21, uint8 v22, uint8 v23, uint8 v24, uint8 v25, uint8 v26, uint8 v27, uint8 v28,
										uint8 v30, uint8 v31, uint8 v32, uint8 v33, uint8 v34, uint8 v35, uint8 v36, uint8 v37, uint8 v38,
										uint8 v40, uint8 v41, uint8 v42, uint8 v43, uint8 v44, uint8 v45, uint8 v46, uint8 v47, uint8 v48,
										uint8 v50, uint8 v51, uint8 v52, uint8 v53, uint8 v54, uint8 v55, uint8 v56, uint8 v57, uint8 v58,
										uint8 v60, uint8 v61, uint8 v62, uint8 v63, uint8 v64, uint8 v65, uint8 v66, uint8 v67, uint8 v68,
										uint8 v70, uint8 v71, uint8 v72, uint8 v73, uint8 v74, uint8 v75, uint8 v76, uint8 v77, uint8 v78,
										uint8 v80, uint8 v81, uint8 v82, uint8 v83, uint8 v84, uint8 v85, uint8 v86, uint8 v87, uint8 v88);

		//==========================================================================
		// Solve() will attempt to solve the Sudoku puzzle
		//==========================================================================
		bool Solve(void);

		//==========================================================================
		// If ShowWorking(true) is called before Solve(), then interrim stages will
		// be displayed
		//==========================================================================
		void ShowWorking(bool set);

	private:
		//==========================================================================
		// SetCell() sets a particular cell with a value, and excludes that value
		//		from the row, column and 3x3 major group
		// ExtrapolateCell() will check if there is a unique solution for that cell
		//==========================================================================
		void SetCell(uint32 row, uint32 column, uint16 bitmask);
		void ExtrapolateCell(uint32 row, uint32 column);

		//==========================================================================
		// IsSingleValue() determines if a bitmask represents a single (and
		// therefore final) value
		//==========================================================================
		bool IsSingleValue(uint16 bitMask);

		//==========================================================================
		// Debugging/visualisation functions
		//==========================================================================
		void DisplayCell(uint32 row, uint32 column);
		void DisplayPossibilities(uint16 bitMask);
		void Display(bool expanded);

	private:
		uint16 m_grid[9][9];
		uint16 m_unknownCellCount;
		uint16 m_setRecursionCount;
		bool m_showWorking;
};

//==============================================================================

#endif // End [!defined(__SUDOKU_H__)]
// [EOF]

