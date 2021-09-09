#ifndef _CONSTANTS_H_
#define _CONSTANTS_H_

#include "Color3B.h"

const int GAME_LEFT   = 12;
const int GAME_TOP    = 55;

const int MINE_LOW_WIDTH  = 164;
const int MINE_MIDDLE_WIDTH  = 276;
const int MINE_HIGH_WIDTH  = 500;


const int CELL_WIDTH  = 16;
const int CELL_HEIGHT = 16;

const int CELL_LOW_ROW    = 9;
const int CELL_LOW_COLUMN = 9;
const int CELL_MIDDLE_ROW    = 16;
const int CELL_MIDDLE_COLUMN = 16;
const int CELL_HIGH_ROW    = 16;
const int CELL_HIGH_COLUMN = 30;

//! gray color
static const Color3B grayColor={192,192,192};
//! white color
static const Color3B whiteColor={255,255,255};
//! black color
static const Color3B blackColor={0,0,0};
//! red color
static const Color3B redColor={255,0,0};
//! Flag 1 
static const Color3B mineFlag1={0,0,255};
//! Flag 2 
static const Color3B mineFlag2={0,128,0};
//! Flag 3 
static const Color3B mineFlag3={255,0,0};
//! Flag 4 
static const Color3B mineFlag4={0,0,128};
//! Flag 5 
static const Color3B mineFlag5={128,0,0};
//! Flag 6 
static const Color3B mineFlag6={0,128,128};
//! Flag 7 
static const Color3B mineFlag7=blackColor;
//! Flag 8 
static const Color3B mineFlag8={128,128,128};

const int DIRECTION [8][2]={
	{1,-1},
	{1,1},
	{-1,1},
	{-1,-1},
	{0,-1},
	{1,0},
	{0,1},
	{-1,0}
};

typedef enum{
	Flag0 = 0,
	Flag1,
	Flag2,
	Flag3,
	Flag4,
	Flag5,
	Flag6,
	Flag7,
	Flag8,
	Unknow,
	IsMine,
	alreadyFlag
}CellState;

typedef enum{
	MineLow,
	MineMid,
	MineHigh
}GameType;

typedef struct _ChangeFlag{
	bool MineChangeFlag         ;
	bool HaveClickResultFlag    ;
	bool HaveNewCombinationFlag ;
	_ChangeFlag():MineChangeFlag(false),
		HaveClickResultFlag(false),HaveNewCombinationFlag(false){

	}
	void Clear(){
		MineChangeFlag = HaveClickResultFlag = HaveNewCombinationFlag = false;
	}
}ChangeFlag;

#endif


