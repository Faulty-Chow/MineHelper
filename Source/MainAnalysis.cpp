#include "stdafx.h"
#include "MainAnalysis.h"
#include <algorithm>
#include <assert.h>

vector<Cell*> MainAnalysis::firstCheck(int x, int y, ChangeFlag& changeFlag){
	vector<Cell*> resultClickCells;
	vector<Cell*> vecUnknowCells;

	Cell* currentCell;
	Cell* aroundCell;
	currentCell = gameMap.GetValue(x, y);
	if(currentCell->getState() == Unknow || currentCell->getState() == Flag0){
		return resultClickCells;
	}
	//获取此格周围总共有多少雷
	int totalMineCount = currentCell->getState();
	int totalUnKnowCount = 0;
	int alreadyFindMineCount = 0;
	int aroundX,aroundY;
	//获取此格周围未知格子的数量
	for(int i = 0; i < 8; ++i){
		aroundX = x + DIRECTION[i][0];
		aroundY = y + DIRECTION[i][1];
		if(gameMap.IsInArray(aroundX, aroundY)){
			aroundCell = gameMap.GetValue(aroundX, aroundY);
			if(aroundCell->getState() == Unknow){
				++totalUnKnowCount;
				vecUnknowCells.push_back(aroundCell);
			}else if(aroundCell->getState() == IsMine){
				++alreadyFindMineCount;
			}
		}
	}
	if(totalUnKnowCount == 0) return resultClickCells;
	int subMineCount = totalMineCount - alreadyFindMineCount;
	//排除旗帜
	if(subMineCount == totalUnKnowCount){
		changeFlag.MineChangeFlag = true;
		for(int i = 0; i < vecUnknowCells.size(); ++i){
			vecUnknowCells[i]->setState(IsMine);
		}
		currentCell->setHaveValue(false);
		return resultClickCells;
	}else if(totalMineCount == alreadyFindMineCount){
		changeFlag.HaveClickResultFlag = true;
		currentCell->setHaveValue(false);
		return vecUnknowCells;
	}else if(subMineCount < totalUnKnowCount){
		CellCombination newCombination(subMineCount,
			make_pair(currentCell->getX(),currentCell->getY()));
		for(int i = 0; i < vecUnknowCells.size(); ++i){
			newCombination.addCell(vecUnknowCells[i]->getX(), vecUnknowCells[i]->getY());
		}
		totalCombination.push_back(newCombination);
	}
	return resultClickCells;
}

vector<Cell*> MainAnalysis::doSubThing(vector<int>& vecInt,ChangeFlag& changeFlag){
	vector<Cell*> resultClickCells;
	int firstIndex = 0;
	int secondIndex = 0;
	bool findFirst = false;
	//寻找包含这两个和方程的方程
	for(int i = 0; i < vecInt.size(); ++i){  
		if(vecInt[i] == 1){
			if(findFirst == false){
				firstIndex = i;
				findFirst = true;
			}else if(findFirst == true){
				secondIndex = i;
				break;
			}
		}
	}
	resultClickCells = doSubThing(firstIndex, secondIndex, changeFlag);

	return resultClickCells;
}


