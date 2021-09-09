#include "stdafx.h"
#include "CellCombination.h"

void CellCombination::addCell(int x, int y){
	pair<int,int> newOne = make_pair(x, y);
	vecCells.push_back(newOne);
}

int CellCombination::getSize()const{
	return vecCells.size();
}

int CellCombination::getTotalMineCount()const{
	return totalMineCount;
}

void CellCombination::setTotalMineCount(int mineCount){
	totalMineCount = mineCount;
}

pair<int,int> CellCombination::getParentCell()const{
	return parentCell;
}

bool CellCombination::isNearMe(CellCombination& other){
	if(abs(parentCell.first - other.getParentCell().first) > 2 ||
		abs(parentCell.second - other.getParentCell().second > 2)){
			return false;
	}else{
		return true;
	}
}

vector<pair<int,int> >& CellCombination::getVecCells(){
	return vecCells;
}