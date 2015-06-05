#pragma once
#include "GameBoard.h"
#include "TacticMap.h"
class CTacticBoard :
	public CGameBoard
{
public:
	CTacticBoard(IRenderer* render,IResourceManager* man);
	~CTacticBoard();
	bool InitTestEnv();
	void CalcIteration();
private:
	CTacticMap map;
	std::vector<std::unique_ptr<ITacticObject>> objects;
	IRenderer* renderer;
	IResourceManager* r_manager;
	void Render();
};

