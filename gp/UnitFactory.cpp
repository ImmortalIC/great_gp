#include "stdafx.h"
#include "Unit.h"

CUnitFactory::CUnitFactory()
{
}


CUnitFactory::~CUnitFactory()
{
}

ITacticObject* CUnitFactory::CreateUnit(BYTE resource, UINT x, UINT y)
{
	CUnit* result = new CUnit();
	result->_resource = resource;
	result->_x = x;
	result->_y = y;
	return result;
}