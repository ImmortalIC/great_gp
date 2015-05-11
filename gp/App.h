#pragma once
#include "Renderer.h"
#include "ResourceManager.h"
#include "GameBoard.h"
#define MAX_LOADSTRING 100

class CApp
{
public:
	
	BOOL InitInstance(HINSTANCE, int);
	int StartCycle();
	static CApp* getApp();
	~CApp();
	CRenderer main_renderer;
	CResourceManager main_r_manager;
private:
	CApp() {};
	CApp(const CApp &app){};
	CApp& operator=(CApp&){};
	static CApp* instance;
	static LRESULT CALLBACK	WndProc(HWND, UINT, WPARAM, LPARAM);
	HINSTANCE hInst;								// текущий экземпляр
	int nCmdShow;
	TCHAR szTitle[MAX_LOADSTRING];					// Текст строки заголовка
	TCHAR szWindowClass[MAX_LOADSTRING];			// имя класса главного окна
	ATOM MyRegisterClass(HINSTANCE hInstance);
	LRESULT ProcessMessages(HWND, UINT, WPARAM, LPARAM);
	std::shared_ptr<CGameBoard> board;

};

