#include "stdafx.h"
#include "TacticBoard.h"
#include "UnitFactory.h"
typedef std::unique_ptr<ITacticObject> TacticObj_ptr;
CTacticBoard::CTacticBoard(IRenderer* render, IResourceManager* man)
{
	this->renderer = render;
	this->r_manager = man;
}


CTacticBoard::~CTacticBoard()
{
}


void CTacticBoard::CalcIteration()
{
	this->Render();
}

bool CTacticBoard::InitTestEnv()
{
	BYTE res = map.InitMap("test_map.map", r_manager);
	if ( res!= TMAP_OK)
		return false;
	UINT unit1_res, unit2_res;
	std::string unit1 = "test_unit1.bmp", unit2 = "test_unit2.bmp";
	unit1_res = r_manager->addResource(RES_GDI_BITMAP, (LPCTSTR)unit1.c_str());
	unit2_res = r_manager->addResource(RES_GDI_BITMAP, (LPCTSTR)unit2.c_str());
	if (unit1_res == NULL || unit2_res == NULL)
	{
		return false;
	}
	CUnitFactory fact;

	objects.push_back(TacticObj_ptr(fact.CreateUnit(unit1_res, 100, 100)));
	objects.push_back(TacticObj_ptr(fact.CreateUnit(unit2_res, 600, 200)));
	objects.push_back(TacticObj_ptr(fact.CreateUnit(unit1_res, 600, 800)));
	return true;
}

void CTacticBoard::Render()
{
	map.Render(renderer);
	for (auto it = objects.begin(); it != objects.end(); it++)
	{
		(*it)->Render(renderer);
	}
}
