
// MiniHelperDlg.h : header file
//

#pragma once

#include <vector>
#include "CaptureHelper.h"
#include "Constants.h"
#include "Cell.h"
#include "Array2D.h"
#include "MainAnalysis.h"

using namespace std;




// CMiniHelperDlg dialog
class CMineHelperDlg : public CDialogEx
{
// Construction
public:
	CMineHelperDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	enum { IDD = IDD_MINIHELPER_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support


// Implementation
protected:
	HICON m_hIcon;
	Array2D<Cell*> gameMap;
	GameType gameType;
	MainAnalysis mainAnaylysis;
	int cellRow;
	int cellColumn;

	// Generated message map functions
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	
	afx_msg void OnBnClickedBtnStart();
	void AILClick(vector<Cell*>& vecCells);
	void AIRClick(vector<Cell*>& vecCells);
	void AIRClick(Cell* cell);
	void AIBothClick(Cell* cell);
	void initGame();
	CellState getCellStateByPosition(int x, int y);
	bool isFlag(int x, int y);
	void fulfillCells(bool firstTime);
};