vector<Cell*> MainAnalysis::doSubThing(int firstIndex,int secondIndex,ChangeFlag& changeFlag){
	vector<Cell*> resultClickCells;
	if(totalCombination[firstIndex].isNearMe(totalCombination[secondIndex]) &&
		totalCombination[firstIndex].getSize() != totalCombination[secondIndex].getSize()){
			//初始化一个新列表
			CellCombination baseOne;
			CellCombination otherOne;
			if(totalCombination[firstIndex].getSize() < totalCombination[secondIndex].getSize()){
				int tmp = secondIndex;
				secondIndex = firstIndex;
				firstIndex = tmp;
			}
			baseOne = CellCombination(totalCombination[firstIndex]);
			otherOne = CellCombination(totalCombination[secondIndex]);
			auto itr = baseOne.getVecCells().begin();

			for(int i = 0; i < otherOne.getSize(); ++i){
				//找到一个就排除一个
				itr = find(baseOne.getVecCells().begin(), 
					baseOne.getVecCells().end(), otherOne.getVecCells()[i]);
				if(itr != baseOne.getVecCells().end()){
					//排除
					baseOne.getVecCells().erase(itr);
				}else{
					//如果找不到，意味着otherOne不是baseOne的加数
					//因此直接返回
					return resultClickCells;
				}
			}
			if(baseOne.getSize() == 0)return resultClickCells;

			int subMineCount = baseOne.getTotalMineCount() - otherOne.getTotalMineCount();
			//剩下的全是雷,x1 + x2 + x3 = 1
			//                 x1 + x2 = 0
			//               得 x3 = 1, x3 是雷
			if(baseOne.getSize() == subMineCount){
				for(int i = 0; i < baseOne.getSize(); ++i){
					gameMap.GetValue(baseOne.getVecCells()[i].first,
						baseOne.getVecCells()[i].second)->setState(IsMine);
				}
				changeFlag.MineChangeFlag = true;
			}
			//剩下的全不是雷, x1 + x2 + x3 + x4 = 2
			//                      x1 + x2 + x3 = 2
			//                    得 x4 = 0, x4 不是雷
			else if(subMineCount == 0){
				for(int i = 0; i < baseOne.getSize(); ++i){
					Cell* cell = gameMap.GetValue(baseOne.getVecCells()[i].first,
						baseOne.getVecCells()[i].second);
					resultClickCells.push_back(cell);
				}
				changeFlag.HaveClickResultFlag = true;
			}
			//处理和已经确定的情况, x1 + x2 + x3 + x4 = 2
			//                    x1 + x2 = 1
			//                 得 x3 + x4 = 1
			else if(baseOne.getSize() > subMineCount){
				baseOne.setTotalMineCount(subMineCount);
				bool alreadyExist = false;
				for(int i = 0; i < totalCombination.size(); ++i){
					if(totalCombination[i].getVecCells() == baseOne.getVecCells()){
						alreadyExist = true;
						break;
					}
				}
				if(alreadyExist == false){
					totalCombination.push_back(baseOne);
					changeFlag.HaveNewCombinationFlag = true;
				}
			}
	}

	return resultClickCells;
} 

bool compareCombo(CellCombination& c1, CellCombination& c2){
	if(c1.getSize() < c2.getSize()){
		return true;
	}else{
		return false;
	}
}

vector<Cell*> MainAnalysis::analysisCombinations(ChangeFlag& changeFlag){
	vector<Cell*> resultClickCells;
	sort(totalCombination.begin(), totalCombination.end(), compareCombo);
	for(int i = totalCombination.size() - 1; i >=1; --i){
		if(totalCombination[i].getSize() > 2){
			for(int j = i - 1; j >= 0; --j){
				resultClickCells = doSubThing(i,j, changeFlag);
				if(resultClickCells.size() > 0){
					return resultClickCells;
				}
			}
		}else{
			break;
		}
	}

	return resultClickCells;



	//initial first combination like:1,1,0,0,0
	//int total = totalCombination.size();
	//vector<Cell*> resultClickCells;
	//if(total < 2) return resultClickCells;

	//
	//vector<int> vecInt(total,0);  
	//for(int i = 0; i < 2; ++i){  
	//	vecInt[i] = 1;  
	//}  
	////find one just return
	//resultClickCells = doSubThing(vecInt, changeFlag);
	//if(resultClickCells.size() > 0){
	//	return resultClickCells;
	//}

	//for(int i = 0; i < total - 1; ++i){  
	//	if(vecInt[i] == 1 && vecInt[i+1] == 0){  
	//		//1. first exchange 1 and 0 to 0 1  
	//		swap(vecInt[i], vecInt[i+1]);  

	//		//2.move all 1 before vecInt[i] to left  
	//		sort(vecInt.begin(),vecInt.begin() + i,MainAnalysis::compare);  

	//		//after step 1 and 2, a new combination is exist
	//		
	//		resultClickCells = doSubThing(vecInt, changeFlag);
	//		//find one just return
	//		if(resultClickCells.size() > 0){
	//			return resultClickCells;
	//		}

	//		//try do step 1 and 2 from front  
	//		i = -1;  
	//	}  
	//}  
	//return resultClickCells;
}  