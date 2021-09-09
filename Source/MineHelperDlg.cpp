
// MiniHelperDlg.cpp : implementation file
//

#include "stdafx.h"
#include "MineHelper.h"
#include "MineHelperDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

HWND	  hWnd, g_WindowHWnd;
// CAboutDlg dialog used for App About

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// Dialog Data
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

// Implementation
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CMiniHelperDlg dialog




CMineHelperDlg::CMineHelperDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CMineHelperDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
	
}

void CMineHelperDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CMineHelperDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BTN_START, &CMineHelperDlg::OnBnClickedBtnStart)
END_MESSAGE_MAP()


// CMiniHelperDlg message handlers

BOOL CMineHelperDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// Add "About..." menu item to system menu.

	// IDM_ABOUTBOX must be in the system command range.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon

	// TODO: Add extra initialization here
	initGame();

	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CMineHelperDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CMineHelperDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

// The system calls this function to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CMineHelperDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

bool CMineHelperDlg::isFlag(int x, int y){
	int cellCenterX = GAME_LEFT + x * CELL_WIDTH + CELL_WIDTH / 2;
	int cellCenterY = GAME_TOP + y * CELL_HEIGHT + CELL_HEIGHT / 2;
	Color3B centerColor = CaptureHelper::getColorByPosition(cellCenterX, cellCenterY, g_WindowHWnd);
	//Color3B topColor = CaptureHelper::getColorByPosition(cellCenterX - 7, cellCenterY, g_WindowHWnd);
	Color3B leftColor = CaptureHelper::getColorByPosition(cellCenterX, cellCenterY - 4, g_WindowHWnd);

	if(c3BEqual(centerColor, blackColor) && c3BEqual(leftColor, redColor)){
		return true;
	}else{
		return false;
	}
}

CellState CMineHelperDlg::getCellStateByPosition(int x, int y){
	int cellCenterX = GAME_LEFT + x * CELL_WIDTH + CELL_WIDTH / 2;
	int cellCenterY = GAME_TOP + y * CELL_HEIGHT + CELL_HEIGHT / 2;
	Color3B centerColor = CaptureHelper::getColorByPosition(cellCenterX, cellCenterY, g_WindowHWnd);
	Color3B topColor = CaptureHelper::getColorByPosition(cellCenterX - 7, cellCenterY, g_WindowHWnd);
	Color3B leftColor = CaptureHelper::getColorByPosition(cellCenterX, cellCenterY - 4, g_WindowHWnd);
	CellState result = Unknow;
	if(c3BEqual(centerColor, grayColor)){
		if(c3BEqual(topColor, whiteColor)){
			result = Unknow;
		}else{
			if(c3BEqual(leftColor, mineFlag7)){
				result = Flag7;
			}else{
				result = Flag0;
			}
		}
	}else if(c3BEqual(centerColor, mineFlag1)){
		result = Flag1;
	}else if(c3BEqual(centerColor, mineFlag2)){
		result = Flag2;
	}else if(c3BEqual(centerColor, mineFlag3)){
		result = Flag3;
	}else if(c3BEqual(centerColor, mineFlag4)){
		result = Flag4;
	}else if(c3BEqual(centerColor, blackColor)){
			result = IsMine;
	}else if(c3BEqual(centerColor, mineFlag5)){
		result = Flag5;
	}else if(c3BEqual(centerColor, mineFlag6)){
		result = Flag6;
	}else if(c3BEqual(centerColor, mineFlag8)){
		result = Flag8;
	}else{
		result = Unknow;
	}
	return result;
}

void CMineHelperDlg::fulfillCells(bool firstTime){
	if(firstTime){
		for(int y = 0; y < cellRow; ++y){
			for(int x = 0; x < cellColumn; ++x){
				Cell* newCell = new Cell(x, y);
				gameMap.SetValue(x,y,newCell);
			}
		}
	}else{
		CellState state = Unknow;
		for(int y = 0; y < cellRow; ++y){
			for(int x = 0; x < cellColumn; ++x){
				Cell* cell = gameMap.GetValue(x,y);
				//we know the cell is a mine, but looks like unknow
				if(cell->getState() == Unknow){
					state = getCellStateByPosition(x, y);
					cell->setState(state);
				}
				if(cell->getState() == IsMine){
					if(isFlag(x, y) == false){
						AIRClick(cell);
					}
				}
			}
		}
	}
	
}

void CMineHelperDlg::initGame(){
	WINDOWPLACEMENT winWndPl;	
	g_WindowHWnd = ::FindWindow( NULL, _T("扫雷"));
	if ( g_WindowHWnd == NULL ){
		if ( ERROR_FILE_NOT_FOUND == WinExec( "winmine.exe", SW_SHOW )){
			MessageBox(_T("未能找到扫雷程序!"), _T("扫雷外挂"), IDOK );
			PostQuitMessage(0);
		}
	}else{
		//always in front
		//::SetFocus(g_WindowHWnd);
		::SetWindowPos( g_WindowHWnd, HWND_TOPMOST, 0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE );
		
		if(::IsIconic(g_WindowHWnd)){
			::ShowWindow(g_WindowHWnd, SW_RESTORE); 
		}

		RECT winRECT;
		GameType gameType = CaptureHelper::getGameType(g_WindowHWnd);
		if(gameType == MineLow){
			cellRow = CELL_LOW_ROW;
			cellColumn = CELL_LOW_COLUMN;
		}else if(gameType == MineMid){
			cellRow = CELL_MIDDLE_ROW;
			cellColumn = CELL_MIDDLE_COLUMN;
		}else if(gameType == MineHigh){
			cellRow = CELL_HIGH_ROW;
			cellColumn = CELL_HIGH_COLUMN;
		}else{
			MessageBox(_T("不支持自定义扫雷!"), _T("扫雷外挂"), IDOK );
			PostQuitMessage(0);
		}
		//gameMap.dispose();
		gameMap = Array2D<Cell*>(cellColumn, cellRow);
		fulfillCells(true);
		//fulfillCells(false);
		mainAnaylysis = MainAnalysis(gameMap);
	}
}

