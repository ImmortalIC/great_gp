#pragma once
#include "stdafx.h"
#include "all_resources.h"
class IRenderer
{
public:
	IRenderer(){};
	virtual ~IRenderer(){};
	virtual bool Render()=0;
	virtual void AddToQueue(UINT x, UINT y, ULONG resource)=0;
	UINT window_width;
	UINT window_height;
	virtual bool InitRenderer(HWND handle, UINT window_width, UINT window_height)=0;
};


class IResourceManager
{
public:
	IResourceManager(){};
	virtual ~IResourceManager(){};
	virtual IResource_ptr operator[](UINT index)=0;
	virtual UINT addResource(UINT type, const LPCTSTR path)=0;
	virtual void CleanOld()=0;

};