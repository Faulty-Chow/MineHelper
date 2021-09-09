#ifndef _MAINANALYSIS_H_
#define _MAINANALYSIS_H_

#include <vector>
#include <algorithm>
#include "Array2D.h"
#include "Cell.h"
#include "Constants.h"
#include "CellCombination.h"

using namespace std;

//typedef enum{
//	NoChange,
//	MineChange,
//	HaveClickResult,
//	HaveNewCombination
//} AnalysisResult;


class MainAnalysis{
public:
	Array2D<Cell*> gameMap;
	vector<CellCombination> totalCombination;
	MainAnalysis(Array2D<Cell*>& map):gameMap(map){
	}
	MainAnalysis(){
	}
	vector<Cell*> firstCheck(int x, int y,ChangeFlag& changeFlag);

	vector<Cell*> doSubThing(vector<int>& vecInt,ChangeFlag& changeFlag);
	vector<Cell*> doSubThing(int firstIndex,int secondIndex,ChangeFlag& changeFlag);

	static bool compare(int a, int b){  
		if(a > b){  
			return true;  
		}else{  
			return false;  
		}  
	}

	vector<Cell*> analysisCombinations(ChangeFlag& changeFlag);

};


#endif