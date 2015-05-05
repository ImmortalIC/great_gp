#include "stdafx.h"
#include "GDIBitmapResource.h"


CGDIBitmapResource::CGDIBitmapResource()
{

}

CGDIBitmapResource* CGDIBitmapResource::CreateResource(LPCTSTR file_name)
{
	CGDIBitmapResource* res = new CGDIBitmapResource();
	res->bitmap = (HBITMAP)LoadImage(NULL, file_name, IMAGE_BITMAP, 0, 0, LR_DEFAULTSIZE | LR_DEFAULTCOLOR | LR_LOADFROMFILE);
	if (res->bitmap == NULL)
	{
		delete res;
		return nullptr;
	} else {
		res->initalised = true;
		BITMAP info;
		GetObject(res->bitmap,sizeof(info),&info);
		res->_size.x = info.bmWidth;
		res->_size.y = info.bmHeight;
		return res;
	}
}

CGDIBitmapResource::~CGDIBitmapResource()
{
	if (initalised)
	{
		DeleteObject(bitmap);
	}
}


void* CGDIBitmapResource::getResource()
{

	return &this->bitmap;
}

POINT CGDIBitmapResource::getSizes()
{
	return _size;
}