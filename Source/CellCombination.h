#ifndef _CELLCOMBINATION_H
#define _CELLCOMBINATION_H

#include <vector>

using namespace std;


class CellCombination{
public:
	CellCombination(int mineCount,pair<int,int> pCell):totalMineCount(mineCount),
	parentCell(pCell){

	}
	CellCombination(){
	}
	void addCell(int x, int y);
	int getSize()const;
	int getTotalMineCount()const;
	void setTotalMineCount(int mineCount);
	pair<int,int> getParentCell()const;
	bool isNearMe(CellCombination& other);

	vector<pair<int,int> >& getVecCells();
private:
	vector<pair<int,int> > vecCells;
	int totalMineCount;
	pair<int,int> parentCell;
};


#endif