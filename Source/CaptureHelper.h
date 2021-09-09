#ifndef _CAPTURE_
#define _CAPTURE_

#include "stdafx.h"
#include "Array2D.h"
#include "Color3B.h"
#include "assert.h"
#include "Constants.h"

class CaptureHelper{
public:
	static Color3B getColorByPosition( int x, int y,HWND hWnd){
		HDC windowDC;
		RECT winRECT;      // 游戏窗口的RECT
		POINT po;          // 位置

		// 获取游戏场景
		windowDC = GetDC(hWnd);
		assert( windowDC );
		// 获得游戏窗口的RECT
		GetClientRect( hWnd, &winRECT );
		po.x = winRECT.left + x;
		po.y = winRECT.top + y;
		COLORREF retColor = GetPixel( windowDC, po.x, po.y );

		BYTE red = GetRValue(retColor);//get red；
		BYTE green = GetGValue(retColor);//get green
		BYTE blue = GetBValue(retColor);//get blue
		// 释放场景
		ReleaseDC( hWnd, windowDC );
		Color3B resultColor={red, green, blue};
		return resultColor;
	}

	static GameType getGameType(HWND hWnd){
		RECT winRECT;
		GetClientRect( hWnd, &winRECT );
		if(winRECT.right == MINE_LOW_WIDTH){
			return MineLow;
		}else if(winRECT.right == MINE_MIDDLE_WIDTH){
			return MineMid;
		}else if(winRECT.right == MINE_HIGH_WIDTH){
			return MineHigh;
		}
	}
};



#endif