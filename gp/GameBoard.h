#pragma once
class CGameBoard
{
public:
	CGameBoard();
	virtual ~CGameBoard();
	virtual bool InitTestEnv()=0;
	virtual  void CalcIteration()=0;
private:
	

};

