#pragma once
#include <vector>
#define SCREEN_WIDTH 1920
#define SCREEN_HEIGHT 1080

struct render_object
{
	UINT x;
	UINT y;
	ULONG resource_id;
	render_object(UINT _x, UINT _y, ULONG _resource_id);
};


class CRenderer
{
public:
	CRenderer();
	~CRenderer();
	bool Render();
	void AddToQueue(UINT x, UINT y, ULONG resource);
	UINT window_width;
	UINT window_height;
	bool InitRenderer(HWND handle,UINT window_width, UINT window_height);
private:
	std::vector<render_object> render_queue;
	HWND hWnd;
};

