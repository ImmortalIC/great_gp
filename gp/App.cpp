#include "stdafx.h"
#include "resource.h"
#include "App.h"
#define WIDTH 1920
#define HEIGHT 1080


CApp* CApp::instance;

CApp* CApp::getApp()
{
	if (CApp::instance == nullptr)
	{
		CApp::instance = new CApp();

	}
	return CApp::instance;
}


ATOM CApp::MyRegisterClass(HINSTANCE hInstance)
{
	WNDCLASSEX wcex;

	wcex.cbSize = sizeof(WNDCLASSEX);

	wcex.style = CS_HREDRAW | CS_VREDRAW;
	wcex.lpfnWndProc = CApp::WndProc;
	wcex.cbClsExtra = 0;
	wcex.cbWndExtra = 0;
	wcex.hInstance = hInstance;
	wcex.hIcon = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_GP));
	wcex.hCursor = LoadCursor(NULL, IDC_ARROW);
	wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
	wcex.lpszClassName =szWindowClass;
	wcex.lpszMenuName = MAKEINTRESOURCE(0);
	wcex.hIconSm = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

	return RegisterClassEx(&wcex);
}

BOOL CApp::InitInstance(HINSTANCE hInstance, int nCmdShow)
{
	HWND hWnd;
	this->hInst = hInstance;
	this->nCmdShow = nCmdShow;
	LoadString(hInstance, IDS_APP_TITLE, this->szTitle, MAX_LOADSTRING);
	LoadString(hInstance, IDC_GP, this->szWindowClass, MAX_LOADSTRING);
	this->MyRegisterClass(hInstance);
	
	hWnd = CreateWindow(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT, 0, WIDTH, HEIGHT, NULL, NULL, hInstance, NULL);

	if (!hWnd)
	{
		return FALSE;
	}
	main_renderer.InitRenderer(hWnd,WIDTH, HEIGHT);
	UINT res;
	res=main_r_manager.addResource(RES_GDI_BITMAP, L"test_sprite1.bmp");
	main_renderer.AddToQueue(500, 500, res);
	ShowWindow(hWnd, this->nCmdShow);
	UpdateWindow(hWnd);

	return TRUE;
	
}

LRESULT CALLBACK CApp::WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	return instance->ProcessMessages(hWnd, message, wParam, lParam);
	
}

LRESULT CApp::ProcessMessages(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	int wmId, wmEvent;
	RECT* rct;


	switch (message)
	{
	case WM_COMMAND:
		wmId = LOWORD(wParam);
		wmEvent = HIWORD(wParam);
		// Разобрать выбор в меню:
		
		return DefWindowProc(hWnd, message, wParam, lParam);
		
		break;
	case WM_PAINT:
		main_renderer.Render();
		break;
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	case WM_SIZING:
		rct = (RECT*)lParam;
		main_renderer.window_width = rct->right - rct->left;
		main_renderer.window_height = rct->bottom - rct->top;
		break;
	default:
		return DefWindowProc(hWnd, message, wParam, lParam);
	}
	return 0;
}
int CApp::StartCycle()
{
	MSG msg;


	while (GetMessage(&msg, NULL, 0, 0))
	{
		
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		
	}

	return (int)msg.wParam;
}

CApp::~CApp()
{
}
