
// MiniHelper.h : main header file for the PROJECT_NAME application
//

#pragma once

#ifndef __AFXWIN_H__
	#error "include 'stdafx.h' before including this file for PCH"
#endif

#include "resource.h"		// main symbols

//

class CMineHelperApp : public CWinApp
{
public:
	CMineHelperApp();

// 重载
public:
	virtual BOOL InitInstance();

	DECLARE_MESSAGE_MAP()
};

extern CMineHelperApp theApp;