// gp.cpp: ���������� ����� ����� ��� ����������.
//

#include "stdafx.h"
#include "gp.h"
#include "App.h"

// ���������� ����������:


// ��������� ���������� �������, ���������� � ���� ������ ����:


int APIENTRY _tWinMain(_In_ HINSTANCE hInstance,
                     _In_opt_ HINSTANCE hPrevInstance,
                     _In_ LPTSTR    lpCmdLine,
                     _In_ int       nCmdShow)
{
	UNREFERENCED_PARAMETER(hPrevInstance);
	UNREFERENCED_PARAMETER(lpCmdLine);
	std::shared_ptr<CApp> app(CApp::getApp());
	
	if (!app->InitInstance(hInstance, nCmdShow))
	{
		return 0;
	}

	int exit_code = app->StartCycle();
	return exit_code;
}




