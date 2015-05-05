#include "stdafx.h"
#include "App.h"


render_object::render_object(UINT _x, UINT _y, ULONG _resource_id)
{
	x = _x;
	y = _y;
	resource_id = _resource_id;
}

CRenderer::CRenderer()
{
}


CRenderer::~CRenderer()
{
}

bool CRenderer::InitRenderer(HWND handle, UINT window_width, UINT window_height)
{
	if (handle == NULL)
		return false;
	this->hWnd = handle;
	this->window_width = window_width ;
	this->window_height = window_height ;
	return true;
}

void CRenderer::AddToQueue(UINT x, UINT y, ULONG resource)
{
	render_queue.push_back(render_object(x, y, resource));
}

bool CRenderer::Render()
{
	HDC main, buffer, bitmap;
	HBITMAP bmpBuffer;
	PAINTSTRUCT ps;
	CGDIBitmapResource* res;
	main = BeginPaint(hWnd, &ps);
	bmpBuffer = CreateCompatibleBitmap(main, SCREEN_WIDTH, SCREEN_HEIGHT);
	if (bmpBuffer == NULL)
	{
		EndPaint(hWnd, &ps);
		return false;
	}
	buffer = CreateCompatibleDC(main);
	if (buffer == NULL)
	{
		DeleteObject(bmpBuffer);
		EndPaint(hWnd, &ps);
		return false;
	}
	SelectObject(buffer, bmpBuffer);
	HBRUSH brush = CreateSolidBrush(RGB(255, 0, 0));
	SelectObject(buffer, brush);
	FloodFill(buffer, 0, 0, RGB(255, 0, 0));
	DeleteObject(brush);


	bitmap = CreateCompatibleDC(buffer);
	for (auto it = render_queue.begin(); it != render_queue.end(); it++)
	{
		
		res = (CGDIBitmapResource*)CApp::getApp()->main_r_manager[it->resource_id].get();
		SelectObject(bitmap, *((HBITMAP*)(res->getResource())));
		BitBlt(buffer, it->x, it->y, res->getSizes().x, res->getSizes().y, bitmap, 0, 0, SRCCOPY);
	}
	DeleteDC(bitmap);
	if (!StretchBlt(main, 0, 0, window_width, window_height, buffer, 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT, SRCCOPY))
	{
		DeleteDC(buffer);
		DeleteObject(bmpBuffer);
		EndPaint(hWnd, &ps);
		return false;
	}
	DeleteDC(buffer);
	DeleteObject(bmpBuffer);
	EndPaint(hWnd, &ps);
	return true;
}

