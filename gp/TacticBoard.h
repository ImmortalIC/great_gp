#pragma once
#include "GameBoard.h"
#include "TacticMap.h"
class CTacticBoard :
	public CGameBoard
{
public:
	CTacticBoard();
	~CTacticBoard();
	void CalcIteration(){};
private:
	CTacticMap map;
};

