#pragma once
#include "iresource.h"

class CGDIBitmapResource: public IResource
{
public:
	CGDIBitmapResource();
	~CGDIBitmapResource();
	static CGDIBitmapResource* CreateResource(LPCTSTR file_name);
	POINT getSizes();
	virtual void* getResource();
private:
	HBITMAP bitmap;
	bool initalised = false;
	POINT _size;
};