void CMineHelperDlg::AILClick(vector<Cell*>& vecCells){
	int kX, kY;
	::SetFocus(g_WindowHWnd);
	for(int i = 0; i < vecCells.size(); ++i){
		kX = vecCells[i]->getX() * CELL_WIDTH + GAME_LEFT + CELL_WIDTH / 2;
		kY = vecCells[i]->getY() * CELL_HEIGHT + GAME_TOP + CELL_HEIGHT / 2;
		::PostMessage( g_WindowHWnd, WM_LBUTTONDOWN, 0, MAKELPARAM(kX, kY) );
		::PostMessage( g_WindowHWnd, WM_LBUTTONUP, 0, MAKELPARAM(kX, kY) );	
	}					
}

void CMineHelperDlg::AIRClick(Cell* cell){
	int kX, kY;
	::SetFocus(g_WindowHWnd);

	kX = cell->getX() * CELL_WIDTH + GAME_LEFT + CELL_WIDTH / 2;
	kY = cell->getY() * CELL_HEIGHT + GAME_TOP + CELL_HEIGHT / 2;
	::PostMessage( g_WindowHWnd, WM_RBUTTONDOWN, 0, MAKELPARAM(kX, kY) );
	::PostMessage( g_WindowHWnd, WM_RBUTTONUP, 0, MAKELPARAM(kX, kY) );		
}

void CMineHelperDlg::AIRClick(vector<Cell*>& vecCells){
	int kX, kY;
	::SetFocus(g_WindowHWnd);
	for(int i = 0; i < vecCells.size(); ++i){
		kX = vecCells[i]->getX() * CELL_WIDTH + GAME_LEFT + CELL_WIDTH / 2;
		kY = vecCells[i]->getY() * CELL_HEIGHT + GAME_TOP + CELL_HEIGHT / 2;
		::PostMessage( g_WindowHWnd, WM_RBUTTONDOWN, 0, MAKELPARAM(kX, kY) );
		::PostMessage( g_WindowHWnd, WM_RBUTTONUP, 0, MAKELPARAM(kX, kY) );	
	}		
}

void CMineHelperDlg::AIBothClick(Cell* cell){
	int kX, kY;
	::SetFocus(g_WindowHWnd);

	kX = cell->getX() * CELL_WIDTH + GAME_LEFT + CELL_WIDTH / 2;
	kY = cell->getY() * CELL_HEIGHT + GAME_TOP + CELL_HEIGHT / 2;
	::PostMessage( g_WindowHWnd, WM_LBUTTONDOWN, 0, MAKELPARAM(kX, kY) );
	::PostMessage( g_WindowHWnd, WM_RBUTTONDOWN, 0, MAKELPARAM(kX, kY) );
	Sleep(100);
	::PostMessage( g_WindowHWnd, WM_LBUTTONUP, 0, MAKELPARAM(kX, kY) );
	::PostMessage( g_WindowHWnd, WM_RBUTTONUP, 0, MAKELPARAM(kX, kY) );	
}

void CMineHelperDlg::OnBnClickedBtnStart()
{
	initGame();

	//AIBothClick(gameMap.GetValue(2, 3));
	//return;

	vector<Cell*> resultClickCells;
	ChangeFlag firstCheckFlag;
	ChangeFlag combinationCheckFlag;
	CheckPicture:
	fulfillCells(false);//check picture
	
	NormalCheck:
	//normal check
	mainAnaylysis.totalCombination.clear();
	for(int y = 0; y < cellRow; ++y){
		for(int x = 0; x < cellColumn; ++x){
			if(gameMap.GetValue(x, y)->getHaveValue() == true){
				resultClickCells = mainAnaylysis.firstCheck(x,y,firstCheckFlag);
				AILClick(resultClickCells);
				resultClickCells.clear();
			}
		}
	}	
	if(firstCheckFlag.HaveClickResultFlag){
		firstCheckFlag.Clear();
		goto CheckPicture;
	}else if(firstCheckFlag.MineChangeFlag){
		firstCheckFlag.Clear();
		goto NormalCheck;
	}else if(!firstCheckFlag.MineChangeFlag && !firstCheckFlag.HaveClickResultFlag){
		firstCheckFlag.Clear();
		goto CheckCombination;
	}
	CheckCombination:	
	resultClickCells = mainAnaylysis.analysisCombinations(combinationCheckFlag);
    AILClick(resultClickCells);
	resultClickCells.clear();

	if(combinationCheckFlag.HaveClickResultFlag){
		combinationCheckFlag.Clear();
        goto CheckPicture;
	}else if(combinationCheckFlag.MineChangeFlag){
		combinationCheckFlag.Clear();
		goto NormalCheck;
	}else if(combinationCheckFlag.HaveNewCombinationFlag){
		combinationCheckFlag.Clear();
		goto CheckCombination;
	}else if(!combinationCheckFlag.HaveClickResultFlag && !combinationCheckFlag.MineChangeFlag
		&& !combinationCheckFlag.HaveNewCombinationFlag){
		combinationCheckFlag.Clear();
		MessageBox(_T("AI无法做出判断，请手动点击!"), _T("扫雷外挂"), IDOK );
	}
	
	//Color3B result = CaptureHelper::GetColorByPosition(cellCenterX,cellCenterY,g_WindowHWnd);
	//always in front
	//SetWindowPos( g_WindowHWnd, HWND_TOPMOST, 0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE );
}
