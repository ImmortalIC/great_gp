#pragma once
#include "UnitFactory.h"
class CUnit :
	public ITacticObject
{
public:
	friend CUnitFactory;

	~CUnit();
	void Render(IRenderer* renderer);
	POINT getPosition();
protected:
	CUnit();
};

