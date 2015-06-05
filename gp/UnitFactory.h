#pragma once
#include "base_interfaces.h"
class CUnitFactory
{
public:
	CUnitFactory();
	~CUnitFactory();
	ITacticObject* CreateUnit(BYTE resource,UINT x,UINT y);
};

