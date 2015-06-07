#include "stdafx.h"
#include "ResourceManager.h"

#define LIFETIME 120

CResourceManager::CResourceManager()
{
	resources.push_back(std::pair<IResource_ptr, ULONG>(nullptr, 0));
}


IResource_ptr CResourceManager::operator[](UINT index)
{
	resources[index].second = time(nullptr);
	return resources[index].first;
}

CResourceManager::~CResourceManager()
{
	resources.clear();
}

UINT CResourceManager::addResource(UINT type, const LPCTSTR path)
{
	IResource* new_res;
	switch (type)
	{
	case RES_GDI_BITMAP:
		new_res = CGDIBitmapResource::CreateResource(path);
		break;
	default:
		return NULL;

	}
	if (new_res == nullptr)
		return NULL;
	resources.push_back(std::pair<IResource_ptr, ULONG>(std::shared_ptr<IResource>(new_res) , 0));
	return resources.size() - 1;
}

void CResourceManager::CleanOld()
{
	ULONG timing = time(nullptr);
	for (auto it = resources.begin(); it != resources.end(); it++)
	{
		if ((timing - it->second) >= LIFETIME)
		{
			delete &(it->first);
			it->first = nullptr;
		}
	}
}
